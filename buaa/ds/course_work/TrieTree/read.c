#include "read.h"
static int positionSize;

//read word from article.txt, 
//return initial position or return -1 if failed
inline int getWord(char word[], FILE *f)
{
    char ch;
    int initialPosi, i = 0;
    while ((ch = fgetc(f)) != EOF) {
        if (isalpha(ch))
            initialPosi = positionSize;
        
        positionSize++;
        while (isalpha(ch)) {
            word[i++] = tolower(ch);
            if ((ch = fgetc(f)) == EOF)
                break;
            positionSize++;
        }
        if (i > 0)
            break;
    }
    word[i] = '\0';
    return i ? initialPosi : -1;
}
