#include <stdio.h>
#include "defs.h"
struct DataItem {
    char *key;
    int value;
};

unsigned stringToInt(char *);

int searchHashDic(char *, unsigned);
void insertHashDic(char *, unsigned);

int insertHashMiss(char *, unsigned);

struct DataItem *searchHash(struct DataItme *, char *, unsigned, unsigned, unsigned);
