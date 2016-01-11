::current_directory: Manu_OS/src
@echo off
cd ../output
echo Linking all files to build kernel.bin
i586-elf-ld -T ../src/linker.ld -o kernel.bin *.o
echo Building bootable kernel image
cat ../imp_files/stage1 ../imp_files/stage2 ../imp_files/pad kernel.bin ../imp_files/pad> kernel.img
::rm *.o
cd .. 
cd ..
rm kernel.img
rm kernel.bin
cp Manu_OS/output/kernel.img kernel.img
cp Manu_OS/output/kernel.bin kernel.bin
imdisk -a -f Manu_OS.flp -s 1440K -m B:
rm B:/kernel.bin
::rm B:/boot/grub/grub.conf
::rm B:/boot/grub/grub.cfg
::rm B:/boot/grub/MENU.LST
cp kernel.bin B:/kernel.bin
::cp grub.conf B:/boot/grub/grub.conf 
::cp grub.cfg B:/boot/grub/grub.cfg 
::cp MENU.LST B:/boot/grub/MENU.LST 
imdisk -D -m B:
rm Manu_OS.img
cp Manu_OS.flp Manu_OS.img
::E:/OSs/Manu_OS/emulators/Bochs/Bochs-2.5.1/bochs.exe bochsrc.bxrc
::"C:\Program Files\Oracle\VirtualBox\VirtualBox.exe" --comment "ManuOS" --startvm "9a1bcb03-5088-4f4a-aca7-dd7fcb27ad1a"
E:/OSs/Manu_OS/emulators/qemu/qemu.exe -fda Manu_OS.flp
