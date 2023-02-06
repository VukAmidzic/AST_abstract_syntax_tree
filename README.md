## About
This is a rework written in C++ that constructs AST tree and compiles it into assembly code. Basic arithmetic, comparison and logical operations supported, as well as assigning and printing operations.

### Project goals
 - [X] Fix some minor bugs regarding the assembly code
 - [ ] Find how to do 2's complement in assembly
 - [ ] Implement if-else statement
 - [ ] Implement loop statement

## Running the program
First, type
```
make
```
to compile files and get a parser.
Until this project gets finished, you can type your program in ``` test.fkc ``` file.
After that, type
```
make run
```
to run program through created parser.
The result of your program will be stored as a generated assembly code.

At the end, type
```
./test
```
to see the result of your program that will be printed to the terminal :) .

### Example 
```
a := 1;
b := 2;
c := 3;
d := 4;

print(a * b * c * d << 2); //prints 96
```

