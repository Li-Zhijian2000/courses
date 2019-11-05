#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "defs.h"
#include "read.h"
#include "hashtable.h"
#include "missword.h"

char bufferArt[ARTCHARTOTAL];

struct DataItem hashArrayMiss[MISSBUCKETSIZE + EXTRASIZE];

int missCollision;

void O3 readArt()
{
    FILE *art = fopen("article.txt", "r");
    int lSize = getSize(art);
    fread(bufferArt, 1, lSize, art);
    bufferArt[lSize] = '\0';
    
    int i, j, ch, missWordIndex;
    unsigned hashCode;
    char *word;
    for (i = 0, j = 0, hashCode = 0; i < lSize; i++) {
        while (isalpha(bufferArt[i])) {
            ch = bufferArt[i] = tolower(bufferArt[i]);
            hashCode = hashCode * SEED + ch;
            i++;
            j++;
        }
        bufferArt[i] = '\0';

        if (j) {
            word = bufferArt + i - j;
            #if 1

            #endif
            #if 1
            if (searchHashDic(word, hashCode) == -1) {
                missWordIndex = insertHashMiss(word, hashCode);
                updateMissWord(missWordIndex, i - j);
                
                #ifdef DEBUG
                missCollision++;
                #endif
            }
            hashCode = j = 0;
            #endif
        }
    }
}

inline O3 INLINE int insertHashMiss(char word[], unsigned hashArrayIndex)
{
    hashArrayIndex ^= (hashArrayIndex >> (32 - MISSBUCKETBITSIZE));
    hashArrayIndex &= (MISSBUCKETSIZE - 1);

    while (hashArrayMiss[hashArrayIndex].key) {
        if (!strcmp(hashArrayMiss[hashArrayIndex].key, word))
            return hashArrayMiss[hashArrayIndex].value;
        hashArrayIndex += STEP;
        hashArrayIndex &= (MISSBUCKETSIZE - 1);
    }

    int missWordIndex = newMissWord();
    hashArrayMiss[hashArrayIndex] = (struct DataItem){word, missWordIndex};

    setMissWordName(missWordIndex, word);
    
    return missWordIndex;
}

