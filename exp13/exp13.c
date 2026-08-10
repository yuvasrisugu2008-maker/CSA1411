#include <stdio.h>
#include <string.h>

char stack[100];
char input[100];
int top = -1;
int i = 0;

/* Display current stack and input */
void display()
{
    int j;

    printf("\nStack\t\tInput\n");
    printf("%s\t\t", stack);

    for (j = i; input[j] != '\0'; j++)
        printf("%c", input[j]);

    printf("\n");
}

/* Reduce the stack */
int reduce()
{
    /* id -> E */
    if (top >= 1 &&
        stack[top - 1] == 'i' &&
        stack[top] == 'd')
    {
        stack[top - 1] = 'E';
        stack[top] = '\0';
        top--;

        printf("REDUCE: id -> E");
        return 1;
    }

    /* (E) -> E */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        stack[top - 2] = 'E';
        stack[top - 1] = '\0';
        top -= 2;

        printf("REDUCE: (E) -> E");
        return 1;
    }

    /* E+E -> E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'E')
    {
        stack[top - 2] = 'E';
        stack[top - 1] = '\0';
        top -= 2;

        printf("REDUCE: E+E -> E");
        return 1;
    }

    /* E*E -> E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        stack[top - 2] = 'E';
        stack[top - 1] = '\0';
        top -= 2;

        printf("REDUCE: E*E -> E");
        return 1;
    }

    return 0;
}

int main()
{
    printf("Grammar:\n");
    printf("E -> E+E | E*E | (E) | id\n\n");

    printf("Enter input string: ");
    scanf("%s", input);

    printf("\nSHIFT-REDUCE PARSING\n");
    printf("--------------------\n");

    while (input[i] != '\0')
    {
        /* SHIFT */
        stack[++top] = input[i];
        stack[top + 1] = '\0';

        i++;

        printf("\nSHIFT");
        display();

        /* REDUCE as much as possible */
        while (reduce())
        {
            display();
        }
    }

    /* Final reductions */
    while (reduce())
    {
        display();
    }

    if (strcmp(stack, "E") == 0)
        printf("\n\nInput string is ACCEPTED.\n");
    else
        printf("\n\nInput string is REJECTED.\n");

    return 0;
}
