# Programming with an image for the PPVM (PicProg Virtual Machine)

### Intro

The PPVM is a virtual machine that executes instruction from the pixels of an image.
By precisely setting the pixels of an image on a painting software you can create all kinds of programs.

### Why ?

For fun.

### How does the PPVM executes images ?

The PPVM, as any virtual machine, has a program pointer, but unlike most virtual machines, this program counter is located in 2 dimensions, and can move 4 ways.
Two register keep track of its position, and one keeps it's direction.
Unless it is changed, the program pointer will continue in the same direction and read pixels one by one.
The program will only stop if a program end instruction is found or if an error is caused. If the pointer leaves the image, it will be "teleported" to the other side of it.
The pixels can also not be instructions but pure data, such as arguments. The pixels can even be changed by some instructions, and can be used as ram to store variables.

### How is an instruction read ?

The pointer starts at position 0,0, and with direction 0 (right)
An instruction is defined by the first byte of the pixel that the program pointer is on, so by the Red component of that pixel.
The two others bytes are used for arguments. They are either the arguments themselves if they fit, or a 2D pointer to the arguments.
The Alpha byte (4th byte) is never used.
If an instruction has a pointer to arguments, the arguments will be read at that position, in line, in the same direction as the program pointer. They will be read until the needed information is found.
As each pixel stores 3 bytes, the arguments might stop not exactly between two pixels.

### What kind of image formats can I use ?

I recommend PNG or BMP (bitmap). Formats such as JPEG use lossy compression and your pixels will be altered as they will only be approximated.
You can technically use any format of image supported by the SFML, as it will load them in a simple 4 bytes per pixel array.

# Opcodes

0 : Nop
1 : Terminate program
// 2 : Jump
// 3 : Change pointer direction
4 : Print string


