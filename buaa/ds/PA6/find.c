#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define maxn 4000
#define NHASH 3001

struct IndexTable {
    int lo;
    int hi;
};
struct IndexTable indexTable[30];

int hashTable[NHASH];
char *node[NHASH * 10];
int next[NHASH * 10];
int nodeSize = 1;

char *word[maxn];
int wordSize;

void initIndexTable();
void initHashTable();
int binarySearch(char *, int, int, int *);
int hashSearch(char *, int *);

int main()
{
    FILE *in = fopen("dictionary3000.txt", "r");
    assert(in != NULL);
    char line[30];
    while (~fscanf(in, "%s", line)) {
        char *p = malloc(strlen(line) + 1);
        strcpy(p, line);
        word[wordSize++] = p;
    }

    initIndexTable();
    initHashTable();

    int opt;
    char key[30];
    while (~scanf("%s%d", key, &opt)) {
        int count = 0, succ = 0;
        switch (opt) {
            case 1:
                while (count < wordSize && strcmp(word[count], key) < 0) {
                    count++;
                }
                if (!strcmp(word[count], key))
                    succ = 1;
                count++;
                break;
            case 2:
                succ = binarySearch(key, 0, wordSize, &count);
                break;
            case 3:
                succ = binarySearch(key, indexTable[key[0] - 'a'].lo, indexTable[key[0] - 'a'].hi, &count);
                break;
            case 4:
                succ = hashSearch(key, &count);
                break;
            default: break;
        }
        printf("%d %d\n", succ, count);
    }
    return 0;
}
static unsigned hashCode(char *str)
{
    unsigned h = 0;
    while (*str)
        h = 37 * h + *str++;
    return h % NHASH;
}
void initIndexTable()
{
    int i, j;
    word[wordSize] = "-end";
    for (i = 0; i < wordSize; i++) {
        if (word[i][0] == word[i+1][0])
            indexTable[word[i][0] - 'a'].hi++;
        else  {
            indexTable[word[i][0] - 'a'].hi = i + 1;
            if (i + 1 != wordSize)
                indexTable[word[i+1][0] - 'a'].lo = i + 1;
        }
        for (j = word[i][0] + 1; j < word[i+1][0]; j++)
            indexTable[j - 'a'] = (struct IndexTable){i+1, i+1};
    }
    // for (i = 0; i < 26; i++)
        // printf("%c %d %d\n", i + 'a', indexTable[i].lo, indexTable[i].hi);
}
void initHashTable()
{
    int i;
    for (i = 0; i < NHASH; i++) {
        hashTable[i] = nodeSize++;
    }
    for (i = 0; i < wordSize; i++) {
        unsigned index = hashCode(word[i]);
        int p = hashTable[index];
        while (next[p] && strcmp(node[next[p]], word[i]) <= 0)
            p = next[p];
        node[nodeSize] = word[i];
        next[nodeSize] = next[p];
        next[p] = nodeSize++;
    }
}
//[lo, hi)
int binarySearch(char *key, int lo, int hi, int *count)
{
    hi--;
    int mi;
    while (lo <= hi) {
        mi = (lo + hi) / 2;
        (*count)++;
        if (!strcmp(key, word[mi]))
            return 1;
        if (strcmp(key, word[mi]) < 0)
            hi = mi - 1;
        else lo = mi + 1;
    }
    return 0;
}
int hashSearch(char *key, int *count)
{
    unsigned index = hashCode(key);
    int p = next[hashTable[index]];
    while (p && strcmp(node[p], key) < 0) {
        p = next[p];
        (*count)++;
    }
    if (p) {
        (*count)++;
        if (!strcmp(node[p], key))
            return 1;
    }
    else return 0;
}
