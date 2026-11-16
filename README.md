# Brainfuck-plus-plus
An interpreter for the Brainfuck++ language

## Core Principles
Brainfuck++ is meant to be a superset of original brainfuck ie. All valid brainfuck code should be valid brainfuck++ code. It is also designed to not abstract to much from the core of moving a pointer around an array of bytes and modifying individual values. There are abstractions, but it's C level abstractions not Python level abstractions, to put in simpler terms. Only individuals can be modified, so no 16-bit ints or bitwise operations.

## Syntax 
This assumes you do not know any of the syntax of the original brainfuck.

Brainfuck++, like the original stimualtes a tape of cells, which are 8-bit ints. The base commands are:
1. `+` - Add
2. `-` - Subtract
3. `e` - Erase/Equals
4. `<` - Move left
5. `>` - Move right
 
These commands are the most basic commands in bfpp, due to showing simmilar behavour. They can be executed with or without an argument. If no argument is provided, the Add adds one to the current cell, Subtract subtracts one, Erase/Equals sets the cell to zero, Move left moves the tape to the left, Move right moves it to the right. (Argumentless commands look like this: `+-e<>`)
