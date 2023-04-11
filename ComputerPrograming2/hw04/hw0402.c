#include <math.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

struct option long_options[] =
    {
        {"source", 1, NULL, 'i'},
        {"struct", 1, NULL, 'n'},
        {"file", 1, NULL, 'p'},
        {0, 0, 0, 0},
};

struct _sStructure
{
    char structName[1000];
    int32_t structureSize;
} __attribute__((__packed__));

typedef struct _sStructure sStructure;

int main(int argc, char *argv[])
{
    // printf("argc: %d\n", argc);

    for (int32_t i = 0; i < argc; i++)
    {
        // printf("argv[%d]: %s\n", i, argv[i]);
    }

    // puts("---");

    // getopt_long

    int32_t c = 0, opti = 0, optn = 0, optp = 0;
    int32_t index = 0;
    char sourceName[1000] = {0};
    char structureName[1000] = {0};
    char fileName[1000] = {0};
    char fileHeaderName[1000] = {0};
    char fileCodeName[1000] = {0};
    sStructure StructureOnHeader[100];

    while ((c = getopt_long(argc, argv, "i:n:p:", long_options, &index)) != -1)
    {
        // printf("index: %d\n", index);
        switch (c)
        {
        case 'i':
            // printf("option: -i, %s\n", optarg);
            opti++;
            if (opti == 1)
                strcpy(sourceName, optarg);
            break;
        case 'n':
            // printf("option: -n, %s\n", optarg);
            optn++;
            if (optn == 1)
                strcpy(structureName, optarg);
            break;
        case 'p':
            // printf("option: -p, %s\n", optarg);
            optp++;
            if (optp == 1)
                strcpy(fileName, optarg);
            break;
        case '?':
            // printf("option: ?\n");
            break;
        default:
            // printf("option: unknown\n");
            break;
        }
    }
    if (optn == 0)
        strcpy(structureName, "test");
    if (optp == 0)
        strcpy(fileName, "test");
    strcat(fileHeaderName, fileName);
    strcat(fileHeaderName, ".h");
    strcat(fileCodeName, fileName);
    strcat(fileCodeName, ".c");

    FILE *pSource = NULL;
    FILE *pHeader = NULL;
    FILE *pCode = NULL;
    if ((pSource = fopen(sourceName, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    int countStruct = 0;
    while (!feof(pSource))
    {
        int i = 0;
        char tmp[3000] = {0};
        int lastCountStruct = countStruct;
        while (1)
        {
            tmp[i] = fgetc(pSource);
            if (feof(pSource))
            {
                tmp[i] = 0;
                break;
            }
            if (tmp[i] == '\n')
                break;
            i++;
        }
        // printf("%s", tmp);
        if (tmp[0] == '|')
        {
            int lastpos = 0;
            for (int i = 1; i < strlen(tmp); i++)
            {
                if (tmp[i] == '|')
                {
                    // printf("%d\n", (i - lastpos) / 2);
                    StructureOnHeader[countStruct].structureSize = (i - lastpos) / 2;
                    countStruct++;
                    lastpos = i;
                }
            }
            char tmp2[1000] = {0}, tmp3[1000] = {0};
            for (int i = 0, j = 1; j < strlen(tmp); j++)
            {
                if (tmp[j] != ' ')
                {
                    tmp2[i] = tmp[j];
                    i++;
                }
            }
            // printf("%s",tmp2);
            char *ptr = tmp2;
            int lenOfTmp2 = strlen(tmp2);
            for (int i = 0, j = lastCountStruct; i < lenOfTmp2; i++)
            {
                if (tmp2[i] == '|')
                {
                    tmp2[i] = 0;
                    strcpy(StructureOnHeader[j].structName, ptr);
                    // printf("%s %d\n",StructureOnHeader[j].structName,StructureOnHeader[j].structureSize);
                    ptr = tmp2 + i + 1;
                    j++;
                }
            }
        }
    }
    pclose(pSource);

    if ((pHeader = fopen(fileHeaderName, "w")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    char _sStructureName[1000] = "_s";
    char structNameToLower[1000] = {0};

    strcat(_sStructureName, structureName);
    strcpy(structNameToLower, structureName);
    for (int i = 0; i < strlen(structNameToLower); i++)
        structNameToLower[i] = tolower(structNameToLower[i]);
    fprintf(pHeader, "#pragma once\n\n#include <stdint.h>\n#include <stdio.h>\n#include <math.h>\n#include <string.h>\n#include <stdlib.h>\n\ntypedef struct %s\n{\n", _sStructureName);
    for (int i = 0; i < countStruct; i++)
    {
        int tmp = 0;
        if (StructureOnHeader[i].structureSize <= 8)
        {
            fprintf(pHeader, "   uint8_t ");
        }
        else if (StructureOnHeader[i].structureSize <= 16)
        {
            fprintf(pHeader, "   uint16_t ");
        }
/*         else if (StructureOnHeader[i].structureSize <= 24)
        {
            tmp = StructureOnHeader[i].structureSize / 8;
            if (StructureOnHeader[i].structureSize % 8 != 0)
                tmp++;
            fprintf(pHeader, "   uint8_t ");
        } */
        else if (StructureOnHeader[i].structureSize <= 32)
        {
            fprintf(pHeader, "   uint32_t ");
        }
        if (tmp == 0)
            fprintf(pHeader, "%s;\n", StructureOnHeader[i].structName);
        else
            fprintf(pHeader, "%s[%d];\n", StructureOnHeader[i].structName, tmp);
    }
    fprintf(pHeader, "}%s;\n\n", structureName);
    fprintf(pHeader, "%s * %s_init( void );\n", structureName, structNameToLower);
    fprintf(pHeader, "void %s_free( %s * );\n", structNameToLower, structureName);
    fprintf(pHeader, "int %s_encode( void *, const %s * );\n", structNameToLower, structureName);
    fprintf(pHeader, "int %s_decode( const void *, %s * );\n", structNameToLower, structureName);
    pclose(pHeader);

    if ((pCode = fopen(fileCodeName, "w")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    fprintf(pCode, "#include \"%s\"\n\n", fileHeaderName);

    fprintf(pCode, "%s * %s_init( void )\n{\n", structureName, structNameToLower);
    fprintf(pCode, "    %s *tmp = calloc(1,sizeof(%s));\n", structureName, structureName);
    for (int i = 0; i < countStruct; i++)
    {
        fprintf(pCode, "    tmp->%s = 0;\n", StructureOnHeader[i].structName);
    }
    fprintf(pCode, "    return tmp;\n");
    fprintf(pCode, "}\n\n");

    fprintf(pCode, "void %s_free( %s * name )\n{\n", structNameToLower, structureName);
    fprintf(pCode, "    free(name);\n");
    fprintf(pCode, "}\n\n");

    int countGroup = 0, max = 32, countSize = 0;
    for (int i = 0; i < countStruct; i++)
    {
        countSize += StructureOnHeader[i].structureSize;
        if (countSize == 32)
        {
            countSize = 0;
            countGroup++;
        }
    }
    fprintf(pCode, "int %s_encode( void * encodeTo, const %s * encodeFrom)\n{\n", structNameToLower, structureName);
    fprintf(pCode, "    uint32_t tmp[%d] = {0};\n", countGroup);
    int from = 0;
    countGroup = 0;
    for (int i = 0; i < countStruct; i++)
    {
        countSize += StructureOnHeader[i].structureSize;
        if (countSize == 32)
        {
            for (int j = i; j >= from; j--)
            {
                fprintf(pCode, "    tmp[%d] += encodeFrom->%s;\n", countGroup, StructureOnHeader[j].structName);
                if (j > from)
                    fprintf(pCode, "    tmp[%d] = tmp[%d] * pow(2,%d);\n", countGroup, countGroup, StructureOnHeader[j - 1].structureSize);
                else
                    continue;
            }
            countSize = 0;
            countGroup++;
            from = i + 1;
        }
    }
    fprintf(pCode, "    memcpy( encodeTo, tmp, %d );\n", countGroup * 4);
    fprintf(pCode, "    return 0;\n");
    fprintf(pCode, "}\n\n");

    fprintf(pCode, "int %s_decode( const void * decodeFrom, %s * decodeTo)\n{\n", structNameToLower, structureName);
    fprintf(pCode, "    uint32_t tmp = 0;\n");
    fprintf(pCode, "    uint32_t *ptr = ( uint32_t *)decodeFrom;\n");
    countGroup = 0;
    from = 0;
    for (int i = 0; i < countStruct; i++)
    {
        countSize += StructureOnHeader[i].structureSize;
        if (countSize == 32)
        {
            fprintf(pCode, "    memcpy( &tmp, ptr, 4);\n");
            for (int j = from; j <= i; j++)
            {

                fprintf(pCode, "    decodeTo->%s = tmp %% (uint32_t)pow( 2, %d);\n", StructureOnHeader[j].structName, StructureOnHeader[j].structureSize);
                if (j < i)
                    fprintf(pCode, "    tmp = tmp / %d;\n", (uint32_t)pow(2, StructureOnHeader[j].structureSize));
                else
                    continue;
            }
            countSize = 0;
            countGroup++;
            from = i + 1;
            fprintf(pCode, "    ptr = ptr + 1;\n");
        }
    }
    fprintf(pCode, "    return 0;\n");
    fprintf(pCode, "}\n\n");

    pclose(pCode);
    return 0;
}