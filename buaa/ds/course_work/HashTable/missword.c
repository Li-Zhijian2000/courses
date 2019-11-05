#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "missword.h"

struct MissWord missWord[MISSWORDNUM];
static int missWordSize;

static int posiList[MISSWORDTOTAL];
static int posiListNext[MISSWORDTOTAL];
static int postListSize;

static int stack[MISSWORDTOTAL];
static int stackSize;

static char bufferMiss[MISSCHARTOTAL];
static int bufferMissSize;

inline int newMissWord()
{
    missWord[missWordSize].posiListHead = -1;
    return missWordSize++;
}

inline void updateMissWord(int index, int position) {
    missWord[index].count++;

    posiList[postListSize] = position;
    posiListNext[postListSize] = missWord[index].posiListHead;
    missWord[index].posiListHead = postListSize;
    postListSize++;
}

inline void setMissWordName(int index, char word[])
{
    missWord[index].word = word;
}

static inline int missWordComp(const void *lhs, const void *rhs)
{
    struct MissWord *a = (struct MissWord *)lhs, *b = (struct MissWord *)rhs;
    return (a->count != b->count) ? -(a->count - b->count) : strcmp(a->word, b->word);
}
inline void quickSort()
{
    qsort(missWord, missWordSize, sizeof(missWord[0]), missWordComp);
}

static inline void _print_int(int x)
{
    bufferMiss[bufferMissSize++] = ' ';
    int stack_int[8], stack_intSize = 0;
    while (x) {
        stack_int[stack_intSize++] = x % 10;
        x /= 10;
    }
    while (stack_intSize)
        bufferMiss[bufferMissSize++] = stack_int[--stack_intSize] + '0';
}
void printMissWord()
{
    FILE *miss = fopen("misspelling.txt", "w");
    int i, list;
    struct MissWord *item;
    for (i = 0; i < missWordSize; i++) {
        item = &missWord[i];

        // fprintf(miss, "%s %d ", item->word, item->count);
        strcpy(bufferMiss + bufferMissSize, item->word);
        bufferMissSize += strlen(item->word);
        _print_int(item->count);

        list = item->posiListHead;

        while (list != -1) {
            stack[stackSize++] = posiList[list];
            list = posiListNext[list];
        }

        while (stackSize) {
            // fprintf(miss, "%d ", stack[--stackSize]);
            _print_int(stack[--stackSize]);
        }
            
        // fprintf(miss, "\n");
        bufferMiss[bufferMissSize++] = '\n';
    }
    fwrite(bufferMiss, 1, bufferMissSize, miss);
}