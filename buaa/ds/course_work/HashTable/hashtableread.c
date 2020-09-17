#include <stdio.h>
#include "hashtable.h"
#include "read.h"

inline unsigned stringToInt(char key[], int len)
{   
    unsigned h = 0, n, i;
    for (n = len, i = 0; i < n; i++) {
        h = (h << 27) ^ (h >> 5);
        h += key[i];
    }
    return h;
    
}

inline int getSize(FILE *file)
{
    fseek(file, 0, SEEK_END);
    int lSize = ftell(file);
    rewind(file);
    return lSize;
}
