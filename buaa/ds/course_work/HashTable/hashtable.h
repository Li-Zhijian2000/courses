#include <stdio.h>

struct DataItem {
    char *key;
    int value;
};

unsigned stringToInt(char *key, int);

int searchHashDic(char *, int);
void insertHashDic(char *, int);

int insertHashMiss(char *, int);


unsigned stringToInt(char *, int);
