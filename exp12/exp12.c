#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0;

/* Function declarations */
int E();
int Eprime();
int T();
int Tprime();
int F();

/* E -> T E' */
int E()
{
    if (T())
        return Eprime();

    return 0;
}

/* E' -> + T E' | epsilon */
int Eprime()
{
    if (input[pos] == '+')
    {
        pos++;

        if (T())
            return Eprime();

        return 0;
    }

    return 1;   // epsilon
}

/* T -> F T' */
int T()
{
    if (F())
        return Tprime();

    return 0;
}

/* T' -> * F T' | epsilon */
int Tprime()
{
    if (input[pos] == '*')
    {
        pos++;

        if (F())
            return Tprime();

        return 0;
    }

    return 1;   // epsilon
}

/* F -> (E) | id */
int F()
{
    /* Identifier */
    if (isalpha(input[pos]))
    {
        pos++;

        while (isalnum(input[pos]))
            pos++;

        return 1;
    }

    /* Parenthesized expression */
    if (input[pos] == '(')
    {
        pos++;

        if (E() && input[pos] == ')')
        {
            pos++;
            return 1;
        }

        return 0;
    }

    return 0;
}

int main()
{
    printf("Enter the expression: ");
    scanf("%s", input);

    if (E() && input[pos] == '\0')
        printf("String is ACCEPTED.\n");
    else
        printf("String is REJECTED.\n");

    return 0;
}
