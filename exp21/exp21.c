%{
#include <stdio.h>

int characters = 0;
int lines = 0;
int words = 0;
%}

%%

\n              { characters++; lines++; }

[ \t]+          { characters += yyleng; }

[a-zA-Z0-9_]+   { characters += yyleng; words++; }

.               { characters++; }

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

    printf("\n--- RESULT ---\n");
    printf("Characters = %d\n", characters);
    printf("Lines      = %d\n", lines);
    printf("Words      = %d\n", words);

    return 0;
}
