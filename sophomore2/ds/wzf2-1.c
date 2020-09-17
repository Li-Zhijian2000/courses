#include <stdio.h>
int chess[20][20];
int step[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
                 {0, -1},  {1, -1}, {1, 0},  {1, 1}};
int main() {
    freopen("input.txt", "r", stdin);
    int i, j, count, k, ii, jj, x, y;
    for (i = 1; i <= 19; i++) {
        for (j = 1; j <= 19; j++) {
            scanf("%d", &chess[i][j]);
        }
    }
    for (i = 1; i <= 19; i++) {
        for (j = 1; j <= 19; j++) {
            if (chess[i][j] != 0) {
                for (k = 0; k < 8; k++) {
                    count = 0;
                    ii = i;
                    jj = j;
                    while (ii <= 19 && ii >= 1 && jj <= 19 && jj >= 1 &&
                           chess[ii][jj] == chess[i][j]) {
                        ii = ii + step[k][0];
                        jj = jj + step[k][1];
                        count++;
                    }
                    if (count == 4 && ii <= 19 && ii >= 1 && jj <= 19 &&
                        jj >= 1 && count == 4 && chess[ii][jj] == 0) {
                        if (k == 3 || k == 5 || k == 6 || k == 7) {
                            x = i;
                            y = j;
                        } else {
                            x = ii - step[k][0];
                            y = jj - step[k][1];
                        }
                        printf("%d:%d,%d\n", chess[i][j], x, y);
                        return 0;
                    }
                }
            }
        }
    }
    printf("No\n");
}
