#include <stdio.h>
#include <string.h>

char stack[100];
char input[100];
int top = -1;
int i = 0;

/* Push symbol onto stack */
void push(char c)
{
    stack[++top] = c;
    stack[top + 1] = '\0';
}

/* Pop symbol from stack */
void pop()
{
    if (top >= 0)
    {
        stack[top] = '\0';
        top--;
    }
}

/* Display stack and remaining input */
void display()
{
    printf("\nStack\t\tInput\n");
    printf("%s\t\t%s\n", stack, &input[i]);
}

/* Get precedence */
int precedence(char c)
{
    if (c == '+' )
        return 1;

    if (c == '*')
        return 2;

    if (c == '(')
        return 0;

    return -1;
}

/* Check whether character is an operand */
int isOperand(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

/* Reduce the stack */
int reduce()
{
    /* E -> id */
    if (top >= 1 &&
        stack[top - 1] == 'i' &&
        stack[top] == 'd')
    {
        pop();
        pop();
        push('E');

        printf("Reduce: id -> E");
        return 1;
    }

    /* E -> (E) */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        pop();
        pop();
        pop();
        push('E');

        printf("Reduce: (E) -> E");
        return 1;
    }

    /* E -> E+E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'E')
    {
        pop();
        pop();
        pop();
        push('E');

        printf("Reduce: E+E -> E");
        return 1;
    }

    /* E -> E*E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        pop();
        pop();
        pop();
        push('E');

        printf("Reduce: E*E -> E");
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

    /* Add end marker */
    strcat(input, "$");

    printf("\nOPERATOR PRECEDENCE PARSING\n");
    printf("---------------------------\n");

    while (input[i] != '$')
    {
        /* Operand */
        if (isOperand(input[i]))
        {
            if (input[i] == 'i' && input[i + 1] == 'd')
            {
                push('i');
                push('d');
                i += 2;

                printf("\nShift: id");
            }
            else
            {
                push('i');
                i++;

                printf("\nShift: operand");
            }

            display();

            while (reduce())
            {
                display();
            }
        }

        /* Opening parenthesis */
        else if (input[i] == '(')
        {
            push(input[i]);
            i++;

            printf("\nShift: (");
            display();
        }

        /* Closing parenthesis */
        else if (input[i] == ')')
        {
            push(input[i]);
            i++;

            printf("\nShift: )");
            display();

            while (reduce())
            {
                display();
            }
        }

        /* Operators */
        else if (input[i] == '+' || input[i] == '*')
        {
            /*
             * Reduce according to operator precedence.
             * '*' has higher precedence than '+'.
             */
            while (top >= 2 &&
                   stack[top] == 'E' &&
                   (stack[top - 1] == '+' ||
                    stack[top - 1] == '*') &&
                   precedence(stack[top - 1]) >=
                   precedence(input[i]))
            {
                if (!reduce())
                    break;

                display();
            }

            push(input[i]);

            printf("\nShift: %c", input[i]);
            i++;

            display();
        }

        else
        {
            printf("\nInvalid symbol: %c\n", input[i]);
            printf("Input string is REJECTED.\n");
            return 0;
        }
    }

    /* Final reductions */
    while (reduce())
    {
        display();
    }

    if (strcmp(stack, "E") == 0)
    {
        printf("\n\nInput string is ACCEPTED.\n");
    }
    else
    {
        printf("\n\nInput string is REJECTED.\n");
    }

    return 0;
}
