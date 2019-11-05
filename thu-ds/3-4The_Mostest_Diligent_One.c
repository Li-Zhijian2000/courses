#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED 31
#define maxn 20000

typedef struct {
    char name[10];
    int count;
}DataItem;

DataItem hashTable[maxn];

unsigned max;

unsigned stringToInt(char *string)
{
    char c;
    unsigned h = 0;
    while (c = *string++) {
        h = h * SEED + c;
    }
    return h;
}
int main()
{
    int n;
    char name[10];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", name);
        unsigned index = stringToInt(name) % maxn;
        // printf("%u\n", index);
        while (hashTable[index].count) {
            if (!strcmp(hashTable[index].name, name)) {
                break;
            }
            index++;
            index %= maxn;
        }
        strcpy(hashTable[index].name, name);
        hashTable[index].count++;
        if (hashTable[index].count > hashTable[max].count) {
            max = index;
        }
    }
    printf("%s %d\n", hashTable[max].name, hashTable[max].count);
    return 0;
}