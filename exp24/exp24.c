%{
#include <stdio.h>
%}

%%

<[^>]+>        { printf("HTML Tag: %s\n", yytext); }

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

    fp = fopen("input.html", "r");

    if (fp == NULL)
    {
        printf("Cannot open input.html\n");
        return 1;
    }

    yyin = fp;

    printf("HTML Tags:\n");
    printf("--------------------\n");

    yylex();

    fclose(fp);

    return 0;
}
