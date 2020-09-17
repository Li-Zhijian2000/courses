#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define maxn 105

char line[maxn], res[maxn];

int main() {
    gets(line);
    int lens = strlen(line), lenres, i, e;
    char *p = strchr(line, '.'), *nozero = line;

    while (*nozero == '0' || *nozero == '.') nozero++;

    if (p < nozero) {
        e = p - nozero;
        if (nozero == line + lens - 1)
            printf("%se%d\n", nozero, e);
        else
            printf("%c.%se%d\n", *nozero, nozero + 1, e);
    } else {
        e = p - nozero - 1;
        putchar(*nozero++);
        putchar('.');
        for (; nozero != line + lens; ++nozero) {
            if (*nozero != '.') putchar(*nozero);
        }
        printf("e%d\n", e);
    }
    return 0;
}
