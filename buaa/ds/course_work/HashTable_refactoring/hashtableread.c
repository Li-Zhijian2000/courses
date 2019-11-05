#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "read.h"
#if 0
inline O3 INLINE unsigned stringToInt(register char *key)
{   
    register unsigned h = 0, c, seed = 13131;
    /*
    while (c = *key++)
        h = ((h << 27) | (h >> 5)) + c;
    
    */
    while (c = *key++)
        h = h * seed + c;
    
    return h;
}
#endif
inline int getSize(FILE *file)
{
    fseek(file, 0, SEEK_END);
    int lSize = ftell(file);
    rewind(file);
    return lSize;
}
