#!/bin/sh
mkdir build
mkdir build/kernel

nasm -fbin -o build/boot.bin bootloader/boot.S
nasm -felf32 kernel/src/kernel.S -o build/kernel/kernel_entry.o

for i in $(find . -name "*.c"); do
    [ -f "$i" ] || break
    echo "Compiling $i..."
    gcc -ffreestanding -I./kernel/include -fno-pie -m32 -c $i -o .$(echo "$i" | cut -f 2 -d '.').o
done

ld -melf_i386 -o build/kernel.bin -Ttext 0x1000 ./build/kernel/kernel_entry.o $(find ./kernel/. -name "*.o") --oformat binary

# making the img
cat build/boot.bin build/kernel.bin > build/practiceOS.bin
dd if=/dev/zero of=practiceOS.img bs=1024 count=1440
dd if=build/practiceOS.bin of=practiceOS.img seek=0 conv=notrunc

# making the iso
# you may comment this part out if you don't want the ISO or don't have genisoimage installed
mkdir build/iso
cp practiceOS.img build/iso/
genisoimage -quiet -V 'practiceOS' -input-charset iso8859-1 -o practiceOS.iso -b practiceOS.img -hide practiceOS.img build/iso/

rm -r build/
rm -rf $(find . -name "*.o")

# uncomment this in case you want to directly boot from the image
#qemu-system-i386 -drive format=raw,file=practicetOS.img -no-reboot -no-shutdown
