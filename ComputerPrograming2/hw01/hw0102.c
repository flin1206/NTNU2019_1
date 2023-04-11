#include <stdio.h>
#include <ctype.h>
#include <string.h>

void replace( char ori_str[], char tar_str[], char rep_str[] );
void printWithColor(char ori_str[], char tar_str[]);
int strnicmp(char ori_str[], char tar_str[], int x);

int main()
{
    // prepare space for three string
    char firstString[270000] = {0};
    char secondString[100]= {0};
    char thirdString[100]= {0};

    // fgets the string and check validity 
    printf("Please enter the string:\n");
    fgets(firstString,270000,stdin);
    firstString[strlen(firstString)-1] = 0; 
    if(( strlen(firstString) > 4096 )||( strlen(firstString) == 0 ))
    {
        printf("error\n");
        return 0;
    }

    // fgets the string and check validity
    printf("Please enter the keyword:\n");
    fgets(secondString, 100, stdin);
    secondString[strlen(secondString) - 1] = '\0';
    if(strstr(firstString,secondString) == NULL)
    {
        printf("no coresponding input\n");
        return 0;
    }
    if(( strlen(secondString) > 64 )||( strlen(secondString) == 0 ))
    {
        printf("error\n");
        return 0;
    }

    // fgets the string and check validity
    printf("Please enter the new word:\n");
    fgets(thirdString,100,stdin);
    thirdString[strlen(thirdString) - 1] = '\0';
    if((strlen(thirdString)>64)||(strlen(thirdString) == 0 ))
    {
        printf("error\n");
        return 0;
    }

    // print the original string with color
    printf("Original:\n");
    printWithColor(firstString,secondString);
    // replace keywords with newwords
    replace(firstString,secondString,thirdString);
    printf("New:\n");
    printWithColor(firstString,thirdString);
    return 0;
}

void printWithColor(char ori_str[], char tar_str[])
{
    // declare length of string
    int ori_len = strlen(ori_str);
    int tar_len = strlen(tar_str);

    for(int i = 0; i < ori_len; i++)
    {
        // compare string per target_length
        char tmp[100];
        for(int j = 0; j < tar_len; j++)
        {
            tmp[j] = ori_str[i+j];
        }
        // when both string is same in case-insensitive condition
        if(strnicmp(tmp,tar_str,tar_len) == 1)
        {
            // print the word in color
            for(int j = i; j < i + tar_len;j++)
            {
                printf("\033[33m%c\033[m",ori_str[j]);
            }
            i = i + tar_len-1;
        }
        // else print the word
        else
        {
            printf("%c",ori_str[i]);
        }
    }
    printf("\n");
    return;
}

void replace( char ori_str[], char tar_str[], char rep_str[] )
{
    // declare the length of each string
    int ori_len = strlen(ori_str);
    int tar_len = strlen(tar_str);
    int rep_len = strlen(rep_str); 

    for(int i = 0 ; i < ori_len ; i++)
    {
        // compare string per target_length
        char tmp[100] = {0};
        char buffer[270000] = {0};
        for(int j = 0; j < tar_len ; j++)
        {
            tmp[j] = ori_str[i+j];
        }
        // when both string is same in case-insensitive condition 
        if(strnicmp(tmp,tar_str,tar_len) == 1)
        {
            // put new word in the buffer and the less original string after it
            for(int j = 0; j < rep_len; j++)
            {
                buffer[j] = rep_str[j];
            }
            for(int j = i + tar_len ; j < ori_len ; j++)
            {
                buffer[rep_len+j-i-tar_len] = ori_str[j];
            }
            // make original string from key word to end become 0
            for(int j = i; j < ori_len; j++)
            {
                ori_str[j] = '\0';
            }
            // combine the buffer after original string
            strcat(ori_str,buffer);
            ori_len = strlen(ori_str);
        }
    }
    return;
}

int strnicmp(char ori_str[], char tar_str[], int x)
{
    for(int i = 0; i < x ; i++)
    {
        // make each character become low and compare  
        if( tolower(ori_str[i]) != tolower(tar_str[i]) )
        {
            return 0;
        }
    }
    return 1;
}