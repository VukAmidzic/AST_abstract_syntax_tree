#!bin/sh

parser: ast.cpp lex.yy.c parser.tab.cpp
	g++ -Wall -Wextra ast.cpp lex.yy.c parser.tab.cpp -g -o parser 

lex.yy.c: lexer.l
	lex lexer.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d parser.ypp

.PHONY: clean run com install 
install:
	flex --version && bison --version || sudo apt-get install flex && sudo apt-get install bison 
run:
	gcc asm_ops.c test.s -O3 -fno-pie -no-pie -g -o test 

com:
	./parser test.fkc > test.s || (exit 0)

clean:
	rm -r *.tab.* *.yy.* parser test
