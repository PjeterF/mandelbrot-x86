# mandelbrot-x86
This program creates a bmp image of specified size. Function calculating whether a pixel belongs to the set is written in x86 assembly.

## Running the program
> nasm -f elf32 mandelbrot.asm
> 
> gcc -m32 main.c -lm mandelbrot.o a
> 
> ./a [size]

size - number from 1-12

## Example
![image](image.bmp)
