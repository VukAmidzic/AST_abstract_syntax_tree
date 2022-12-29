test: main test.s
	./main test.s && gcc -m64 -masm=intel test.s -o test

main: main.c ast.c
	gcc -Wall -Wextra -Wswitch -Wimplicit-fallthrough ast.c main.c -o main
	
.PHONY: clean
clean: 
	rm -rf main test
