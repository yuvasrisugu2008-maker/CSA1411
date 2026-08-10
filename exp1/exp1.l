#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '%' || ch == '=' || ch == '<' || ch == '>' ||
            ch == '!');
}

int main()
{
    char str[200];
    int i = 0;

    printf("Enter an expression: ");
    fgets(str, sizeof(str), stdin);

    printf("\nLexical Analysis:\n");
    printf("-----------------------------\n");

    while (str[i] != '\0')
    {
        /* Ignore spaces */
        if (isspace(str[i]))
        {
            i++;
        }

        /* Identifier */
        else if (isalpha(str[i]) || str[i] == '_')
        {
            char token[50];
            int j = 0;

            while (isalnum(str[i]) || str[i] == '_')
            {
                token[j++] = str[i++];
            }

            token[j] = '\0';

            printf("%-15s : Identifier\n", token);
        }

        /* Constant */
        else if (isdigit(str[i]))
        {
            char token[50];
            int j = 0;

            while (isdigit(str[i]) || str[i] == '.')
            {
                token[j++] = str[i++];
            }

            token[j] = '\0';

            printf("%-15s : Constant\n", token);
        }

        /* Operators */
        else if (isOperator(str[i]))
        {
            char op[3];

            op[0] = str[i];
            op[1] = '\0';

            /* Check for two-character operators */
            if ((str[i] == '=' && str[i + 1] == '=') ||
                (str[i] == '!' && str[i + 1] == '=') ||
                (str[i] == '<' && str[i + 1] == '=') ||
                (str[i] == '>' && str[i + 1] == '='))
            {
                op[1] = str[i + 1];
                op[2] = '\0';
                i += 2;
            }
            else
            {
                i++;
            }

            printf("%-15s : Operator\n", op);
        }

        /* Other symbols */
        else
        {
            printf("%-15c : Special Symbol\n", str[i]);
            i++;
        }
    }

    return 0;
}
