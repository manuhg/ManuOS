#current_directory: Manu_OS/src
if test "`whoami`" != "root" ; then
 echo "You must be logged in as root"
 exit
fi
set -e

if [[ "$OSTYPE" == "linux-gnu" ]]; then
export PATH="/home/gk1000/opt/cross/bin:$PATH"
fi
cd ../output
echo Linking all files to build kernel.bin
i586-elf-ld -T ../src/linker.ld -o kernel.bin *.o
echo Building bootable kernel image
cd .. 
cd ..
rm kernel.bin
cp Manu_OS/output/kernel.bin kernel.bin
mount  -o rw, Manu_OS.flp /mnt
rm /mnt/kernel.bin
cp kernel.bin /mnt/kernel.bin
imdisk -D -m B:
rm Manu_OS.img
umount /dev/loop0
VirtualBox --comment "ManuOS" --startvm "062fd560-66a6-4f91-946e-fd91a9515f2f"
qemu-system-i386 -fda Manu_OS.flp
