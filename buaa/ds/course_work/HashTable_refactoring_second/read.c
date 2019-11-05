#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defs.h"
#include "read.h"
#include "hashtable.h"
#include "missword.h"

char bufferDic[DICCHARTOTAL], bufferArt[ARTCHARTOTAL];;

struct DataItem hashArrayDic[DICBUCKETSIZE + EXTRASIZE], hashArrayMiss[MISSBUCKETSIZE + EXTRASIZE];

int dicWordSize;

O3 
    void readDic() 
{
    int lSize = readFile("dictionary.txt", bufferDic);

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
            insertHash(hashArrayDic, bufferDic + i - j, hashCode, DICBUCKETBITSIZE, DICBUCKETSIZE);
            #ifdef DEBUG
            dicWordSize++;
            #endif
            hashCode = j = 0;
        }
    }
}


O3 
    void readArt() 
{
    int lSize = readFile("article.txt", bufferArt);
    
    int i, j, ch, missWordIndex;
    unsigned hashCode;
    char *word;
    struct DataItem *dicPtr, *missPtr;
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
            missPtr = searchHash(hashArrayMiss, word, hashCode, MISSBUCKETBITSIZE, MISSBUCKETSIZE);
            if (missPtr->value) {
                updateMissWord(missPtr->value, i - j);
            }
            else {
                dicPtr = searchHash(hashArrayDic, word, hashCode, DICBUCKETBITSIZE, DICBUCKETSIZE);
                if (!dicPtr->value) {
                    int missWordIndex = newMissWord();
                    *missPtr = (struct DataItem){word, missWordIndex};
                    setMissWordName(missWordIndex, word);
                    updateMissWord(missWordIndex, i - j);
                }
            }
            hashCode = j = 0;
            #endif
            #if 0
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

inline O3 INLINE 
    int getSize(FILE *file) 
{
    fseek(file, 0, SEEK_END);
    int lSize = ftell(file);
    rewind(file);
    return lSize;
}
inline O3 INLINE 
    int readFile(char *fileName, char *buffer)  
{
    FILE *art = fopen(fileName, "r");
    int lSize = getSize(art);
    fread(buffer, 1, lSize, art);
    buffer[lSize] = '\0';
    return lSize;
}
