#include <stdio.h>
#include <string.h>
#define maxn 10000000 + 20

typedef struct 
{
    char mod;
    int code;
}value;

value *hash[maxn / 10];
char cnt[maxn / 10];
char islogin[maxn / 8];

char test(int k)
{
    return (islogin[k >> 3]) & (0x80 >> (islogin[k] & 0x07));
}
void set(int k)
{
    (islogin[k >> 3]) &= (0x80 >> (islogin[k] & 0x07));
}
void clear(int k)
{
    (islogin[k >> 3]) &= ~(0x80 >> (islogin[k] & 0x07));
}
int main()
{
    int n, m, workernum = 0;
    long long res = 0;
    scanf("%d%d", &n, &m);
    while (m--) {
        char *opt;
        int a, c;
        scanf("%s", opt);
        switch (*opt) {
            case 'I':scanf("%d%d", &a, &c);
                     int quotient = a / 10;
                     char remainder = a % 10;
                     value *startnode = hash[quotient];
                     if (!test(a)) {
                         workernum++;
                         startnode[cnt[quotient]].mod = remainder;
                         startnode[cnt[quotient]].code = c;
                         cnt[quotient]++;
                         set(a);
                         workernum++;
                     }
                     for (char i = 0; i < cnt[quotient]; ++i) {
                         if (startnode[i].mod == remainder) {
                             startnode[i].code = c;
                             break;
                         }
                     }
                     break;
            case 'O':scanf("%d", &a);
                     clear(a);
                     break;
            case 'C':memset(islogin, 0, (n + 7) / 8);
                     workernum = 0;
                     break;
            case 'N':res += workernum;
                     break;
            case 'Q':scanf("%d", &a);
                     if (test(a)) {
                         int quotient = a / 10;
                         char remainder = a % 10;
                         value *startnode = hash[quotient];
                         for (char i = 0; i < cnt[quotient]; ++i) {
                             if (startnode[i].mod == remainder) {
                                 res += startnode[i].code;
                                 break;
                             }
                         }
                     }
                     else res += -1;
                     break;
            default:break;
        }
        // printf("%d %lld\n", m, res);
    }
    printf("%lld\n", res);
    return 0;
}