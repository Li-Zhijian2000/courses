#include <stdio.h>
#include <stdlib.h>
#define MAXN 500

struct Line {
    int x1, y1;
    int x2, y2;
    int cnt;
};
struct Line lines[MAXN];
int next[MAXN];
int size = 1;  // 头节点

int cmp(const void *lhs, const void *rhs) {
    struct Line *a = (struct Line *)lhs, *b = (struct Line *)rhs;
    return a->x1 - b->x1;
}

int main() {
    int n;
    scanf("%d", &n);

    int i, j;
    for (i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        lines[size++] = (struct Line){x1, y1, x2, y2, 1};
    }
    qsort(lines + 1, size - 1, sizeof(lines[0]), cmp);

    for (i = 1; i < size; i++) {
        next[i] = (i != size - 1) ? i + 1 : 0;
    }

    for (i = 1; i != 0; i = next[i]) {
        for (j = 1; j != i; j = next[j]) {
            if (lines[j].x2 == lines[i].x1 && lines[j].y2 == lines[i].y1) {
                lines[j].cnt++;
                lines[j].x2 = lines[i].x2;
                lines[j].y2 = lines[i].y2;

                next[i - 1] = next[i];

                break;
            }
        }
    }

    i = 1;
    int max = i;
    while (i) {
        if (lines[i].cnt > lines[max].cnt) max = i;
        i = next[i];
    }

    printf("%d %d %d\n", lines[max].cnt, lines[max].x1, lines[max].y1);
}