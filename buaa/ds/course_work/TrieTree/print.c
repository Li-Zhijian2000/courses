#include "defs.h"
#include "print.h"

struct PrintNode printNode[MISSINGWORD];
static int printNodeNum = 1;

static int bucket[MISSINGWORD];
static int bucketSum[MISSINGWORD];
static int printOrder[MISSINGWORD];

static int posi[WORDNUM], next[WORDNUM];
static int posiNum = 1;

static int stack[WORDNUM];

inline int newPrintNode()
{
    return printNodeNum++;
}

inline void update(int printNodeIndex, int listKey)
{
    printNode[printNodeIndex].count++;

    posi[posiNum] = listKey;
    next[posiNum] = printNode[printNodeIndex].posiList;
    printNode[printNodeIndex].posiList = posiNum;
    posiNum++;
}

inline void setPrintNodeWordAndOrder(int i, char *p)
{
    strcpy(printNode[i].word, p);
    printOrder[printNodeNum - 1 - bucketSum[printNode[i].count]--] = i;
}

inline void bucketSort()
{
    int i, sum;
    for (i = 1; i < printNodeNum; i++) {
        bucket[printNode[i].count]++;
    }
    for (i = 1, sum = 0; i < printNodeNum; i++) {
        sum += bucket[i];
        bucketSum[i] = sum;
    }
}

void printPrintNode(FILE *out)
{
    int i, cnt, list;
    for (i = 0, cnt = 0; i < printNodeNum - 1; i++) {
        struct PrintNode *p = &printNode[printOrder[i]];
        fprintf(out, "%s %d ", p->word, p->count);
        list = p->posiList;

        while (list) {
            stack[cnt++] = posi[list];
            list = next[list];
        }

        while (cnt)
            fprintf(out, "%d ", stack[--cnt]);
        fprintf(out, "\n");
    }
}


