#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#define keywordNumInC 44
#define keywordNumInCpp 84
#define keywordNumInJava 51
#define keywordNumInJS 38
#define keywordNumInRust 53
void printWithColor(char ori_str[], char *tar_str[], int tar_strNum)
{
    // declare length of string
    int tmpStr[10000] = {0}, tmpCom[10000] = {0};
    int ori_len = strlen(ori_str);
    int *printInColor = calloc(sizeof(int), ori_len);
    int tar_strLen[tar_strNum];
    for (int i = 0; i < tar_strNum; i++)
    {
        tar_strLen[i] = strlen(tar_str[i]);
    }
    int checkStr = 0, checkCom = 0, checkStr2 = 0;
    for (int i = 0; i < ori_len - 1; i++)
    {

        if ((ori_str[i] == '/') && (ori_str[i + 1] == '/'))
        {
            checkCom = 1;
        }
        if (checkCom == 1)
        {
            tmpCom[i] = 1;
        }
    }
    for (int i = 0; i < ori_len; i++)
    {
        if ((ori_str[i] == '\"') && (checkStr == 0))
            checkStr = 1;
        else if ((ori_str[i] == '\"') && (checkStr == 1))
            checkStr = 0;
        if ((ori_str[i] == '<') && (checkStr2 == 0))
            checkStr2 = 1;
        else if ((ori_str[i] == '<') && (checkStr2 == 1))
            checkStr2 = 0;

        if ((checkStr == 1) || (checkStr2 == 1))
            tmpStr[i] = 1;
    }

    for (int i = 0; i < ori_len; i++)
    {
        for (int k = 0; k < tar_strNum; k++)
        {
            // compare string per target_length
            char tmp[100];
            for (int j = 0; j < tar_strLen[k]; j++)
            {
                tmp[j] = ori_str[i + j];
            }

            if (strncmp(tmp, tar_str[k], tar_strLen[k]) == 0)
            {
                // print the word in color
                if (isalnum(ori_str[i + tar_strLen[k]]))
                {
                    continue;
                }
                else
                {
                    for (int j = i; j < i + tar_strLen[k]; j++)
                    {
                        printInColor[j] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < ori_len; i++)
    {
        if ((printInColor[i] == 1) && (tmpCom[i] == 0) && (tmpStr[i] == 0))
        {
            printf("\033[33m%c\033[m", ori_str[i]);
        }
        else
        {
            printf("%c", ori_str[i]);
        }
    }
    return;
}

struct option long_options[] =
    {
        {"linenum", 0, NULL, 'n'},
        {"color", 0, NULL, 'c'},
        {"language", 1, NULL, 'l'},
        {0, 0, 0, 0},
};

char *keywordInC[keywordNumInC] = {
    "auto", "break", "case", "char",
    "const", "continue", "default", "do",
    "double", "else", "enum", "extern",
    "float", "for", "goto", "if",
    "inline", "int", "long", "register",
    "restrict", "return", "short", "signed",
    "sizeof", "static", "struct", "switch",
    "typedef", "union", "unsigned", "void",
    "volatile", "while", "_Alignas", "_Alignof",
    "_Atomic", "_Bool", "_Complex", "_Generic",
    "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local"};
char *keywordInCPP[keywordNumInCpp] = {
    "alignas", "alignof", "asm", "auto",
    "bool", "break", "case", "catch",
    "char", "char16_t", "char32_t", "class",
    "const", "constexpr", "const_cast", "continue",
    "decltype", "default", "delete", "do",
    "double", "dynamic_cast", "else", "enum",
    "explicit", "export", "extern", "false",
    "float", "for", "friend", "goto",
    "if", "inline", "int", "long",
    "mutable", "namespace", "new", "noexcept",
    "nullptr", "operator", "private", "protected",
    "public", "register", "reinterpret_cast", "return",
    "short", "signed", "sizeof", "static",
    "static_assert", "static_cast", "struct", "switch",
    "template", "this", "thread_local", "throw",
    "true", "try", "typedef", "typeid",
    "typename", "union", "unsigned", "using",
    "virtual", "void", "volatile", "wchar_t",
    "while", "and", "and_eq", "bitand",
    "bitor", "compl", "not", "not_eq",
    "or", "or_eq", "xor", "xor_eq"};
char *keywordInJava[keywordNumInJava] = {
    "abstract", "assert", "boolean", "break",
    "byte", "case", "catch", "char",
    "class", "const", "continue", "default",
    "do", "double", "else", "enum",
    "extends", "final", "finally", "float",
    "for", "if", "goto", "implements",
    "import", "instanceof", "int", "interface",
    "long", "native", "new", "package",
    "private", "protected", "public", "return",
    "short", "static", "strictfp", "super",
    "switch", "synchronized", "this", "throw",
    "throws", "transient", "try", "void",
    "volatile", "while", "_"};
char *keywordInJS[keywordNumInJS] = {
    "await", "break", "case", "catch",
    "class", "const", "continue", "debugger",
    "default", "delete", "do", "else",
    "enum", "export", "extends", "false",
    "finally", "for", "function", "if",
    "import", "in", "instanceof", "new",
    "null", "return", "super", "switch",
    "this", "throw", "true", "try",
    "typeof", "var", "void", "while",
    "with", "yield"};
char *keywordInRust[keywordNumInRust] = {
    "as", "break", "const", "continue",
    "crate", "else", "enum", "extern",
    "false", "fn", "for", "if",
    "impl", "in", "let", "loop",
    "match", "mod", "move", "mut",
    "pub", "ref", "return", "self",
    "Self", "static", "struct", "super",
    "trait", "true", "type", "unsafe",
    "use", "where", "while", "async",
    "await", "dyn", "abstract", "become",
    "box", "do", "final", "macro",
    "override", "priv", "typeof", "unsized",
    "virtual", "yield", "try", "union",
    "'static"};
int main(int argc, char *argv[])
{
    // getopt_long
    int32_t c = 0, optN = 0, optC = 0, optL = 0;
    int32_t index = 0;
    FILE *pFile = NULL;
    char fileName[1000];
    strcpy(fileName, argv[argc - 1]);
    if ((pFile = fopen(fileName, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    while ((c = getopt_long(argc, argv, "ncl:", long_options, &index)) != -1)
    {
        // printf("index: %d\n", index);
        switch (c)
        {
        case 'n':
            // printf("option: -n\n");
            optN = 1;
            break;
        case 'c':
            // printf("option: -c\n");
            optC = 1;
            break;
        case 'l':
            // printf("option: -l %s\n", optarg);
            if (strcmp(optarg, "C++") == 0)
                optL = 1;
            else if (strcmp(optarg, "Java") == 0)
                optL = 2;
            else if (strcmp(optarg, "JS") == 0)
                optL = 3;
            else if (strcmp(optarg, "Rust") == 0)
                optL = 4;
            break;
        case '?':
            printf("option: ?\n");
            break;
        default:
            printf("option: unknown\n");
            break;
        }
    }

    while (!feof(pFile))
    {
        int i = 0;
        char tmp[30000] = {0};
        if (optN > 0)
        {
            printf("%d", optN);
            optN++;
        }
        while (1)
        {
            tmp[i] = fgetc(pFile);
            if (feof(pFile))
            {
                tmp[i] = 0;
                break;
            }
            if (tmp[i] == '\n')
                break;
            i++;
        }
        if (optC > 0)
        {
            switch (optL)
            {
            case 1:
                printWithColor(tmp, keywordInCPP, keywordNumInCpp);
                break;
            case 2:
                printWithColor(tmp, keywordInJava, keywordNumInJava);
                break;
            case 3:
                printWithColor(tmp, keywordInJS, keywordNumInJS);
                break;
            case 4:
                printWithColor(tmp, keywordInRust, keywordNumInRust);
                break;
            default:
                printWithColor(tmp, keywordInC, keywordNumInC);
                break;
            }
        }
        else
            printf("%s", tmp);
    }

    return 0;
}