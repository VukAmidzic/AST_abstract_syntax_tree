parser: ast.cpp lex.yy.c parser.tab.cpp
	g++ -Wall -Wextra ast.cpp lex.yy.c parser.tab.cpp -g -o parser 

lex.yy.c: lexer.l
	lex lexer.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d parser.ypp

.PHONY: clean run com
run:
	gcc asm_ops.c test.s -fno-pie -no-pie -g -o test 

com:
	./parser test.fkc > test.s || (exit 0)

clean:
	rm -r *.tab.* *.yy.* parser test
