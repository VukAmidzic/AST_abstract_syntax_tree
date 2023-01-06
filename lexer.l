%option noyywrap
%option nounput
%option noinput
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"
    #include "parser.tab.h"
    int line_index = 1;
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
 /*
"<" { return LESS; }
">" { return GREAT; }
"==" { return EQ; }
"!=" { return NEQ; }
"<=" { return LEQ; }
">=" { return GEQ; }
 */

[ \t] {};
\n { line_index++; }

. {
    fprintf(stderr, "Error in %s, line %d : \n", __FILE__, line_index);
    fprintf(stderr, "Uknown lexema -> {%s}\n", yytext);
    return 1;
}

%%
