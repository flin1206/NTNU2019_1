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
#include <curl/curl.h>
#include <assert.h>

struct option long_options[] =
    {
        {"country", 1, NULL, 'c'},
        {"start", 1, NULL, 's'},
        {"end", 1, NULL, 'e'},
        {"output", 1, NULL, 'o'},
        {"help", no_argument, NULL, 1},
        {0, 0, 0, 0},
};

void printHelp()
{
    printf("fin02:\n");
    printf("    -c, --country: the country name. default: Taiwan\n");
    printf("    -s, --start MM-DD-YYYY: the start date. default: 01-23-2020.\n");
    printf("    -e, --end MM-DD-YYYY: the end date. default: 12-31-2021.\n");
    printf("    -o, --output: output file name. default: output.csv\n");
    printf("    --help: This description\n");
}

int main(int argc, char *argv[])
{
    int32_t c = 0;
    int32_t index = 0, optC = 0, optS = 0, optE = 0, optO = 0;
    long width = 1024, height = 768;
    char outputName[1000] = {0}, countryName[1000] = {0}, startDate[100] = {0}, endDate[100] = {0};

    while ((c = getopt_long(argc, argv, "c:s:e:o:", long_options, &index)) != -1)
    {
        // printf("index: %d\n", index);
        switch (c)
        {
        case 'c':
            // printf("option: -w, %s\n", optarg);
            optC = 1;
            strcpy(countryName, optarg);
            break;
        case 's':
            // printf("option: -h, %s\n", optarg);
            optS = 1;
            strcpy(startDate, optarg);
            break;
        case 'e':
            // printf("option: -o, %s\n", optarg);
            optE = 1;
            strcpy(endDate, optarg);
            break;
        case 'o':
            // printf("option: -o, %s\n", optarg);
            optO = 1;
            strcpy(outputName, optarg);
            break;
        case 1:
            printHelp();
            return 0;
        default:
            printf("error\n");
            break;
        }
    }
    if (optC == 0)
        strcpy(countryName, "Taiwan");
    if (optS == 0)
        strcpy(startDate, "01-23-2020.");
    if (optE == 0)
        strcpy(endDate, "12-31-2021.");
    if (optO == 0)
        strcpy(outputName, "output.csv");

    CURL *curl;
    CURLcode res;

    char curlcommand[1000] = "https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_daily_reports/";

    curl = curl_easy_init();
    if (curl)
    {
        char command[1000] = "grep ";
        strcat(command, countryName);
        strcat(command, " tmp.txt | awk -F, '{ print $3,$4 }' | awk '{ print $1,$3 }'| awk 'BEGIN{ sum=0;} {sum+=$2} END{ print $1,sum }' >> ");
        strcat(command, outputName);
        //printf("%s\n",command);

        char tmpcommand[1000];
        strcpy(tmpcommand, curlcommand);
        strcat(tmpcommand, startDate);
        strcat(tmpcommand, "csv");
        // printf("%s\n",tmpcommand);

        curl_easy_setopt(curl, CURLOPT_URL, tmpcommand);

        FILE *pFile = fopen("tmp.txt", "w");
        assert(pFile);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, pFile);
        system(command);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        system("rm tmp.txt");

        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(pFile);
    }
    return 0;
}
