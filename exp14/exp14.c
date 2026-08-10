#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

/* Push symbol onto stack */
void push(char c)
{
    stack[++top] = c;
    stack[top + 1] = '\0';
}

/* Reduce the stack */
int reduce()
{
    /* id -> E */
    if (top >= 1 && stack[top - 1] == 'i' && stack[top] == 'd')
    {
        top -= 1;
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printf("Reduce: id -> E\n");
        return 1;
    }

    /* (E) -> E */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printf("Reduce: (E) -> E\n");
        return 1;
    }

    /* E+E -> E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printf("Reduce: E+E -> E\n");
        return 1;
    }

    /* E*E -> E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printf("Reduce: E*E -> E\n");
        return 1;
    }

    return 0;
}

int main()
{
    char input[100];
    int i = 0;

    printf("Grammar:\n");
    printf("E -> E+E | E*E | (E) | id\n\n");

    printf("Enter input string: ");
    scanf("%s", input);

    printf("\nSHIFT-REDUCE PARSING\n");
    printf("--------------------\n");

    while (input[i] != '\0')
    {
        /* Shift */
        push(input[i]);
        printf("Shift: %c\n", input[i]);
        i++;

        /* Try reductions */
        while (reduce())
        {
            printf("Stack: %s\n", stack);
        }
    }

    /* Final reduction */
    while (reduce())
    {
        printf("Stack: %s\n", stack);
    }

    if (strcmp(stack, "E") == 0)
        printf("\nInput string is ACCEPTED.\n");
    else
        printf("\nInput string is REJECTED.\n");

    return 0;
}
