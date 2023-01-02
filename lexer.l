%option noyywrap
%option nounput
%option noinput
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"
    #include "parser.tab.h"
%}

%%
[0-9][0-9]* {
    yylval.number = atoi(yytext);
    return NUM;
}

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MUL; }
"/" { return DIV; }
"(" { return LP; }
")" { return RP; }

[ \n\t] {};

. {
    fprintf(stderr, "Uknown lexema!!\n");
}

%%
