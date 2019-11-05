#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

struct PrintNode {
    int count;
    int posiList;
    char word[WORDSIZE];
};

int newPrintNode();
void update(int, int);
void printPrintNode(FILE *);
void bucketSort();
void setPrintNodeWordAndOrder(int i, char *);
