# practiceOS
A simple "Operating System" if you can call it that I built with the knowledge from osdev.org and several other sites

## How to compile

It's as simple as entering `./build.sh` on linux.  
Please note that you have to have gcc and nasm installed.  
If you want to build an .iso file you'll also need genisoimage.  

The images where tested with qemu and bochs.  
To run with qemu type `qemu-system-i386 -drive format=raw,file=practiceOS.img`  
or `qemu-system-i386 -cdrom practiceOS.iso` 

## Notes

PracticeOS has a hardcoded german keyboard layout. I am however planning on changing this in near future.  
Type `help` or `HELP` in the PracticeOS commandline to receive a list of commands.  

## Features
TicTacToe  
A [brainfuck](https://en.wikipedia.org/wiki/Brainfuck) interpreter  
A simple textmode-cursor tool  
