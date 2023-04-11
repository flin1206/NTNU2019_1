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

void printHelp(void);


struct option long_options[] =
    {
        {"bytes", no_argument, NULL, 'b'},
        {"kilo", no_argument, NULL, 1},
        {"mega", no_argument, NULL, 2},
        {"seconds", required_argument, NULL, 's'},
        {"count", required_argument, NULL, 'c'},
        {"help", no_argument, NULL, 3},
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
    uint32_t c = 0;
    uint32_t index = 0, optByte = 0, optKilo = 0, optMega = 0, optSeconds = 0, optCount = 0, optHelp = 0;
    long int count = 1, second = 0;

    if (argc == 1)
        optKilo = 1;
    while ((c = getopt_long(argc, argv, "bs:c:", long_options, &index)) != -1)
    {
        // printf("index: %d\n", index);
        switch (c)
        {
        case 'b':
            // printf("option: -b\n");
            optByte = 1;
            break;
        case 1:
            // printf("option: --kilo\n");
            optKilo = 1;
            break;
        case 2:
            // printf("option: --mega\n");
            optMega = 1;
            break;
        case 's':
            // printf("option: -s, %s\n", optarg);
            optSeconds = 1;
            second = atol(optarg);
            break;
        case 'c':
            // printf("option: -c, %s\n", optarg);
            optCount = 1;
            count = atol(optarg);
            break;
        case 3:
            // printf("option: --help\n");
            optHelp = 1;
            break;
        case '?':
            // printf("option: ?\n");
            break;
        default:
            printf("option: --kilo\n");
            optKilo = 1;
            break;
        }
    }
    if (optByte == 0 && optMega == 0)
        optKilo = 1;

    if (optHelp)
    {
        printHelp();
        return 0;
    }
    char buf[64] = {'\0'};
    FILE *Stream;
    double MemFree_info = 0, MemTotal_info = 0, MemAvailable_info = 0;

    while (count > 0)
    {
        Stream = popen("cat /proc/meminfo | grep MemTotal | awk {'print $2'}", "r");
        fread(buf, sizeof(char), sizeof(buf), Stream);
        MemTotal_info = atol(buf);
        pclose(Stream);
        Stream = popen("cat /proc/meminfo | grep MemAvailable | awk {'print $2'}", "r");
        fread(buf, sizeof(char), sizeof(buf), Stream);
        MemAvailable_info = atol(buf);
        pclose(Stream);

        double ratio = 0;

        ratio = MemAvailable_info * 100 / MemTotal_info;
        if (optByte)
        {
            printf("Available: %.lf B (%.2lf%%)\n", MemAvailable_info*1024, ratio);
        }
        if (optKilo)
        {
            printf("Available: %.lf KB (%.2lf%%)\n", MemAvailable_info, ratio);
        }
        if (optMega)
        {
            printf("Available: %.lf MB (%.2lf%%)\n", MemAvailable_info/1024, ratio);
        }
        sleep(second);

        count--;
    }

    return 0;
}

void printHelp(void)
{
    printf("Usage:\n    hw0501 [options]\nOptions:\n -b, --bytes         show output in bytes\n     --kilo          show output in kilobytes (default)\n     --mega          show output in megabytes\n -s N, --seconds N   repeat printing every N seconds\n -c N, --count N     repeat printing N times , then exit\n     --help          display this help and exit\n");
}
