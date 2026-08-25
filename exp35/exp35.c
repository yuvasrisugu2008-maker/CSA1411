%{
#include <stdio.h>
%}

%%
[0-9]+              { printf("Number : %s\n", yytext); }
[a-zA-Z]+           { printf("Word   : %s\n", yytext); }
[ \t\n]+            ;       /* Ignore spaces and new lines */
.                   ;       /* Ignore other characters */
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a statement:\n");
    yylex();
    return 0;
}
