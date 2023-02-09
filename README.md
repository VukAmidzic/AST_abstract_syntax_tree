## About
This is a personal hobby-made language written in C++ together with Flex/Bison tools. The goal is to simulate the translation of the programming language into assembly code through the syntax tree and its execution.


### Project goals
 - [X] Fix some minor bugs regarding the assembly code
 - [X] Fix subtraction and shifting
 - [X] Make comments
 - [X] Make error messages verbose
 - [X] Implement if-else statement
 - [ ] Implement loop statement

 
### Supported operations and statements
- assignment
- printing 
- arithmetic operations
- logical and bitwise operations
- nested if-else statements

 
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
Any change made to the ``` test.fkc ``` file requires repeating the previous steps
starting from ```make com``` command.

### Example 
```
/* 
    possible multiple assignment to
    same variable without losing the data 
*/
a := 2;
b := (a << 2) - 1;
a := b * b;

/* 
    possible nested if-else statements 
*/
if (b = 8) {
    c := 0;
    
    if (b - b/2*2 = 0) {
        c := 1;
    }
    else {
        c := 0;
    };
} else {
    c := 10;
};

print(a); /* prints 49 */
print(b); /* prints 7 */
print(c); /* prints 10 */
print(a + b + c); /* prints 66 */
```

