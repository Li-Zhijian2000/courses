#include <stdio.h>
#include <stdlib.h>
#define maxn 1000
typedef struct
{
    long long a;
    int index;
}node;

node left[maxn], right[maxn], res[maxn * maxn];
int resn[maxn];

node multi(node lhs, node rhs)
{
    node x = {lhs.a * rhs.a, lhs.index + rhs.index};
    return x;
}
int comp(const void *lhs, const void *rhs)
{
    return ((node*)rhs) -> index - ((node*) lhs) -> index;
}
int input(node *start)
{
    char line[1024];
    char *data = line;
    int offset, i = 0;
    gets(line);
    while (~sscanf(data, "%lld%d%n", &start[i].a, &start[i].index, &offset)) {
        data += offset;
        i ++;
    }
    return i;
}
int main()
{
    int lcnt = input(left), rcnt = input(right), cnt = 0, i, j;
    for (i = 0; i < lcnt; i++) {
        for (j = 0; j < rcnt; j++) {
            res[cnt++] = multi(left[i], right[j]);
        }
    }
    qsort(res, cnt, sizeof(res[0]), comp);
    res[cnt].index = -1;
    for (i = 0; i < cnt; i++) {
        if (res[i].index != res[i + 1].index)
            printf("%lld %d ", res[i].a, res[i].index);
        else res[i + 1].a += res[i].a;
    }
    puts("");
    return 0;
}
