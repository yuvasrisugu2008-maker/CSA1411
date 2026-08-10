#include <stdio.h>
#include <string.h>

int main()
{
    char nonTerminal;
    char production[10][50];
    int n, i, j;
    char prefix[50];
    int prefixLen = 0;

    printf("Enter the non-terminal: ");
    scanf(" %c", &nonTerminal);

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%s", production[i]);
    }

    /* Find common prefix between all productions */
    strcpy(prefix, production[0]);

    for (i = 1; i < n; i++)
    {
        prefixLen = 0;

        while (prefix[prefixLen] != '\0' &&
               production[i][prefixLen] != '\0' &&
               prefix[prefixLen] == production[i][prefixLen])
        {
            prefixLen++;
        }

        prefix[prefixLen] = '\0';
    }

    printf("\nGrammar after eliminating left factoring:\n");

    if (prefixLen == 0)
    {
        /* No common prefix */
        printf("%c -> ", nonTerminal);

        for (i = 0; i < n; i++)
        {
            printf("%s", production[i]);

            if (i < n - 1)
                printf(" | ");
        }

        printf("\n");
    }
    else
    {
        /* A -> prefix A' */
        printf("%c -> %s%c'\n", nonTerminal, prefix, nonTerminal);

        /* A' productions */
        printf("%c' -> ", nonTerminal);

        for (i = 0; i < n; i++)
        {
            if (production[i][prefixLen] == '\0')
                printf("epsilon");
            else
                printf("%s", &production[i][prefixLen]);

            if (i < n - 1)
                printf(" | ");
        }

        printf("\n");
    }

    return 0;
}
