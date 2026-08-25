%{
#include <stdio.h>
int vowels = 0;
%}

%%
[aeiouAEIOU]    { vowels++; }
\n              { 
                    printf("Number of vowels = %d\n", vowels);
                    return 0;
                }
.               ;
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a sentence: ");
    yylex();
    return 0;
}
