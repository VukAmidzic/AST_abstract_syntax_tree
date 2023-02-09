%option noyywrap
%option nounput
%option noinput
%x comment 
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <vector>
    #include <utility>
    #include "ast.hpp"
    #include "parser.tab.hpp"
    
    /*#define PRINT 1
    #define ID 2
    #define NUM 3
    #define PLUS 4
    #define MINUS 5
    #define MUL 6
    #define DIV 7

    #define ASSIGN 8
    #define SEMIC 9

    #define LP 10
    #define RP 11

    #define LBP 12
    #define RBP 13

    #define SHR 14
    #define SHL 15

    #define AND 16
    #define OR 17
    #define NOT 18

    #define LESS 19
    #define GREAT 20
    #define EQ 21
    #define NEQ 22
    #define LEQ 23
    #define GEQ 24
    */
    
    int line_index = 1;
%}

%%
"print" { return PRINT; }
"if" { return IF; }
"else" { return ELSE; }

[a-zA-Z][a-zA-Z_0-9]* {
    yylval.id = new std::string(yytext);
    return ID; 
}

[0-9][0-9]* {
    yylval.number = atoi(yytext);
    return NUM;
}

"/*" { BEGIN(comment); }
<comment>[^*\n]* {}
<comment>"*"* {}
<comment>\n { line_index++; }
<comment>\*+"/" { BEGIN(INITIAL); }

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MUL; }
"/" { return DIV; }

":=" { return ASSIGN; }
";" { return SEMIC; }

"(" { return LP; }
")" { return RP; }

"{" { return LCP; }
"}" { return RCP; }

">>" { return SHR; }
"<<" { return SHL; }

"&&" { return AND; }
"||" { return OR; }
"!" { return NOT; }

"<" { return LESS; }
">" { return GREAT; }
"=" { return EQ; }
"<>" { return NEQ; }
"<=" { return LEQ; }
">=" { return GEQ; }

[ \t] {};
\n { line_index++; }

. {
    fprintf(stderr, "Error in %s, line %d : \n", __FILE__, line_index);
    fprintf(stderr, "Uknown lexema -> {%s}\n", yytext);
    return 1;
}

%%
