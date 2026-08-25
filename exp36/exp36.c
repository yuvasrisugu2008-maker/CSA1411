%{
#include <stdio.h>

int positive = 0;
int negative = 0;
%}

%%
[+]?[0-9]+(\.[0-9]+)?     {
                              printf("Positive Number : %s\n", yytext);
                              positive++;
                           }

-[0-9]+(\.[0-9]+)?         {
                              printf("Negative Number : %s\n", yytext);
                              negative++;
                           }

[ \t\n]+                   ;   /* Ignore spaces and new lines */
.                          ;   /* Ignore other characters */
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter numbers:\n");
    yylex();

    printf("\nTotal Positive Numbers = %d\n", positive);
    printf("Total Negative Numbers = %d\n", negative);

    return 0;
}
