#include <stdio.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char filename[100];
    char ch;

    int characters = 0;
    int words = 0;
    int lines = 0;
    int inWord = 0;

    printf("Enter the file name: ");
    scanf("%s", filename);

    /* Open file */
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Unable to open the file.\n");
        return 1;
    }

    /* Read the file character by character */
    while ((ch = fgetc(fp)) != EOF)
    {
        characters++;

        /* Count lines */
        if (ch == '\n')
        {
            lines++;
        }

        /* Count words */
        if (isspace(ch))
        {
            inWord = 0;
        }
        else
        {
            if (inWord == 0)
            {
                words++;
                inWord = 1;
            }
        }
    }

    /* If file has characters but no newline at the end */
    if (characters > 0)
    {
        lines++;
    }

    fclose(fp);

    printf("\n----- File Statistics -----\n");
    printf("Number of Characters : %d\n", characters);
    printf("Number of Words      : %d\n", words);
    printf("Number of Lines      : %d\n", lines);

    return 0;
}
