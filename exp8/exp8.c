#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char first[MAX][MAX];
int n;

/* Check whether character is a non-terminal */
int isNonTerminal(char c)
{
    return (c >= 'A' && c <= 'Z');
}

/* Find the production index of a non-terminal */
int findIndex(char c)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (production[i][0] == c)
            return i;
    }

    return -1;
}

/* Add symbol to FIRST set */
void addToFirst(int index, char symbol)
{
    int i;

    for (i = 0; first[index][i] != '\0'; i++)
    {
        if (first[index][i] == symbol)
            return;
    }

    int len = strlen(first[index]);
    first[index][len] = symbol;
    first[index][len + 1] = '\0';
}

/* Find FIRST of a symbol */
void findFirst(char symbol, int index)
{
    int i, j;
    int prodIndex;

    /* Terminal */
    if (!isNonTerminal(symbol))
    {
        addToFirst(index, symbol);
        return;
    }

    prodIndex = findIndex(symbol);

    if (prodIndex == -1)
        return;

    /* Check all productions of the non-terminal */
    for (i = 0; i < n; i++)
    {
        if (production[i][0] == symbol)
        {
            /* RHS begins at position 3 */
            char firstSymbol = production[i][3];

            /* Epsilon */
            if (firstSymbol == '#')
            {
                addToFirst(index, '#');
            }
            else if (!isNonTerminal(firstSymbol))
            {
                addToFirst(index, firstSymbol);
            }
            else
            {
                /* Find FIRST of non-terminal */
                findFirst(firstSymbol, index);
            }
        }
    }
}

int main()
{
    int i;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("\nEnter productions (use # for epsilon):\n");

    for (i = 0; i < n; i++)
    {
        scanf("%s", production[i]);
        first[i][0] = '\0';
    }

    /* Find FIRST for each non-terminal */
    for (i = 0; i < n; i++)
    {
        findFirst(production[i][0], i);
    }

    printf("\nFIRST Sets:\n");

    for (i = 0; i < n; i++)
    {
        printf("FIRST(%c) = { ", production[i][0]);

        for (int j = 0; first[i][j] != '\0'; j++)
        {
            printf("%c ", first[i][j]);
        }

        printf("}\n");
    }

    return 0;
}
