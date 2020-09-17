#include <stdio.h>

int a[12];

void perm(int cur, int n) {
    int i;
    if (cur == n) {
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        putchar('\n');
        return;
    }
    for (i = 1; i <= n; i++) {
        int ok = 1, j;
        for (j = 0; j < cur; j++) {
            if (a[j] == i) ok = 0;
        }
        if (ok) {
            a[cur] = i;
            perm(cur + 1, n);
        }
    }
}
int main() {
    int n;
    scanf("%d", &n);
    perm(0, n);
    return 0;
}