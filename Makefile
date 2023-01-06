parser: ast.c lex.yy.c parser.tab.c
	gcc -Wall -Wextra ast.c lex.yy.c parser.tab.c -o parser 

lex.yy.c: lexer.l
	lex lexer.l

parser.tab.h parser.tab.c: parser.y
	bison -d parser.y

.PHONY: clean run
run:
	./parser test.s && gcc test.s -fno-pie -no-pie -g -o test

clean:
	rm -r *.tab.* *.yy.* parser test
