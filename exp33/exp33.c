%{
#include <stdio.h>
int count = 0;
%}

%%
[aeiouAEIOU]    { count++; }
\n              {
                  printf("Number of vowels = %d\n", count);
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
