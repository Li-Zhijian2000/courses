#include <stdio.h>
#define maxn 100005

typedef struct {
    int index;
    char method;
}opt;

opt opts[maxn * 3];
int in[maxn], s[maxn];

int main()
{
    int n, m, i, need = 1, size = 0, optcnt = 0;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
        scanf("%d", in + i);
    
    i = 0;
    while (need <= n && size <= m) {
        if (size > 0 && s[size - 1] == need) {
            opt x = {need, 'O'};
            opts[optcnt++] = x;
            size--;
            need++;
            continue;
        }
        if (in[i] == need) {
            opt x = {need, 'P'};
            opts[optcnt++] = x;
            i++;
            need++;
        }
        else {
            opt x = {in[i], 'I'};
            opts[optcnt++] = x;
            s[size++] = in[i];
            i++;
        }
    }
    if (need > n) {
        for (i = 0; i < optcnt; i++)
            printf("%d %c\n", opts[i].index, opts[i].method);
    }
    else puts("No");
    return 0;
}