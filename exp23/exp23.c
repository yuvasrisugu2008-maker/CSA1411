%{
#include <stdio.h>

int macros = 0;
int headers = 0;
%}

%%

^[ \t]*#[ \t]*define[ \t]+[A-Za-z_][A-Za-z0-9_]* {
    macros++;
}

^[ \t]*#[ \t]*include[ \t]*[<"][^>"]+[>"] {
    headers++;
}

[ \t\n]+       ;

.              ;

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

    yylex();

    fclose(fp);

    printf("\n-----------------------------\n");
    printf("Number of Macros   : %d\n", macros);
    printf("Number of Headers  : %d\n", headers);
    printf("-----------------------------\n");

    return 0;
}
