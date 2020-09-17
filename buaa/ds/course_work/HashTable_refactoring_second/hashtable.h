#include <stdio.h>
#include "defs.h"
struct DataItem {
    char *key;
    int value;
};

struct DataItem *searchHash(struct DataItem * hashArray, char *word, unsigned hashArrayIndex, 
    unsigned BUCKETBITSIZE, unsigned BUCKETSIZE);
struct DataItem *insertHash(struct DataItem * hashArray, char *word, unsigned hashArrayIndex, 
    unsigned BUCKETBITSIZE, unsigned BUCKETSIZE);