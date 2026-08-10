#include <stdio.h>
#include <string.h>

int main()
{
    char nonTerminal;
    char alpha[10][50], beta[10][50];
    int nAlpha, nBeta;
    int i;

    printf("Enter the non-terminal: ");
    scanf(" %c", &nonTerminal);

    printf("Enter number of left recursive productions (alpha): ");
    scanf("%d", &nAlpha);

    printf("Enter alpha productions:\n");
    for (i = 0; i < nAlpha; i++)
    {
        scanf("%s", alpha[i]);
    }

    printf("Enter number of non-left recursive productions (beta): ");
    scanf("%d", &nBeta);

    printf("Enter beta productions:\n");
    for (i = 0; i < nBeta; i++)
    {
        scanf("%s", beta[i]);
    }

    printf("\nGrammar after eliminating left recursion:\n");

    /* A -> beta A' */
    for (i = 0; i < nBeta; i++)
    {
        printf("%c -> %s%c'\n", nonTerminal, beta[i], nonTerminal);
    }

    /* A' -> alpha A' */
    for (i = 0; i < nAlpha; i++)
    {
        printf("%c' -> %s%c' | ", nonTerminal, alpha[i], nonTerminal);
    }

    /* Epsilon */
    printf("epsilon\n");

    return 0;
}
