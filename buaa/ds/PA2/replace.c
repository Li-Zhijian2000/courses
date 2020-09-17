#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *mystrstr(char *a, char *b)
{
    int lena = strlen(a), lenb = strlen(b), i, j, k, flag = 1;
    for (i = 0; i < lena; i++) {
        for (j = i, k = 0; j < lena && k < lenb; ) {
            if (tolower(a[j++]) != tolower(b[k++])) {
                break;
            }
        }
        if (tolower(a[j-1]) == tolower(b[k-1]))
            return a + i;
    }
    return NULL;
}
int main()
{
    char a[20], b[20], input[1024], output[1024];
    gets(a);
    gets(b);
    int lena = strlen(a), lenb = strlen(b);
    FILE *in = fopen("filein.txt", "r"), *out = fopen("fileout.txt", "w");
    while (fgets(input, 1024, in) != NULL) {
        int lens = strlen(input);
        char *p1 = input, *p2, *outp = output;
        while ((p2 = mystrstr(p1, a)) != NULL) {
            for (; p1 != p2;) {
                *outp++ = *p1++;
            }
            int i;
            for (i = 0; i < lenb; i++, outp++) {
                *outp = b[i];
            }
            p1 += lena;
        }
        while (*outp++ = *p1++)
            ;
        fputs(output, out);
    }
    return 0;
}

