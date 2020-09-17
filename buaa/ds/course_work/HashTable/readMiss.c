#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defs.h"
#include "read.h"
#include "hashtable.h"
#include "missword.h"

char bufferArt[ARTCHARTOTAL];

static struct DataItem hashArrayMiss[MISSBUCKETSIZE];

extern int collision;

void readArt()
{
    FILE *art = fopen("article1.txt", "r");
    int lSize = getSize(art);
    fread(bufferArt, 1, lSize, art);
    bufferArt[lSize] = '\0';
    
    int i, j, missWordIndex;
    char *word;
    for (i = 0, j = 0; i < lSize; i++) {
        while (isalpha(bufferArt[i])) {
            bufferArt[i] = tolower(bufferArt[i]);
            i++;
            j++;
        }
        bufferArt[i] = '\0';

        if (j) {
            word = bufferArt + i - j;
            if (searchHashDic(word, j) == -1) {
                missWordIndex = insertHashMiss(word, j);
                updateMissWord(missWordIndex, i - j);
            }
            j = 0;
        }
    }
}

inline int insertHashMiss(char word[], int len)
{
    unsigned hashArrayIndex = stringToInt(word, len);
    hashArrayIndex ^= (hashArrayIndex >> (32 - MISSBUCKETBITSIZE));
    hashArrayIndex &= (MISSBUCKETSIZE - 1);

    while (hashArrayMiss[hashArrayIndex].key) {
        if (!strcmp(hashArrayMiss[hashArrayIndex].key, word))
            return hashArrayMiss[hashArrayIndex].value;
        hashArrayIndex++;
        collision++;
        hashArrayIndex &= (MISSBUCKETSIZE - 1);
    }

    int missWordIndex = newMissWord();
    hashArrayMiss[hashArrayIndex] = (struct DataItem){word, missWordIndex};

    setMissWordName(missWordIndex, word);
    
    return missWordIndex;
}

