%{
#include <stdio.h>

int comment_count = 0;
FILE *out;
%}

%%

"//".*                  { comment_count++; }

"/*"([^*]|\*+[^*/])*\*+"/" {
                            comment_count++;
                         }

\n                       { fprintf(out, "\n"); }

.                        { fprintf(out, "%s", yytext); }

%%

int yywrap()
{
    return 1;
}

int main()
{
    FILE *in;

    /* Open input C file */
    in = fopen("input.c", "r");

    if (in == NULL)
    {
        printf("Cannot open input.c\n");
        return 1;
    }

    /* Open output file */
    out = fopen("output.c", "w");

    if (out == NULL)
    {
        printf("Cannot create output.c\n");
        fclose(in);
        return 1;
    }

    yyin = in;

    /* Scan input file */
    yylex();

    fclose(in);
    fclose(out);

    printf("\nNumber of comment lines removed: %d\n", comment_count);
    printf("Comments removed successfully.\n");
    printf("Output written to output.c\n");

    return 0;
}
