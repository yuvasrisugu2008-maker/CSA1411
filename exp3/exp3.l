#include <stdio.h>
#include <string.h>

int main()
{
    char line[500];
    int i = 0;

    printf("Enter the source code.\n");
    printf("Enter END to stop.\n\n");

    while (1)
    {
        fgets(line, sizeof(line), stdin);

        /* Stop input */
        if (strncmp(line, "END", 3) == 0)
            break;

        /* Ignore blank lines */
        if (line[0] == '\n')
            continue;

        /* Ignore single-line comments */
        if (line[0] == '/' && line[1] == '/')
            continue;

        /* Process the line */
        while (line[i] != '\0')
        {
            /* Ignore spaces and tabs */
            if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            {
                i++;
                continue;
            }

            printf("%c", line[i]);
            i++;
        }

        i = 0;
    }

    printf("\n\nComments, spaces, tabs and new lines are ignored.\n");

    return 0;
}
