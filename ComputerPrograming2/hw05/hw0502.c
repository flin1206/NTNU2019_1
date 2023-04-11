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

void printGenre(uint8_t i);
void printHelp(void);
void delay(unsigned int secs);
uint8_t genreToInt(char *str);

uint64_t util_getFdSize(int fd)
{
    struct stat statbuf;

    if (fstat(fd, &statbuf) < 0)
    {
        close(fd);
        return -1;
    }

    return statbuf.st_size;
}

struct _sID3
{
    char TAG[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[28];
    char zeroByte;
    char track;
    char genre;
} __attribute__((__packed__));
typedef struct _sID3 sID3;

int main(int argc, char *argv[])
{
    char fileName[1000] = {0}, titleNew[30] = {0}, trackNew, artistNew[30] = {0}, albumNew[30] = {0}, yearNew[4] = {0}, commentNew[28] = {0}, genreNew[100] = {0};
    // printf("argc: %d\n", argc);

    // for (int32_t i = 0; i < argc; i++)
    // {
    //     printf("argv[%d]: %s\n", i, argv[i]);
    // }
    // puts("---");

    strcpy(fileName, argv[argc - 1]);
    int32_t c = 0;
    int32_t index = 0, optTitle = 0, optTrack = 0, optArtist = 0, optAlbum = 0, optYear = 0, optComment = 0, optGenre = 0, optList = 0, optDelete = 0, optHelp = 0;

    while ((c = getopt(argc, argv, "t:T:a:A:y:c:g:dhl")) != -1)
    {
        switch (c)
        {
        case 't':
            //printf("option: -t, %s\n", optarg);
            strncpy(titleNew, optarg, 30);
            optTitle = 1;
            break;
        case 'T':
            //printf("option: -T, %s\n", optarg);
            trackNew = atoi(optarg);
            optTrack = 1;
            break;
        case 'a':
            //printf("option: -a, %s\n", optarg);
            memcpy(artistNew, optarg, 30);
            optArtist = 1;
            break;
        case 'A':
            //printf("option: -A, %s\n", optarg);
            strncpy(albumNew, optarg, 30);
            optAlbum = 1;
            break;
        case 'y':
            //printf("option: -y, %s\n", optarg);
            strncpy(yearNew, optarg, 4);
            optYear = 1;
            break;
        case 'c':
            //printf("option: -c, %s\n", optarg);
            strncpy(commentNew, optarg, 28);
            optComment = 1;
            break;
        case 'g':
            //printf("option: -g, %s\n", optarg);
            strncpy(genreNew, optarg, 100);
            optGenre = 1;
            break;
        case 'l':
            //printf("option: -l\n");
            optList = 1;
            break;
        case 'd':
            //printf("option: -d\n");
            optDelete = 1;
            break;
        case 'h':
            //printf("option: -h\n");
            optHelp = 1;
            break;
        }
    }

    if (optHelp)
    {
        printHelp();
        return 0;
    }

    int32_t fd;

    fd = open(fileName, O_RDWR);
    // Open file descriptor
    if (fd == -1)
    {
        printf("Open file error!\n");
        return -1;
    }

    // MMAP

    char *_pFile = NULL;
    uint64_t fileSize = util_getFdSize(fd);
    _pFile = mmap(0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sID3 *ID3 = (sID3 *)(_pFile + fileSize - 128);

    if (optList)
    {
        if (strncmp(ID3->TAG, "TAG", 3)) // no tag
        {
            printf("TAG IS NOT EXIST\n");
            munmap(_pFile, fileSize);
            close(fd);
            return 0;
        }
        printf("%s:\n", fileName);
        printf("  Title  : ");
        for (int i = 0; i < sizeof(ID3->title); i++)
            printf("%c", ID3->title[i]);
        printf("\n");

        printf("  Artist: ");
        for (int i = 0; i < sizeof(ID3->artist); i++)
            printf("%c", ID3->artist[i]);
        printf("\n");

        printf("  Album  : ");
        for (int i = 0; i < sizeof(ID3->album); i++)
            printf("%c", ID3->album[i]);
        printf("\n");

        printf("  Year: ");
        for (int i = 0; i < sizeof(ID3->year); i++)
            printf("%c", ID3->year[i]);
        printf("\n");

        printGenre(ID3->genre);

        printf("  Comment: ");
        for (int i = 0; i < sizeof(ID3->comment); i++)
            printf("%c", ID3->comment[i]);
        printf("\n");

        printf("  Track  : %d\n", ID3->track);
        return 0;
    }

    if (optDelete)
    {
        if (strncmp(ID3->TAG, "TAG", 3)) // no tag
        {
            printf("TAG IS NOT EXIST\n");
            munmap(_pFile, fileSize);
            close(fd);
            return 0;
        }
        munmap(_pFile, fileSize);
        close(fd);

        FILE *fin, *ftp;
        fin = fopen(fileName, "r");
        ftp = fopen("tmp.txt", "w");

        for (uint64_t i = 0; i < fileSize - 128; i++)
        {
            char a;
            a = fgetc(fin);
            fputc(a, ftp);
        }

        fclose(fin);
        fclose(ftp);
        remove(fileName); //刪除原檔案

        rename("tmp.txt", fileName); //將臨時檔名改為原檔名
        return 0;
    }

    if (strncmp(ID3->TAG, "TAG", 3)) // no tag
    {
        munmap(_pFile, fileSize);
        close(fd);

        FILE *fin, *ftp;
        fin = fopen(fileName, "r");
        ftp = fopen("tmp.txt", "w");
        for (uint64_t i = 0; i < fileSize; i++)
        {
            char a;
            a = fgetc(fin);
            fputc(a, ftp);
        }

        sID3 defaultID3;
        memset(defaultID3.album, 0, sizeof(defaultID3.album));
        memset(defaultID3.artist, 0, sizeof(defaultID3.artist));
        memset(defaultID3.comment, 0, sizeof(defaultID3.comment));
        defaultID3.genre = 255;
        strncpy(defaultID3.TAG, "TAG", 3);
        memset(defaultID3.title, 0, sizeof(defaultID3.title));
        defaultID3.track = 0;
        memset(defaultID3.year, 0, sizeof(defaultID3.year));
        defaultID3.zeroByte = 0;

        if (optTitle)
            strncpy(defaultID3.title, titleNew, 30);

        if (optTrack)
            defaultID3.track = trackNew;

        if (optArtist)
            strncpy(defaultID3.artist, artistNew, 30);

        if (optAlbum)
            strncpy(defaultID3.album, albumNew, 30);

        if (optYear)
            strncpy(defaultID3.year, yearNew, 4);

        if (optComment)
            strncpy(defaultID3.comment, commentNew, 28);

        if (optGenre)
            defaultID3.genre = genreToInt(genreNew);

        fwrite(&defaultID3, sizeof(defaultID3), 1, ftp);

        fclose(fin);
        fclose(ftp);
        remove(fileName); //刪除原檔案
        rename("tmp.txt", fileName);
        return 0;
    }
    else
    {
        if (optTitle)
            strncpy(ID3->title, titleNew, 30);

        if (optTrack)
            ID3->track = trackNew;

        if (optArtist)
            strncpy(ID3->artist, artistNew, 30);

        if (optAlbum)
            strncpy(ID3->album, albumNew, 30);

        if (optYear)
            strncpy(ID3->year, yearNew, 4);

        if (optComment)
            strncpy(ID3->comment, commentNew, 28);

        if (optGenre)
        {
            ID3->genre = genreToInt(genreNew);
        }

        munmap(_pFile, fileSize);
        close(fd);
        return 0;
    }
}

void printHelp(void)
{
    printf("usage: hw0502 -[tTaAycg] \"value\" file1 [file2...]\n");
    printf("       hw0502 -d file1 [file2...]\n");
    printf("       hw0502 -l file1 [file2...]\n");
    printf("       hw0502 -h\n");
    printf(" -t   Modifies a Title tag\n");
    printf(" -T   Modifies a Track tag\n");
    printf(" -a   Modifies an Artist tag\n");
    printf(" -A   Modifies an Album tag\n");
    printf(" -y   Modifies a Year tag\n");
    printf(" -c   Modifies a Comment tag\n");
    printf(" -g   Modifies a Genre tag\n");
    printf(" -l   Lists an ID3 tag\n");
    printf(" -d   Deletes an ID3 tag\n");
    printf(" -h   Displays this help info\n");
}

void delay(unsigned int secs)
{
    unsigned int retTime = time(0) + secs;
    while (time(0) < retTime)
        ;
}

void printGenre(uint8_t i)
{
    printf("  Genre: ");
    switch (i)
    {
    case 0:
        printf("Blues");
        break;
    case 1:
        printf("Classic Rock");
        break;
    case 2:
        printf("Country");
        break;
    case 3:
        printf("Dance");
        break;
    case 4:
        printf("Disco");
        break;
    case 5:
        printf("Funk");
        break;
    case 6:
        printf("Grunge");
        break;
    case 7:
        printf("Hip-Hop");
        break;
    case 8:
        printf("Jazz");
        break;
    case 9:
        printf("Metal");
        break;
    case 10:
        printf("New Age");
        break;
    case 11:
        printf("Oldies");
        break;
    case 12:
        printf("Other");
        break;
    case 13:
        printf("Pop");
        break;
    case 14:
        printf("R&B");
        break;
    case 15:
        printf("Rap");
        break;
    case 16:
        printf("Reggae");
        break;
    case 17:
        printf("Rock");
        break;
    case 18:
        printf("Techno");
        break;
    case 19:
        printf("Industrial");
        break;
    case 20:
        printf("Alternative");
        break;
    case 21:
        printf("Ska");
        break;
    case 22:
        printf("Death Metal");
        break;
    case 23:
        printf("Pranks");
        break;
    case 24:
        printf("Soundtrack");
        break;
    case 25:
        printf("Euro-Techno");
        break;
    case 26:
        printf("Ambient");
        break;
    case 27:
        printf("Trip-Hop");
        break;
    case 28:
        printf("Vocal");
        break;
    case 29:
        printf("Jazz+Funk");
        break;
    case 30:
        printf("Fusion");
        break;
    case 31:
        printf("Trance");
        break;
    case 32:
        printf("Classical");
        break;
    case 33:
        printf("Instrumental");
        break;
    case 34:
        printf("Acid");
        break;
    case 35:
        printf("House");
        break;
    case 36:
        printf("Game");
        break;
    case 37:
        printf("Sound Clip");
        break;
    case 38:
        printf("Gospel");
        break;
    case 39:
        printf("Noise");
        break;
    case 40:
        printf("AlternRock");
        break;
    case 41:
        printf("Bass");
        break;
    case 42:
        printf("Soul");
        break;
    case 43:
        printf("Punk");
        break;
    case 44:
        printf("Space");
        break;
    case 45:
        printf("Meditative");
        break;
    case 46:
        printf("Instrumental Pop");
        break;
    case 47:
        printf("Instrumental Rock");
        break;
    case 48:
        printf("Ethnic");
        break;
    case 49:
        printf("Gothic");
        break;
    case 50:
        printf("Darkwave");
        break;
    case 51:
        printf("Techno-Industrial");
        break;
    case 52:
        printf("Electronic");
        break;
    case 53:
        printf("Pop-Folk");
        break;
    case 54:
        printf("Eurodance");
        break;
    case 55:
        printf("Dream");
        break;
    case 56:
        printf("Southern Rock");
        break;
    case 57:
        printf("Comedy");
        break;
    case 58:
        printf("Cult");
        break;
    case 59:
        printf("Gangsta");
        break;
    case 60:
        printf("Top 40");
        break;
    case 61:
        printf("Christian Rap");
        break;
    case 62:
        printf("Pop/Funk");
        break;
    case 63:
        printf("Jungle");
        break;
    case 64:
        printf("Native American");
        break;
    case 65:
        printf("Cabaret");
        break;
    case 66:
        printf("New Wave");
        break;
    case 67:
        printf("Psychadelic");
        break;
    case 68:
        printf("Rave");
        break;
    case 69:
        printf("Showtunes");
        break;
    case 70:
        printf("Trailer");
        break;
    case 71:
        printf("Lo-Fi");
        break;
    case 72:
        printf("Tribal");
        break;
    case 73:
        printf("Acid Punk");
        break;
    case 74:
        printf("Acid Jazz");
        break;
    case 75:
        printf("Polka");
        break;
    case 76:
        printf("Retro");
        break;
    case 77:
        printf("Musical");
        break;
    case 78:
        printf("Rock & Roll");
        break;
    case 79:
        printf("Hard Rock");
        break;
    case 80:
        printf("Folk");
        break;
    case 81:
        printf("Folk-Rock");
        break;
    case 82:
        printf("National Folk");
        break;
    case 83:
        printf("Swing");
        break;
    case 84:
        printf("Fast Fusion	");
        break;
    case 85:
        printf("Bebob");
        break;
    case 86:
        printf("Latin");
        break;
    case 87:
        printf("Revival");
        break;
    case 88:
        printf("Celtic");
        break;
    case 89:
        printf("Bluegrass");
        break;
    case 90:
        printf("Avantgarde");
        break;
    case 91:
        printf("Gothic Rock");
        break;
    case 92:
        printf("Progressive Rock");
        break;
    case 93:
        printf("Psychedelic Rock");
        break;
    case 94:
        printf("Symphonic Rock");
        break;
    case 95:
        printf("Slow Rock");
        break;
    case 96:
        printf("Big Band");
        break;
    case 97:
        printf("Chorus");
        break;
    case 98:
        printf("Easy Listening");
        break;
    case 99:
        printf("Acoustic");
        break;
    case 100:
        printf("Humour");
        break;
    case 101:
        printf("Speech");
        break;
    case 102:
        printf("Chanson");
        break;
    case 103:
        printf("Opera");
        break;
    case 104:
        printf("Chamber Music");
        break;
    case 105:
        printf("Sonata");
        break;
    case 106:
        printf("Symphony");
        break;
    case 107:
        printf("Booty Bass");
        break;
    case 108:
        printf("Primus");
        break;
    case 109:
        printf("Porn Groove");
        break;
    case 110:
        printf("Satire");
        break;
    case 111:
        printf("Slow Jam");
        break;
    case 112:
        printf("Club");
        break;
    case 113:
        printf("Tango");
        break;
    case 114:
        printf("Samba");
        break;
    case 115:
        printf("Folklore");
        break;
    case 116:
        printf("Ballad");
        break;
    case 117:
        printf("Power Ballad");
        break;
    case 118:
        printf("Rhythmic Soul");
        break;
    case 119:
        printf("Freestyle");
        break;
    case 120:
        printf("Duet");
        break;
    case 121:
        printf("Punk Rock");
        break;
    case 122:
        printf("Drum Solo");
        break;
    case 123:
        printf("A capella");
        break;
    case 124:
        printf("Euro-House");
        break;
    case 125:
        printf("Dance Hall");
        break;
    default:
        i = 255;
        printf("default");
        break;
    }

    printf(" (%u)\n", i);
}

uint8_t genreToInt(char *str)
{
    if (!strcmp(str, "Blues"))
        return 0;
    if (!strcmp(str, "Classic Rock"))
        return 1;
    if (!strcmp(str, "Country"))
        return 2;
    if (!strcmp(str, "Dance"))
        return 3;
    if (!strcmp(str, "Disco"))
        return 4;
    if (!strcmp(str, "Funk"))
        return 5;
    if (!strcmp(str, "Grunge"))
        return 6;
    if (!strcmp(str, "Hip-Hop"))
        return 7;
    if (!strcmp(str, "Jazz"))
        return 8;
    if (!strcmp(str, "Metal"))
        return 9;
    if (!strcmp(str, "New Age"))
        return 10;
    if (!strcmp(str, "Oldies"))
        return 11;
    if (!strcmp(str, "Other"))
        return 12;
    if (!strcmp(str, "Pop"))
        return 13;
    if (!strcmp(str, "R&B"))
        return 14;
    if (!strcmp(str, "Rap"))
        return 15;
    if (!strcmp(str, "Reggae"))
        return 16;
    if (!strcmp(str, "Rock"))
        return 17;
    if (!strcmp(str, "Techno"))
        return 18;
    if (!strcmp(str, "Industrial"))
        return 19;
    if (!strcmp(str, "Alternative"))
        return 20;
    if (!strcmp(str, "Ska"))
        return 21;
    if (!strcmp(str, "Death Metal"))
        return 22;
    if (!strcmp(str, "Pranks"))
        return 23;
    if (!strcmp(str, "Soundtrack"))
        return 24;
    if (!strcmp(str, "Euro-Techno"))
        return 25;
    if (!strcmp(str, "Ambient"))
        return 26;
    if (!strcmp(str, "Trip-Hop"))
        return 27;
    if (!strcmp(str, "Vocal"))
        return 28;
    if (!strcmp(str, "Jazz+Funk"))
        return 29;
    if (!strcmp(str, "Fusion"))
        return 30;
    if (!strcmp(str, "Trance"))
        return 31;
    if (!strcmp(str, "Classical"))
        return 32;
    if (!strcmp(str, "Instrumental"))
        return 33;
    if (!strcmp(str, "Acid"))
        return 34;
    if (!strcmp(str, "House"))
        return 35;
    if (!strcmp(str, "Game"))
        return 36;
    if (!strcmp(str, "Sound Clip"))
        return 37;
    if (!strcmp(str, "Gospel"))
        return 38;
    if (!strcmp(str, "Noise"))
        return 39;
    if (!strcmp(str, "AlternRock"))
        return 40;
    if (!strcmp(str, "Bass"))
        return 41;
    if (!strcmp(str, "Soul"))
        return 42;
    if (!strcmp(str, "Punk"))
        return 43;
    if (!strcmp(str, "Space"))
        return 44;
    if (!strcmp(str, "Meditative"))
        return 45;
    if (!strcmp(str, "Instrumental Pop"))
        return 46;
    if (!strcmp(str, "Instrumental Rock"))
        return 47;
    if (!strcmp(str, "Ethnic"))
        return 48;
    if (!strcmp(str, "Gothic"))
        return 49;
    if (!strcmp(str, "Darkwave"))
        return 50;
    if (!strcmp(str, "Techno-Industrial"))
        return 51;
    if (!strcmp(str, "Electronic"))
        return 52;
    if (!strcmp(str, "Pop-Folk"))
        return 53;
    if (!strcmp(str, "Eurodance"))
        return 54;
    if (!strcmp(str, "Dream"))
        return 55;
    if (!strcmp(str, "Southern Rock"))
        return 56;
    if (!strcmp(str, "Comedy"))
        return 57;
    if (!strcmp(str, "Cult"))
        return 58;
    if (!strcmp(str, "Gangsta"))
        return 59;
    if (!strcmp(str, "Top 40"))
        return 60;
    if (!strcmp(str, "Christian Rap"))
        return 61;
    if (!strcmp(str, "Pop/Funk"))
        return 62;
    if (!strcmp(str, "Jungle"))
        return 63;
    if (!strcmp(str, "Native American	"))
        return 64;
    if (!strcmp(str, "Cabaret"))
        return 65;
    if (!strcmp(str, "New Wave"))
        return 66;
    if (!strcmp(str, "Psychadelic	"))
        return 67;
    if (!strcmp(str, "Rave"))
        return 68;
    if (!strcmp(str, "Showtunes"))
        return 69;
    if (!strcmp(str, "Trailer"))
        return 70;
    if (!strcmp(str, "Lo-Fi"))
        return 71;
    if (!strcmp(str, "Tribal"))
        return 72;
    if (!strcmp(str, "Acid Punk"))
        return 73;
    if (!strcmp(str, "Acid Jazz"))
        return 74;
    if (!strcmp(str, "Polka"))
        return 75;
    if (!strcmp(str, "Retro"))
        return 76;
    if (!strcmp(str, "Musical"))
        return 77;
    if (!strcmp(str, "Rock & Roll"))
        return 78;
    if (!strcmp(str, "Hard Rock"))
        return 79;
    if (!strcmp(str, "Folk"))
        return 80;
    if (!strcmp(str, "Folk-Rock"))
        return 81;
    if (!strcmp(str, "National Folk"))
        return 82;
    if (!strcmp(str, "Swing"))
        return 83;
    if (!strcmp(str, "Fast Fusion	"))
        return 84;
    if (!strcmp(str, "Bebob"))
        return 85;
    if (!strcmp(str, "Latin"))
        return 86;
    if (!strcmp(str, "Revival"))
        return 87;
    if (!strcmp(str, "Celtic"))
        return 88;
    if (!strcmp(str, "Bluegrass"))
        return 89;
    if (!strcmp(str, "Avantgarde"))
        return 90;
    if (!strcmp(str, "Gothic Rock"))
        return 91;
    if (!strcmp(str, "Progressive Rock"))
        return 92;
    if (!strcmp(str, "Psychedelic Rock"))
        return 93;
    if (!strcmp(str, "Symphonic Rock"))
        return 94;
    if (!strcmp(str, "Slow Rock"))
        return 95;
    if (!strcmp(str, "Big Band"))
        return 96;
    if (!strcmp(str, "Chorus"))
        return 97;
    if (!strcmp(str, "Easy Listening	"))
        return 98;
    if (!strcmp(str, "Acoustic"))
        return 99;
    if (!strcmp(str, "Humour"))
        return 100;
    if (!strcmp(str, "Speech"))
        return 101;
    if (!strcmp(str, "Chanson"))
        return 102;
    if (!strcmp(str, "Opera"))
        return 103;
    if (!strcmp(str, "Chamber Music"))
        return 104;
    if (!strcmp(str, "Sonata"))
        return 105;
    if (!strcmp(str, "Symphony"))
        return 106;
    if (!strcmp(str, "Booty Bass"))
        return 107;
    if (!strcmp(str, "Primus"))
        return 108;
    if (!strcmp(str, "Porn Groove"))
        return 109;
    if (!strcmp(str, "Satire"))
        return 110;
    if (!strcmp(str, "Slow Jam"))
        return 111;
    if (!strcmp(str, "Club"))
        return 112;
    if (!strcmp(str, "Tango"))
        return 113;
    if (!strcmp(str, "Samba"))
        return 114;
    if (!strcmp(str, "Folklore"))
        return 115;
    if (!strcmp(str, "Ballad"))
        return 116;
    if (!strcmp(str, "Power Ballad"))
        return 117;
    if (!strcmp(str, "Rhythmic Soul"))
        return 118;
    if (!strcmp(str, "Freestyle"))
        return 119;
    if (!strcmp(str, "Duet"))
        return 120;
    if (!strcmp(str, "Punk Rock"))
        return 121;
    if (!strcmp(str, "Drum Solo"))
        return 122;
    if (!strcmp(str, "A capella"))
        return 123;
    if (!strcmp(str, "Euro-House"))
        return 124;
    if (!strcmp(str, "Dance Hall"))
        return 125;
    return 255;
}