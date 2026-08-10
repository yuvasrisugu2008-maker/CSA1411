#include <stdio.h>

int main()
{
    char op;

    printf("Enter an arithmetic operator (+, -, *, /): ");
    scanf("%c", &op);

    if (op == '+')
        printf("Valid Operator: Addition (+)\n");
    else if (op == '-')
        printf("Valid Operator: Subtraction (-)\n");
    else if (op == '*')
        printf("Valid Operator: Multiplication (*)\n");
    else if (op == '/')
        printf("Valid Operator: Division (/)\n");
    else
        printf("Invalid Operator\n");

    return 0;
}
