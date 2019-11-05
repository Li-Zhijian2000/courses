#include <string.h>
#include <assert.h>
#include "defs.h"
#include "hashtable.h"

int dicCollision, missCollision;

inline O3 INLINE 
    struct DataItem *searchHash(struct DataItem * hashArray, char *word, unsigned hashArrayIndex, 
        unsigned BUCKETBITSIZE, unsigned BUCKETSIZE)
{   
    hashArrayIndex ^= hashArrayIndex >> (32 - BUCKETBITSIZE);
    hashArrayIndex &= BUCKETSIZE - 1;

    register struct DataItem *p = hashArray + hashArrayIndex;
    while (p->value) {
        if (!strcmp(p->key, word))
            return p;
        p += STEP;
        #ifdef DEBUG
        if (BUCKETBITSIZE == DICBUCKETBITSIZE)
            dicCollision++;
        else missCollision++;
        #endif
    }
    return p;
}
inline O3 INLINE 
    struct DataItem *insertHash(struct DataItem * hashArray, char *word, unsigned hashArrayIndex, 
        unsigned BUCKETBITSIZE, unsigned BUCKETSIZE)
{
    hashArrayIndex ^= hashArrayIndex >> (32 - BUCKETBITSIZE);
    hashArrayIndex &= BUCKETSIZE - 1;

    register struct DataItem *p = hashArray + hashArrayIndex;
    while (p->value)
        p += STEP;
    *p = (struct DataItem){word, 1};
}
