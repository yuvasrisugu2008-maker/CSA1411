#include <stdio.h>
#include <string.h>

int main()
{
    int n, i;
    char lhs[20], op1[20], op2[20], op;
    char statement[100];

    printf("Enter number of three-address statements: ");
    scanf("%d", &n);

    printf("\nEnter Three Address Code:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%s", statement);

        /*
         * Check for assignment with operator:
         * t1=a+b
         */
        if (sscanf(statement, "%[^=]=%[^+*-/]%c%s",
                   lhs, op1, &op, op2) == 4)
        {
            printf("\n; %s\n", statement);

            printf("MOV R0, %s\n", op1);

            switch (op)
            {
                case '+':
                    printf("ADD R0, %s\n", op2);
                    break;

                case '-':
                    printf("SUB R0, %s\n", op2);
                    break;

                case '*':
                    printf("MUL R0, %s\n", op2);
                    break;

                case '/':
                    printf("DIV R0, %s\n", op2);
                    break;

                default:
                    printf("Invalid operator\n");
                    continue;
            }

            printf("MOV %s, R0\n", lhs);
        }
        else
        {
            /*
             * Simple assignment:
             * x=t1
             */
            if (sscanf(statement, "%[^=]=%s", lhs, op1) == 2)
            {
                printf("\n; %s\n", statement);
                printf("MOV R0, %s\n", op1);
                printf("MOV %s, R0\n", lhs);
            }
            else
            {
                printf("Invalid statement: %s\n", statement);
            }
        }
    }

    return 0;
}
