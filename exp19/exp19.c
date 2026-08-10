#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char leading[MAX][MAX];
int n;

/* Check whether a character is a non-terminal */
int isNonTerminal(char c)
{
    return (c >= 'A' && c <= 'Z');
}

/* Find index of a non-terminal */
int findIndex(char c)
{
    for (int i = 0; i < n; i++)
    {
        if (production[i][0] == c)
            return i;
    }

    return -1;
}

/* Add symbol to LEADING set */
int addLeading(int index, char symbol)
{
    int i;

    if (symbol == '#')
        return 0;

    for (i = 0; leading[index][i] != '\0'; i++)
    {
        if (leading[index][i] == symbol)
            return 0;
    }

    int len = strlen(leading[index]);
    leading[index][len] = symbol;
    leading[index][len + 1] = '\0';

    return 1;
}

/* Compute LEADING sets */
void computeLeading()
{
    int changed = 1;

    while (changed)
    {
        changed = 0;

        for (int i = 0; i < n; i++)
        {
            char A = production[i][0];
            int Aindex = findIndex(A);

            /*
             * Production format:
             * A->alpha
             * RHS starts from position 3
             */
            char first = production[i][3];

            /* Case 1: A -> a... */
            if (!isNonTerminal(first))
            {
                if (addLeading(Aindex, first))
                    changed = 1;
            }

            /* Case 2: A -> Ba...
             * Add LEADING(B)
             */
            else
            {
                int Bindex = findIndex(first);

                if (Bindex != -1)
                {
                    for (int j = 0; leading[Bindex][j] != '\0'; j++)
                    {
                        if (addLeading(Aindex, leading[Bindex][j]))
                            changed = 1;
                    }
                }

                /*
                 * Case 3:
                 * A -> B a ...
                 * Add terminal 'a'
                 */
                if (production[i][4] != '\0' &&
                    !isNonTerminal(production[i][4]))
                {
                    if (addLeading(Aindex, production[i][4]))
                        changed = 1;
                }
            }
        }
    }
}

int main()
{
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("\nEnter productions:\n");
    printf("Example: E->E+T\n\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%s", production[i]);
        leading[i][0] = '\0';
    }

    computeLeading();

    printf("\nLEADING Sets:\n");
    printf("----------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("LEADING(%c) = { ", production[i][0]);

        for (int j = 0; leading[i][j] != '\0'; j++)
        {
            printf("%c ", leading[i][j]);
        }

        printf("}\n");
    }

    return 0;
}
