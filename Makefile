test:
	gcc -Wall -Wextra ast.c test.c -o test
		
.PHONY: clean
clean: 
	rm -r test
