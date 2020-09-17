#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "hashtable.h"
#include "read.h"
#include "missword.h"

#include <time.h>
#define time(start, end) ((double)(end - start) / CLOCKS_PER_SEC)
extern int dicCollision, dicWordSize, missCollision, missWordSize;

O3 int main() 
{
    clock_t start, read, find, sort, end;
    
    start = clock();

    readDic();

    read = clock();

    readArt();
    
    find = clock();

    quickSort();

    sort = clock();

    printMissWord();

    end = clock();
    printf("%-15s%8lf    %4.2lf%%\n", "read_time:", time(start, read), time(start, read)/time(start, end) * 100);
    printf("%-15s%8lf    %4.2lf%%\n", "find_time:", time(read, find), time(read, find)/time(start, end) * 100);
    printf("%-15s%8lf    %4.2lf%%\n", "sort_time:", time(find, sort), time(find, sort)/time(start, end) * 100);
    printf("%-15s%8lf    %4.2lf%%\n", "print_time:", time(sort, end), time(sort, end)/time(start, end) * 100);
    printf("%-15s%8lf\n", "all_time:", time(start, end));
    printf("%-15s%-8d%-15s%-8d\n", "dicCollision", dicCollision, "missCollison", missCollision);
    printf("%-15s%-8d%-15s%-8d\n", "dicHashSize:", dicWordSize, "missHashSize:", missWordSize - 1);
    return 0;
}
