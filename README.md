## About
This is a rework written in C++ that constructs AST tree and compiles it into assembly code. Basic arithmetic, comparison and logical operations supported, as well as assigning and printing operations.

### Project goals
 - [X] Fix some minor bugs regarding the assembly code
 - [X] Fix subtraction and shifting
 - [X] Made comments
 - [X] Made error messages verbose
 - [ ] Implement if-else statement
 - [ ] Implement loop statement

## Running the program
First, type
```
make
```
to get a parser.
Until this project gets finished, you can type your program in ``` test.fkc ``` file.
After that, type
```
make com
```
to compile your program into an assembly code, which you can, later on, run by typing:
```
make run
./test
```

### Example 
```
a := 1;
b := 2;
c := 3;
d := 4;

print(a * b * c * d << 2); //prints 96
```

