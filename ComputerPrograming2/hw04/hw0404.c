#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#define HP_OFFSET (62)
#define WRIST_OFFSET (64)
#define SMART_OFFSET (66)
#define TEMP_OFFSET (68)
#define CHARM_OFFSET (70)
#define ETHIC_OFFSET (72)
#define BELIEF_OFFSET (74)
#define GUILT_OFFSET (76)
#define FEEL_OFFSET (78)
#define TIRED_OFFSET (80)

#define FIGHT_SKILL_OFFSET (92)
#define ATTACK_SKILL_OFFSET (94)
#define DEFEND_SKILL_OFFSET (96)
#define MAGIC_SKILL_OFFSET (98)
#define MAGIC_ABILITY_SKILL_OFFSET (100)
#define MAGIC_DEFEND_SKILL_OFFSET (102)

#define POLITE_OFFSET (104)
#define ART_OFFSET (106)
#define TALK_OFFSET (108)
#define COOK_OFFSET (110)
#define CLEAN_OFFSET (112)
#define KISS_OFFSET (114)

#define WARRIOR_RATE_OFFSET (84)
#define MAGIC_RATE_OFFSET (86)
#define SOCIAL_RATE_OFFSET (88)
#define HOUSEWORK_RATE_OFFSET (90)

#define MONEY_OFFSET (176)
#define RELATION_OFFSET (238)
#define HEIGHT_OFFSET (210)
#define WEIGHT_OFFSET (212)
#define BREAST_OFFSET (214)
#define WAIST_OFFSET (216)
#define HIPS_OFFSET (218)

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

int main()
{
    int32_t fd = 0;
    int32_t choice = 0;
    char fileName[256] = {0};

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

    while (1)
    {
        uint16_t *pHp = (uint16_t *)(_pFile + HP_OFFSET);
        uint16_t *pWr = (uint16_t *)(_pFile + WRIST_OFFSET);
        uint16_t *pSm = (uint16_t *)(_pFile + SMART_OFFSET);
        uint16_t *pTm = (uint16_t *)(_pFile + TEMP_OFFSET);
        uint16_t *pCh = (uint16_t *)(_pFile + CHARM_OFFSET);
        uint16_t *pEt = (uint16_t *)(_pFile + ETHIC_OFFSET);
        uint16_t *pBe = (uint16_t *)(_pFile + BELIEF_OFFSET);
        uint16_t *pGu = (uint16_t *)(_pFile + GUILT_OFFSET);
        uint16_t *pFe = (uint16_t *)(_pFile + FEEL_OFFSET);
        uint16_t *pTi = (uint16_t *)(_pFile + TIRED_OFFSET);
        printf("-----------------------------------------------------------\n");
        printf("chart1:\n");
        printf(" 1. HP: %u\n", *pHp);
        printf(" 2. WRIST: %u\n", *pWr);
        printf(" 3. Smart: %u\n", *pSm);
        printf(" 4. Tmperate: %u\n", *pTm);
        printf(" 5. Charm: %u\n", *pCh);
        printf(" 6. Ethic: %u\n", *pEt);
        printf(" 7. Belief: %u\n", *pBe);
        printf(" 8. Guilt: %u\n", *pGu);
        printf(" 9. Feel: %u\n", *pFe);
        printf("10. Tired: %u\n", *pTi);

        printf("-----------------------------------------------------------\n");
        uint16_t *pComSki = (uint16_t *)(_pFile + FIGHT_SKILL_OFFSET);
        uint16_t *pAtkSki = (uint16_t *)(_pFile + ATTACK_SKILL_OFFSET);
        uint16_t *pDefSki = (uint16_t *)(_pFile + DEFEND_SKILL_OFFSET);
        uint16_t *pMagSki = (uint16_t *)(_pFile + MAGIC_SKILL_OFFSET);
        uint16_t *pMagAbiSki = (uint16_t *)(_pFile + MAGIC_ABILITY_SKILL_OFFSET);
        uint16_t *pMaDefSki = (uint16_t *)(_pFile + MAGIC_DEFEND_SKILL_OFFSET);
        printf("chart2:\n");
        printf(" 1.COMBAT SKILL: %u\n", *pComSki);
        printf(" 2.ATTACK SKILL: %u\n", *pAtkSki);
        printf(" 3.DEFEND SKILL: %u\n", *pDefSki);
        printf(" 4.MAGIC SKILL: %u\n", *pMagSki);
        printf(" 5.MAGIC ABILITY SKILL: %u\n", *pMagAbiSki);
        printf(" 6.MAGIC DEFEND SKILL: %u\n", *pMaDefSki);

        printf("-----------------------------------------------------------\n");
        uint16_t *pWarRat = (uint16_t *)(_pFile + WARRIOR_RATE_OFFSET);
        uint16_t *pMagRat = (uint16_t *)(_pFile + MAGIC_RATE_OFFSET);
        uint16_t *pSocRat = (uint16_t *)(_pFile + SOCIAL_RATE_OFFSET);
        uint16_t *pHouRat = (uint16_t *)(_pFile + HOUSEWORK_RATE_OFFSET);
        printf("chart3:\n");
        printf(" 1.WARRIOR RATE: %u\n", *pWarRat);
        printf(" 2.MAGIC RATE: %u\n", *pMagRat);
        printf(" 3.SOCIAL RATE: %u\n", *pSocRat);
        printf(" 4.HOUSEWORK RATE: %u\n", *pHouRat);

        printf("-----------------------------------------------------------\n");
        uint16_t *pPolite = (uint16_t *)(_pFile + POLITE_OFFSET);
        uint16_t *pArt = (uint16_t *)(_pFile + ART_OFFSET);
        uint16_t *pTalk = (uint16_t *)(_pFile + TALK_OFFSET);
        uint16_t *pCook = (uint16_t *)(_pFile + COOK_OFFSET);
        uint16_t *pClean = (uint16_t *)(_pFile + CLEAN_OFFSET);
        uint16_t *pSocial = (uint16_t *)(_pFile + KISS_OFFSET);
        printf("chart4:\n");
        printf(" 1.POLITE: %u\n", *pPolite);
        printf(" 2.ART: %u\n", *pArt);
        printf(" 3.TALK: %u\n", *pTalk);
        printf(" 4.COOK: %u\n", *pCook);
        printf(" 5.CLEAN: %u\n", *pClean);
        printf(" 6.SOCIAL: %u\n", *pSocial);

        printf("-----------------------------------------------------------\n");
        uint32_t *pMoney = (uint32_t *)(_pFile + MONEY_OFFSET);
        uint16_t *pRelation = (uint16_t *)(_pFile + RELATION_OFFSET);
        uint16_t *pHeight = (uint16_t *)(_pFile + HEIGHT_OFFSET);
        uint16_t *pWeight = (uint16_t *)(_pFile + WEIGHT_OFFSET);
        uint16_t *pBreast = (uint16_t *)(_pFile + BREAST_OFFSET);
        uint16_t *pWaist = (uint16_t *)(_pFile + WAIST_OFFSET);
        uint16_t *pHips = (uint16_t *)(_pFile + HIPS_OFFSET);

        printf("chart5:\n");
        printf(" 1.MONEY: %u\n", *pMoney);
        printf(" 2.RELATION: %u\n", *pRelation);
        printf(" 3.HEIGHT*100: %u\n", *pHeight);
        printf(" 4.WEIGHT*100: %u\n", *pWeight);
        printf(" 5.BREAST*100: %u\n", *pBreast);
        printf(" 6.WAIST*100: %u\n", *pWaist);
        printf(" 7.HIPS*100: %u\n", *pHips);


        printf("-----------------------------------------------------------\n");

        int modifyChartNum, modifyChoiceNum, modifyToNum;

        printf("modify chart:");
        scanf("%d", &modifyChartNum);
        printf("modify choice:");
        scanf("%d", &modifyChoiceNum);
        printf("modify num:");
        scanf("%d", &modifyToNum);

        switch (modifyChartNum)
        {
        case 1:
            switch (modifyChoiceNum)
            {
            case 1:
                *pHp = modifyToNum;
                break;
            case 2:
                *pWr = modifyToNum;
                break;
            case 3:
                *pSm = modifyToNum;
                break;
            case 4:
                *pTm = modifyToNum;
                break;
            case 5:
                *pCh = modifyToNum;
                break;
            case 6:
                *pEt = modifyToNum;
                break;
            case 7:
                *pBe = modifyToNum;
                break;
            case 8:
                *pGu = modifyToNum;
                break;
            case 9:
                *pFe = modifyToNum;
                break;
            case 10:
                *pTi = modifyToNum;
                break;
            default:
                break;
            }
            break;
        case 2:
            switch (modifyChoiceNum)
            {
            case 1:
                *pComSki = modifyToNum;
                break;
            case 2:
                *pAtkSki = modifyToNum;
                break;
            case 3:
                *pDefSki = modifyToNum;
                break;
            case 4:
                *pMagSki = modifyToNum;
                break;
            case 5:
                *pMagAbiSki = modifyToNum;
                break;
            case 6:
                *pMaDefSki = modifyToNum;
                break;
            default:
                break;
            }
            break;
        case 3:
            switch (modifyChoiceNum)
            {
            case 1:
                *pWarRat = modifyToNum;
                break;
            case 2:
                *pMagRat = modifyToNum;
                break;
            case 3:
                *pSocRat = modifyToNum;
                break;
            case 4:
                *pHouRat = modifyToNum;
                break;
            default:
                break;
            }
            break;
        case 4:
            switch (modifyChoiceNum)
            {
            case 1:
                *pPolite = modifyToNum;
                break;
            case 2:
                *pArt = modifyToNum;
                break;
            case 3:
                *pTalk = modifyToNum;
                break;
            case 4:
                *pCook = modifyToNum;
                break;
            case 5:
                *pClean = modifyToNum;
                break;
            case 6:
                *pSocial = modifyToNum;
                break;
            default:
                break;
            }
            break;
        case 5:
            switch (modifyChoiceNum)
            {
            case 1:
                *pMoney = modifyToNum;
                break;
            case 2:
                *pRelation = modifyToNum;
                break;
            case 3:
                *pHeight = modifyToNum;
                break;
            case 4:
                *pWeight = modifyToNum;
                break;
            case 5:
                *pBreast = modifyToNum;
                break;
            case 6:
                *pWaist = modifyToNum;
                break;
            case 7:
                *pHips = modifyToNum;
                break;
            default:
                break;
            }
            break;
        }
        char checkContinue[2];
        printf("anybutton: continue, 0: close ==> ");
        scanf("%s", checkContinue);

        if (checkContinue[0] == '0')
            break;
    }

    munmap(_pFile, fileSize);
    close(fd);

    return 0;
}
