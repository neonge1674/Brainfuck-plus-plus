# Brainfuck-plus-plus
An interpreter for the Brainfuck++ language

## Core Principles
Brainfuck++ is meant to be a superset of original brainfuck ie. All valid brainfuck code should be valid brainfuck++ code. It is also designed to not abstract to much from the core of moving a pointer around an array of bytes and modifying individual values. There are abstractions, but it's C level abstractions not Python level abstractions, to put in simpler terms. Only individuals can be modified, so no 16-bit ints or bitwise operations.

## Syntax 
This assumes you do not know any of the syntax of the original brainfuck.

### Basic commands

Brainfuck++, like the original stimualtes a tape of cells, which are 8-bit ints. The base commands are:
1. `+` - Add
2. `-` - Subtract
3. `e` - Erase/Equals
4. `<` - Move left
5. `>` - Move right
 
These commands are the most basic commands in bfpp, due to showing simmilar behavour. They can be executed with or without an argument. If no argument is provided, the Add adds one to the current cell, Subtract subtracts one, Erase/Equals sets the cell to zero, Move left moves the tape to the left, Move right moves it to the right. (Argumentless commands look like this: `+-e<>`)

As for commands with arguments. Arguments are simply numerical values. If Add/Substract has an argument than it adds/subtracts that number from the cell(`+65-3` <- example) Erase/Equals when provided with an argument, sets the current cell to that value, hence the name Erase/Equals. Move left and right move the tape by the number of cells provided by the argument. You can still chain commands like in the original bf(`++++++`), however just providing arguments is both more readable and faster, both to write and run.

### IO commands

Brainfuck++ also has a pair of two IO commands, The print `.` and the input `,`. `.` prints the value of the current cell as an ASCII character to the console, `,` halts the program requests a single character and sets the value of the cell to ASCII value of the character inputed. This pretty much it.

### Loops

The last commands that bfpp shares with bf are the loop markers `[]`. If the value of the current cell is bigger than 0 that the code inside the brackets is looped. I inteded to also add brackets for an 'if' block, however an 'if' block is just a loop is just a loop that repeats once.

