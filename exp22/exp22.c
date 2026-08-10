%{
#include <stdio.h>
%}

%%

[0-9]+(\.[0-9]+)?       { printf("Constant: %s\n", yytext); }

\'([^\\\']|\\.)\'       { printf("Constant: %s\n", yytext); }

\"([^\\\"]|\\.)*\"       { printf("String Constant: %s\n", yytext); }

[ \t\n]+                ;

.                       ;

%%

int yywrap()
{
    return 1;
}

int main()
{
    FILE *fp;

    fp = fopen("input.c", "r");

    if (fp == NULL)
    {
        printf("Cannot open input.c\n");
        return 1;
    }

    yyin = fp;

    printf("Constants in the C program:\n");
    printf("----------------------------\n");

    yylex();

    fclose(fp);

    return 0;
}
