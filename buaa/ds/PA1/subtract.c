#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define maxn 85

char stnum[maxn], ndnum[maxn], res[maxn];

void print(char *str)
{
    int i = 0;
    while (str[i++] == '0');
    i--;
    printf("%s\n", str + i);
}
void minus(char *first, char *second, int n) {
    int i, flag;
    for (i = n - 1; i >= 0; --i) {
//        printf("%s %s\n", first, second);
        if (first[i] < second[i]) {
            first[i] += 10;
            first[i - 1] -= 1;
        }
        res[i] = first[i] - second[i] + '0';
    }
}
int main()
{
    gets(stnum);
    gets(ndnum);
    int stlens = strlen(stnum), ndlens = strlen(ndnum), lens; 
    if (stlens > ndlens) {
        int prelens = stlens - ndlens;
        char pre[maxn];
        memset(pre, '0', prelens);
        pre[prelens] = '\0';
        strcat(pre, ndnum);
        memcpy(ndnum, pre, sizeof(pre));
        lens = stlens;
    }
    else {
        int prelens = ndlens - stlens;
        char pre[maxn];
        memset(pre, '0', prelens);
        pre[prelens] = '\0';
        strcat(pre, stnum);
        memcpy(stnum, pre, sizeof(pre));
        lens = ndlens;

    }
    
    int judge = strcmp(stnum, ndnum);
    if (judge > 0) {
        minus(stnum, ndnum, lens);
        print(res);
    }
    else if (judge < 0) {
        minus(ndnum, stnum, lens);
        putchar('-');
        print(res);
    }
    else printf("0\n");
   
    return 0;
}
