#include <stdio.h>
#include <stdlib.h>
#define maxn 1000
struct Node {
    long a;
    int index;
};

struct Node left[maxn], right[maxn], res[maxn * maxn];
int resn[maxn];

struct Node multi(struct Node lhs, struct Node rhs) {
    struct Node x = {lhs.a * rhs.a, lhs.index + rhs.index};
    return x;
}
int comp(const void *lhs, const void *rhs) {
    return ((struct Node *)rhs)->index - ((struct Node *)lhs)->index;
}

int input(struct Node *start) {
    char line[1024];
    char *data = line;
    int offset, i = 0;
    gets(line);
    while (~sscanf(data, "%lld%d%n", &start[i].a, &start[i].index, &offset)) {
        data += offset;
        i++;
    }
    return i;
}

int main() {
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
        else
            res[i + 1].a += res[i].a;
    }
    putchar('\n');
    return 0;
}
