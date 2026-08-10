#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;
int tempCount = 1;

/* Push character */
void push(char c)
{
    stack[++top] = c;
}

/* Pop character */
char pop()
{
    return stack[top--];
}

/* Return operator precedence */
int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;

    if (c == '*' || c == '/')
        return 2;

    return 0;
}

/* Convert infix expression to postfix */
void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++)
    {
        c = infix[i];

        if (isalnum(c))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            push(c);
        }
        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = pop();

            if (top != -1)
                pop();
        }
        else if (c == '+' || c == '-' ||
                 c == '*' || c == '/')
        {
            while (top != -1 &&
                   precedence(stack[top]) >= precedence(c))
            {
                postfix[j++] = pop();
            }

            push(c);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

/* Generate Three Address Code */
void generateTAC(char postfix[])
{
    char operandStack[100][20];
    int operandTop = -1;

    char op1[20], op2[20], temp[20];

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        if (isalnum(postfix[i]))
        {
            operandTop++;
            operandStack[operandTop][0] = postfix[i];
            operandStack[operandTop][1] = '\0';
        }
        else
        {
            strcpy(op2, operandStack[operandTop--]);
            strcpy(op1, operandStack[operandTop--]);

            sprintf(temp, "t%d", tempCount++);

            printf("%s = %s %c %s\n",
                   temp, op1, postfix[i], op2);

            operandTop++;
            strcpy(operandStack[operandTop], temp);
        }
    }

    printf("Result = %s\n", operandStack[operandTop]);
}

int main()
{
    char input[100];
    char lhs;
    char expression[100];
    char postfix[100];

    printf("Enter the assignment statement: ");
    scanf("%s", input);

    /* Find '=' */
    lhs = input[0];

    strcpy(expression, strchr(input, '=') + 1);

    /* Convert to postfix */
    infixToPostfix(expression, postfix);

    printf("\nThree Address Code:\n");
    printf("-------------------\n");

    generateTAC(postfix);

    printf("%c = t%d\n", lhs, tempCount - 1);

    return 0;
}
