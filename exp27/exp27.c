%{
#include <stdio.h>
%}

%%

[A-Z]+      { printf("Capital Word: %s\n", yytext); }

[ \t\n]+    ;

.           ;

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter the input:\n");
    yylex();

    return 0;
}
