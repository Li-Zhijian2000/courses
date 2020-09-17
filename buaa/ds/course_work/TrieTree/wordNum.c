#include <stdio.h>
#include "defs.h"
#include "Trie.h"
#include "read.h"
#include "print.h"

#define DEBUG

#ifdef DEBUG
#include <time.h>
#define time(start, end) ((double)(end - start) / CLOCKS_PER_SEC)
#endif
int main()
{   
    #ifdef DEBUG
    clock_t start, read, find, preTra, end;
    start = clock();
    #endif
    FILE *in = fopen("dictionary.txt", "r"), *article = fopen("article.txt", "r"), *out = fopen("misspelling.txt", "w");

    Trie dictionaryTrie = initial();
    char line[WORDSIZE];
    while (fscanf(in, "%s", line) != EOF) {
        insertDic(dictionaryTrie, line);
    }
    #ifdef DEBUG
    read = clock();
    #endif
    Trie missingTrie = initial();
    int p, printNodeNum;
    while ((p = getWord(line, article)) != -1) {
        if (!search(dictionaryTrie, line)) {
            printNodeNum = insertMiss(missingTrie, line);
            update(printNodeNum, p);
        }
    }

    #ifdef DEBUG
    find = clock();
    #endif
    bucketSort();

    char str[WORDSIZE];
    triePreorder(missingTrie, str, 0);
    #ifdef DEBUG
    preTra = clock();
    #endif
    printPrintNode(out);
    #ifdef DEBUG
    end = clock();
    printf("%-15s%8lf    %4.2lf%%\n", "read_time:", time(start, read), time(start, read)/time(start, end) * 100);
    printf("%-15s%8lf    %4.2lf%%\n", "find_time:", time(read, find), time(read, find)/time(start, end) * 100);
    printf("%-15s%8lf    %4.2lf%%\n", "traval_time:", time(find, preTra), time(find, preTra)/time(start, end) * 100);
    printf("%-15s%8lf    %4.2lf%%\n", "print_time:", time(preTra, end), time(preTra, end)/time(start, end) * 100);
    printf("%-15s%8lf\n", "all:", time(start, end));
    #endif
    return 0;

}

