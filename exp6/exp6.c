#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char str[])
{
    char keywords[][20] = {
        "auto", "break", "case", "char", "const",
        "continue", "default", "do", "double", "else",
        "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return",
        "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };

    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int isValidIdentifier(char str[])
{
    int i;

    // First character must be alphabet or underscore
    if (!(isalpha(str[0]) || str[0] == '_'))
        return 0;

    // Remaining characters
    for (i = 1; str[i] != '\0'; i++)
    {
        if (!(isalnum(str[i]) || str[i] == '_'))
            return 0;
    }

    // Check whether it is a keyword
    if (isKeyword(str))
        return 0;

    return 1;
}

int main()
{
    char identifier[100];

    printf("Enter an identifier: ");
    scanf("%99s", identifier);

    if (isValidIdentifier(identifier))
        printf("%s is a VALID identifier.\n", identifier);
    else
        printf("%s is an INVALID identifier.\n", identifier);

    return 0;
}
