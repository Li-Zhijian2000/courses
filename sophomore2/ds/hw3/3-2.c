#include <stdio.h>
#define maxn 105
int next[maxn];

void init(int n) {
    int i;
    for (i = 1; i <= n; i++) {
        next[i] = (i + 1) > n ? 1 : i + 1;
    }
}
int main() {
    int n, m, q, i;
    scanf("%d%d%d", &n, &m, &q);
    if (n == 1) {
        puts("1");
        return 0;
    }
    init(n);
    q = (q - 1) < 1 ? n : q - 1;
    while (--n) {
        int step = (m - 1) % (n + 1);
        for (i = 0; i < step; i++) q = next[q];
        next[q] = next[next[q]];
    }
}
