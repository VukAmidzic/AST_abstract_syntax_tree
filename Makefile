test: parser
	./parser test.s

parser: ast.c lex.yy.c parser.tab.c
	gcc -Wall -Wextra ast.c lex.yy.c parser.tab.c -o parser 

lex.yy.c: lexer.l
	lex lexer.l

parser.tab.h parser.tab.c: parser.y
	bison -d parser.y

.PHONY: clean compile_asm run_asm
compile_asm: 
	gcc -m64 -masm=intel test.s -o test 
	
clean:
	rm -r *.tab.* *.yy.* test parser
