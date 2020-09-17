#include <stdio.h>
#include <string.h>
#define maxn 10000000 + 5

int code[maxn];
int worker[maxn / 10];
int main()
{
    int n, m, workernum = 0, a, c;
    char opt[5];
    long long res = 0;
    scanf("%d %d", &n, &m);
    memset(code, -1, 4 * (n + 1));
    while (m--) {
        scanf("%s", opt);
        switch (*opt) {
            case 'I':scanf("%d %d", &a, &c);
                     if (code[a] == -1) {
                         worker[workernum++] = a;
                     }
                     code[a] = c;
                     break;
            case 'O':scanf("%d", &a);
                     if (code[a] != -1) {
                         workernum--;
                         code[a] = -1;
                     }
                     break;
            case 'C':if (workernum < n / 10) {
                         for (int i = 0; i < workernum; ++i) {
                             code[worker[i]] = -1;
                         }
                     }
                     else memset(code, -1, 4 * (n + 1));
                     workernum = 0;
                     break;
            case 'N':res += workernum;
                     break;
            case 'Q':scanf("%d", &a);
                     res += code[a];
                     break;
            default:break;
        }
        // printf("%d %lld\n", m, res);
    }
    printf("%lld\n", res);
    return 0;
}