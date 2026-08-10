#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char follow[MAX][MAX];
int n;

/* Add a symbol to FOLLOW set if it is not already present */
void addToFollow(int index, char symbol)
{
    int i;

    if (symbol == '#')
        return;

    for (i = 0; follow[index][i] != '\0'; i++)
    {
        if (follow[index][i] == symbol)
            return;
    }

    int len = strlen(follow[index]);
    follow[index][len] = symbol;
    follow[index][len + 1] = '\0';
}

/* Find index of non-terminal */
int findNonTerminal(char symbol)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (production[i][0] == symbol)
            return i;
    }

    return -1;
}

/* Check whether a symbol is a non-terminal */
int isNonTerminal(char symbol)
{
    return (symbol >= 'A' && symbol <= 'Z');
}

void findFollow()
{
    int changed = 1;
    int i, j, k;
    char lhs, current, next;

    /* FOLLOW of start symbol contains $ */
    follow[0][0] = '$';
    follow[0][1] = '\0';

    while (changed)
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            lhs = production[i][0];

            /* RHS starts after -> */
            for (j = 3; production[i][j] != '\0'; j++)
            {
                current = production[i][j];

                if (!isNonTerminal(current))
                    continue;

                k = j + 1;

                if (production[i][k] != '\0')
                {
                    next = production[i][k];

                    if (!isNonTerminal(next))
                    {
                        if (next != '#')
                            addToFollow(findNonTerminal(current), next);
                    }
                    else
                    {
                        /* If next is non-terminal, add its FIRST
                           symbols except epsilon.
                           For this simple program, FIRST is derived
                           from the first RHS symbol. */

                        int ntIndex = findNonTerminal(next);

                        for (int x = 3; production[ntIndex][x] != '\0'; x++)
                        {
                            char first = production[ntIndex][x];

                            if (!isNonTerminal(first))
                            {
                                if (first != '#')
                                    addToFollow(findNonTerminal(current), first);
                                break;
                            }
                        }

                        /* If next can produce epsilon */
                        int canEpsilon = 0;

                        for (int p = 0; p < n; p++)
                        {
                            if (production[p][0] == next)
                            {
                                int len = strlen(production[p]);

                                if (production[p][3] == '#' &&
                                    len == 4)
                                {
                                    canEpsilon = 1;
                                }
                            }
                        }

                        if (canEpsilon)
                        {
                            int before = strlen(follow[findNonTerminal(current)]);

                            int lhsIndex = findNonTerminal(lhs);

                            for (int x = 0; follow[lhsIndex][x] != '\0'; x++)
                                addToFollow(findNonTerminal(current),
                                            follow[lhsIndex][x]);

                            int after = strlen(follow[findNonTerminal(current)]);

                            if (before != after)
                                changed = 1;
                        }
                    }
                }
                else
                {
                    /* A at the end of RHS:
                       FOLLOW(A) is added to FOLLOW(current) */

                    int currentIndex = findNonTerminal(current);
                    int lhsIndex = findNonTerminal(lhs);

                    int before = strlen(follow[currentIndex]);

                    for (int x = 0; follow[lhsIndex][x] != '\0'; x++)
                        addToFollow(currentIndex, follow[lhsIndex][x]);

                    int after = strlen(follow[currentIndex]);

                    if (before != after)
                        changed = 1;
                }
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
        follow[i][0] = '\0';
    }

    findFollow();

    printf("\nFOLLOW Sets:\n");

    for (i = 0; i < n; i++)
    {
        printf("FOLLOW(%c) = { ", production[i][0]);

        for (int j = 0; follow[i][j] != '\0'; j++)
        {
            printf("%c ", follow[i][j]);
        }

        printf("}\n");
    }

    return 0;
}
