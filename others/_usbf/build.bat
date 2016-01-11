nasm -f bin -o usbf.bin usbf.asm
dd status=noxfer conv=notrunc if=usbf.bin of=usbf.flp
E:/OSs/Manu_OS/emulators/qemu/qemu.exe -fda usbf.flp