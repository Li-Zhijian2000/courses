#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defs.h"
#include "read.h"
#include "hashtable.h"

char bufferDic[DICCHARTOTAL];

static struct DataItem hashArrayDic[DICBUCKETSIZE];

extern int collision;

inline void readDic()
{
    FILE *dic = fopen("dictionary.txt", "r");
    int lSize = getSize(dic);
    fread(bufferDic, 1, lSize, dic);
    bufferDic[lSize] = '\0';

    int i, j;
    for (i = 0, j = 0; i < lSize; i++) {
        while (isalpha(bufferDic[i])) {
            i++;
            j++;
        }
        bufferDic[i] = '\0';
        
        if (j) {
            insertHashDic(bufferDic + i - j, j);
            j = 0;
        }
    }
}

inline void insertHashDic(char word[], int len)
{
    int hashArrayIndex = stringToInt(word, len);
    hashArrayIndex ^= (hashArrayIndex >> (32 - DICBUCKETBITSIZE));
    hashArrayIndex &= (DICBUCKETSIZE - 1);

    while (hashArrayDic[hashArrayIndex].value) {
        hashArrayIndex++;
        collision++;
        hashArrayIndex &= (DICBUCKETSIZE - 1);;
    }

    hashArrayDic[hashArrayIndex] = (struct DataItem){word, 1};
}
inline int searchHashDic(char word[], int len)
{
    int hashArrayIndex = stringToInt(word, len);
    hashArrayIndex ^= (hashArrayIndex >> (32 - DICBUCKETBITSIZE));
    hashArrayIndex &= (DICBUCKETSIZE - 1);

    while (hashArrayDic[hashArrayIndex].value) {
        if (!strcmp(hashArrayDic[hashArrayIndex].key, word))
            return hashArrayDic[hashArrayIndex].value;
        hashArrayIndex++;
        collision++;
        hashArrayIndex &= (DICBUCKETSIZE - 1);
    }
    return -1;
}