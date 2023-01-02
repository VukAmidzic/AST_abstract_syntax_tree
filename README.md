## About
This is an attempt to make an AST abstract syntax tree in C
that currently supports addition,subtraction, multiplication
and division, and also makes an assembly code.

## Running the program
First, type
```
make
```
to compile and run the parser.
The result after parsing will be a constructed AST
syntax tree.

Once you've written you arithmetic term, type
```
make compile_asm
```
to translate AST syntax tree to assembly code.
At the end, type
```
./test
echo $?
```
to see the result of your term.
To run your program again, type
```
make clean
```
and repeat the procedure from beginning. 

