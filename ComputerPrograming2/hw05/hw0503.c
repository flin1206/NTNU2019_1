// reference :
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

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static int mod_table[] = {0, 2, 1};
char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length);

unsigned char *base64_decode(unsigned char *code, long *de_lan);

struct option long_options[] =
    {
        {"enc", required_argument, NULL, 'e'},
        {"dec", required_argument, NULL, 'd'},
        {"output", required_argument, NULL, 'o'},
        {0, 0, 0, 0},
};

int main(int argc, char *argv[])
{
    // printf("argc: %d\n", argc);

    // for (int32_t i = 0; i < argc; i++)
    // {
    //     printf("argv[%d]: %s\n", i, argv[i]);
    // }

    // puts("---");

    // getopt_long

    int32_t c = 0;
    int32_t index = 0, optEncode = 0, optDecode = 0;
    char inputFileName[1000] = {0}, outputFileName[1000] = {0};

    while ((c = getopt_long(argc, argv, "e:d:o:", long_options, &index)) != -1)
    {
        // printf("index: %d\n", index);
        switch (c)
        {
        case 'e':
            // printf("option: -e, %s\n", optarg);
            strcpy(inputFileName, optarg);
            optEncode = 1;
            break;
        case 'd':
            // printf("option: -d, %s\n", optarg);
            strcpy(inputFileName, optarg);
            optDecode = 1;
            break;
        case 'o':
            //  printf("option: -o, %s\n", optarg);
            strcpy(outputFileName, optarg);
            break;
        default:
            // printf("option: unknown\n");
            break;
        }
    }

    FILE *pFile = NULL;
    if ((pFile = fopen(inputFileName, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    FILE *pFile2 = fopen(outputFileName, "w");

    if (optEncode == 1)
    {
        while (!feof(pFile))
        {
            char buf[4] = {0};
            size_t len = 0, en_len = 0;
            for (int i = 0; i < 3; i++)
            {
                char c = fgetc(pFile);
                if (feof(pFile))
                    break;
                buf[i] = c;
                // printf("%c", buf[i]);
                len++;
            }
            // printf("\nlen:%d\n", len);
            char *en_data = base64_encode(buf, len, &en_len);

            // printf("%d\n",en_len);
            if (en_len > 0)
                fwrite(en_data, 1, en_len, pFile2);
            free(en_data);
            // printf("%s", buf);
        }
    }
    else if (optDecode == 1)
    {
        while (!feof(pFile))
        {
            char buf[5] = {0};
            long len = 0;
            for (int i = 0; i < 4; i++)
            {
                char c = fgetc(pFile);
                if (feof(pFile))
                    break;
                buf[i] = c;
                // printf("%c", buf[i]);
            }
            // printf("\n");
            char *de_data = base64_decode(buf, &len);
            if (len > 0)
                fwrite(de_data, 1, len, pFile2);
            free(de_data);
        }
    }

    fclose(pFile);
    fclose(pFile2);

    return 0;
}

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length)
{

    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = malloc(*output_length);
    if (encoded_data == NULL)
        return NULL;

    for (int i = 0, j = 0; i < input_length;)
    {

        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}

unsigned char *base64_decode(unsigned char *code, long *de_lan)
{
    int table[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0,
                   63, 52, 53, 54, 55, 56, 57, 58,
                   59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0,
                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
                   13, 14, 15, 16, 17, 18, 19, 20, 21,
                   22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26,
                   27, 28, 29, 30, 31, 32, 33, 34, 35,
                   36, 37, 38, 39, 40, 41, 42, 43, 44,
                   45, 46, 47, 48, 49, 50, 51};
    long len;
    long ori_len;
    unsigned char *res;
    int i, j;

    len = strlen(code);
    if (strstr(code, "=="))
        ori_len = len / 4 * 3 - 2;
    else if (strstr(code, "="))
        ori_len = len / 4 * 3 - 1;
    else
        ori_len = len / 4 * 3;

    *de_lan = ori_len;
    res = malloc(sizeof(unsigned char) * ori_len + 1);
    res[ori_len] = '\0';

    for (i = 0, j = 0; i < len - 2; j += 3, i += 4)
    {
        res[j] = ((unsigned char)table[code[i]]) << 2 | (((unsigned char)table[code[i + 1]]) >> 4);
        res[j + 1] = (((unsigned char)table[code[i + 1]]) << 4) | (((unsigned char)table[code[i + 2]]) >> 2);
        res[j + 2] = (((unsigned char)table[code[i + 2]]) << 6) | ((unsigned char)table[code[i + 3]]);
    }
    return res;
}