#include <stdio.h>
#include <string.h>

#define MAX 50

struct Symbol
{
    char name[30];
    char type[20];
    char value[20];
};

struct Symbol table[MAX];
int count = 0;

/* Insert a symbol */
void insert()
{
    char name[30];

    printf("Enter symbol name: ");
    scanf("%s", name);

    /* Check for duplicate */
    for (int i = 0; i < count; i++)
    {
        if (strcmp(table[i].name, name) == 0)
        {
            printf("Symbol already exists!\n");
            return;
        }
    }

    if (count >= MAX)
    {
        printf("Symbol table is full!\n");
        return;
    }

    strcpy(table[count].name, name);

    printf("Enter data type: ");
    scanf("%s", table[count].type);

    printf("Enter value: ");
    scanf("%s", table[count].value);

    count++;

    printf("Symbol inserted successfully.\n");
}

/* Search a symbol */
void search()
{
    char name[30];

    printf("Enter symbol to search: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(table[i].name, name) == 0)
        {
            printf("\nSymbol found!\n");
            printf("Name  : %s\n", table[i].name);
            printf("Type  : %s\n", table[i].type);
            printf("Value : %s\n", table[i].value);
            return;
        }
    }

    printf("Symbol not found!\n");
}

/* Delete a symbol */
void deleteSymbol()
{
    char name[30];

    printf("Enter symbol to delete: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(table[i].name, name) == 0)
        {
            /* Shift remaining elements */
            for (int j = i; j < count - 1; j++)
            {
                table[j] = table[j + 1];
            }

            count--;

            printf("Symbol deleted successfully.\n");
            return;
        }
    }

    printf("Symbol not found!\n");
}

/* Display symbol table */
void display()
{
    if (count == 0)
    {
        printf("\nSymbol table is empty!\n");
        return;
    }

    printf("\n------------- SYMBOL TABLE -------------\n");
    printf("%-15s %-15s %-15s\n", "Name", "Type", "Value");
    printf("----------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-15s %-15s %-15s\n",
               table[i].name,
               table[i].type,
               table[i].value);
    }

    printf("----------------------------------------\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n===== SYMBOL TABLE =====\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insert();
                break;

            case 2:
                search();
                break;

            case 3:
                deleteSymbol();
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
