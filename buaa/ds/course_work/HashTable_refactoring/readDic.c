#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "defs.h"
#include "read.h"
#include "hashtable.h"

char bufferDic[DICCHARTOTAL];

struct DataItem hashArrayDic[DICBUCKETSIZE + EXTRASIZE];

int dicCollision, dicWordSize;

void O3 readDic()
{
    FILE *dic = fopen("dictionary.txt", "r");
    int lSize = getSize(dic);
    fread(bufferDic, 1, lSize, dic);
    bufferDic[lSize] = '\0';

    int i, j, ch;
    unsigned hashCode;
    for (i = 0, j = 0, hashCode = 0; i < lSize; i++) {
        while (isalpha(ch = bufferDic[i])) {
            i++;
            j++;
            hashCode = hashCode * SEED + ch;
        }
        bufferDic[i] = '\0';
        
        if (j) {
            insertHashDic(bufferDic + i - j, hashCode);
            #ifdef DEBUG
            dicWordSize++;
            #endif
            hashCode = j = 0;
        }
    }
}

inline O3 INLINE void insertHashDic(char word[], unsigned hashArrayIndex)
{
    hashArrayIndex ^= (hashArrayIndex >> (32 - DICBUCKETBITSIZE));
    hashArrayIndex &= (DICBUCKETSIZE - 1);

    #if 1
    register struct DataItem *p = hashArrayDic + hashArrayIndex;
    while (p->value)
        p += STEP;
    *p = (struct DataItem){word, 1};
    #endif

    #if 0
    while (hashArrayDic[hashArrayIndex].value) {
        hashArrayIndex += 13;
        hashArrayIndex &= (DICBUCKETSIZE - 1);;
    }
    hashArrayDic[hashArrayIndex] = (struct DataItem){word, 1};
    #endif
}

#if 1
inline O3 INLINE int searchHashDic(char word[], register unsigned hashArrayIndex)
{
    // register struct DataItem *p = hashArrayDic;
    hashArrayIndex ^= (hashArrayIndex >> (32 - DICBUCKETBITSIZE));
    hashArrayIndex &= (DICBUCKETSIZE - 1);
    #if 1
    register struct DataItem *p = hashArrayDic + hashArrayIndex;
    while (p->value) {
        if (!strcmp(p->key, word))
            return p->value;
        p += STEP;

        #ifdef DEBUG
        dicCollision++;
        #endif
    }
    return -1;
    #endif
    #if 0
    while (hashArrayDic[hashArrayIndex].value) {
        if (!strcmp(hashArrayDic[hashArrayIndex].key, word))
            return hashArrayDic[hashArrayIndex].value;
        hashArrayIndex += 13;
        #ifdef DEBUG
        collision++;
        #endif
        hashArrayIndex &= (DICBUCKETSIZE - 1);
    }
    return -1;
    #endif
}
#endif