#include <stdio.h>

typedef struct {
    int count;
    int x1, y1, x2, y2;
}line;

line lines[105];

int main()
{
    int n, i, j, cnt = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        int x1, y1, x2, y2, flag = -1;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        for (j = 0; j < cnt; j++) {
            if (x1 == lines[j].x2 && y1 == lines[j].y2 && lines[j].count) {
                lines[j].x2 = x2;
                lines[j].y2 = y2;
                lines[j].count ++;
                flag = j;
            }
        }
        for (j = 0; j < cnt; j++) {
            if (x2 == lines[j].x1 && y2 == lines[j].y1 && lines[j].count) {
                if (flag < 0) {
                    lines[j].x1 = x1;
                    lines[j].y1 = y1;
                    lines[j].count ++;
                    flag = j;
                    break;
                }
                else {
                    lines[flag].x2 = lines[j].x2;
                    lines[flag].y2 = lines[j].y2;
                    lines[flag].count += lines[j].count;
                    lines[j].count = 0;
                }
            }
        }
        if (flag == -1) {
            line x = {1, x1, y1, x2, y2};
            lines[cnt++] = x;
        }
    }
    int max = 0;
    for (i = 1; i < cnt; i++) {
        // printf("%d:%d,%d,%d,%d\n", lines[i].count, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
        if (lines[i].count > lines[max].count)
            max = i;
    }
    printf("%d %d %d\n", lines[max].count, lines[max].x1, lines[max].y1);
    return 0;
}