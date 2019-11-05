#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define maxn 105

char input[maxn], res[maxn];

int main()
{
    gets(input);
    int lens = strlen(input), lenres, i, e;
    char *p = strchr(input, '.'), *nozero = input;
    
    while(*nozero == '0' || *nozero == '.')
        nozero++;
    
    if (p < nozero) {
        e = p - nozero;
        if (nozero == input + lens - 1)
            printf("%se%d\n", nozero, e);
        else printf("%c.%se%d\n", *nozero, nozero + 1, e);
    }
    else {
        e = p - nozero - 1;
        putchar(*nozero++);
        putchar('.');
        for (; nozero != input + lens; ++nozero) {
            if (*nozero != '.')
                putchar(*nozero);
        }
        printf("e%d\n", e);
    }
    return 0;

}

