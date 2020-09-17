#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "hashtable.h"
#include "read.h"
#include "missword.h"

#define DEBUG

#ifdef DEBUG
#include <time.h>
#define time(start, end) ((double)(end - start) / CLOCKS_PER_SEC)

int collision, dicSize, missSize;
#endif


int main()
{
    #ifdef DEBUG
    clock_t start, read, find, sort, end;
    start = clock();
    #endif

    readDic();

    #ifdef DEBUG
    read = clock();
    #endif

    readArt();
    
    #ifdef DEBUG
    find = clock();
    #endif

    quickSort();

    #ifdef DEBUG
    sort = clock();
    #endif
    printMissWord();

    #ifdef DEBUG
    end = clock();
    printf("%-15s%8lf    %4.2lf%%\n", "read_time:", time(start, read), time(start, read)/time(start, end) * 100);
    printf("%-15s%8lf    %4.2lf%%\n", "find_time:", time(read, find), time(read, find)/time(start, end) * 100);
    printf("%-15s%8lf    %4.2lf%%\n", "sort_time:", time(find, sort), time(find, sort)/time(start, end) * 100);
    printf("%-15s%8lf    %4.2lf%%\n", "print_time:", time(sort, end), time(sort, end)/time(start, end) * 100);
    printf("%-15s%8lf\n", "all_time:", time(start, end));
    printf("%d\n", collision);
    printf("%-15s%-8d%-15s%-8d\n", "dicHashSize:", dicSize, "missHashSize:", missSize);
    #endif

    return 0;
}
