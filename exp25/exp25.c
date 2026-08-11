%{
#include <stdio.h>

int line_no = 1;
%}

%%

\n      {
            printf("\n%4d  ", ++line_no);
        }

.       {
            printf("%s", yytext);
        }

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

    printf("Line Numbered C Program\n");
    printf("------------------------\n");
    printf("%4d  ", line_no);

    yylex();

    fclose(fp);

    return 0;
}
