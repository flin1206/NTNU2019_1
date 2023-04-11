#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main()
{
    FILE *pFile = NULL;
    char fileName[32] = {0};
    char tmp[32] = {0};

    printf("Please enter the file name: ");

    if (fgets(fileName, sizeof(fileName), stdin) == NULL)
    {
        printf("Error!\n");
        return 0;
    }

    // Since fgets will include '\n', we need to remove this character.

    if (fileName[strlen(fileName) - 1] == '\n')
    {
        fileName[strlen(fileName) - 1] = 0;
    }
    else
    {
        // If the last byte is not '\n', we need to clean the input buffer.
        int32_t c = 0;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
    }

    if ((pFile = fopen(fileName, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    char account[32] = {0};
    char password[32] = {0};
    int32_t i = 1;
    while (1)
    {
        int32_t c = fgetc(pFile);
        if (c == '\n')
            i++;
        else if (c == EOF)
            break;
    }
    fclose(pFile);


    if ((pFile = fopen(fileName, "a")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    while (1)
    {
        printf("Please enter your account and password.\n");
        printf("The length of account and password cannot be over 31.\n");

        printf("Account: ");
        if (fgets(account, 32, stdin) == NULL)
        {
            break;
        }

        if (account[strlen(account) - 1] == '\n')
        {
            account[strlen(account) - 1] = 0;
        }
        else
        {
            int32_t c = 0;
            while ((c = fgetc(stdin)) != '\n' && c != EOF)
            {
            }
        }

        printf("Password: ");
        if (fgets(password, 32, stdin) == NULL)
        {
            break;
        }

        if (password[strlen(password) - 1] == '\n')
        {
            password[strlen(password) - 1] = 0;
        }
        else
        {
            int32_t c = 0;
            while ((c = fgetc(stdin)) != '\n' && c != EOF)
            {
            }
        }

        fprintf(pFile, "%02d %s/%s\n", i, account, password);
        i++;
    }
    fclose(pFile);

    return 0;
}