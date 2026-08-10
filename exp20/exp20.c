#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char trailing[MAX][MAX];
int n;

/* Check whether a symbol is a non-terminal */
int isNonTerminal(char c)
{
    return (c >= 'A' && c <= 'Z');
}

/* Find the index of a non-terminal */
int findIndex(char c)
{
    for (int i = 0; i < n; i++)
    {
        if (production[i][0] == c)
            return i;
    }

    return -1;
}

/* Add a symbol to TRAILING set */
int addTrailing(int index, char symbol)
{
    int i;

    /* Check whether symbol already exists */
    for (i = 0; trailing[index][i] != '\0'; i++)
    {
        if (trailing[index][i] == symbol)
            return 0;
    }

    int len = strlen(trailing[index]);

    trailing[index][len] = symbol;
    trailing[index][len + 1] = '\0';

    return 1;
}

/* Compute TRAILING sets */
void computeTrailing()
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
             * Find the last symbol of RHS.
             * RHS starts at position 3.
             */
            int len = strlen(production[i]);
            char last = production[i][len - 1];

            /* Case 1: A -> ...a
               If last symbol is terminal */
            if (!isNonTerminal(last))
            {
                if (addTrailing(Aindex, last))
                    changed = 1;
            }

            /* Case 2: A -> ...B
               If last symbol is non-terminal */
            else
            {
                int Bindex = findIndex(last);

                if (Bindex != -1)
                {
                    for (int j = 0;
                         trailing[Bindex][j] != '\0';
                         j++)
                    {
                        if (addTrailing(Aindex,
                                        trailing[Bindex][j]))
                        {
                            changed = 1;
                        }
                    }
                }

                /*
                 * Case 3:
                 * A -> ...aB
                 *
                 * Add terminal 'a' to TRAILING(A)
                 */
                if (len >= 5)
                {
                    char beforeLast = production[i][len - 2];

                    if (!isNonTerminal(beforeLast))
                    {
                        if (addTrailing(Aindex, beforeLast))
                            changed = 1;
                    }
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
        trailing[i][0] = '\0';
    }

    computeTrailing();

    printf("\nTRAILING Sets:\n");
    printf("----------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("TRAILING(%c) = { ",
               production[i][0]);

        for (int j = 0;
             trailing[i][j] != '\0';
             j++)
        {
            printf("%c ", trailing[i][j]);
        }

        printf("}\n");
    }

    return 0;
}
