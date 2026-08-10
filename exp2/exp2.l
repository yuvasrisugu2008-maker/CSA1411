#include <stdio.h>
#include <string.h>

int main()
{
    char line[200];

    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);

    // Check for single-line comment
    if (line[0] == '/' && line[1] == '/')
    {
        printf("The given line is a COMMENT.\n");
    }
    // Check for multi-line comment starting
    else if (line[0] == '/' && line[1] == '*')
    {
        printf("The given line is a COMMENT.\n");
    }
    else
    {
        printf("The given line is NOT a COMMENT.\n");
    }

    return 0;
}
