#include <stdio.h>

int main()
{
    char ch;
    int whitespace = 0;
    int newline = 0;

    printf("Enter the text:\n");
    printf("Press Ctrl+Z and Enter to stop input.\n\n");

    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ' || ch == '\t')
        {
            whitespace++;
        }
        else if (ch == '\n')
        {
            newline++;
        }
    }

    printf("\nNumber of whitespaces: %d\n", whitespace);
    printf("Number of newline characters: %d\n", newline);

    return 0;
}
