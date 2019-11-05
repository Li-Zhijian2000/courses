#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
struct Node {
    int data;
    int next[ALPHASIZE];
};

typedef int Trie;

int initial();

void insertDic(Trie, char *);
int insertMiss(Trie, char *);

int search(Trie, char *);

void triePreorder(Trie, char *, int);

