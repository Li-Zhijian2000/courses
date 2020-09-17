#include <stdio.h>

#define N 19

int board[N][N];

int valid(int i, int j) { return i >= 0 && i < N && j >= 0 && j < N; }
int main() {
    int i, j, n = N;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) scanf("%d", &board[i][j]);

    int step[][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1},
    };
    int k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int player = board[i][j];
            if (player) {
                for (k = 0; k < 8; k++) {
                    int si = i, sj = j, cnt = 0;
                    while (valid(si, sj) && board[si][sj] == player) {
                        cnt++;
                        si += step[k][0];
                        sj += step[k][1];
                    }
                    if (cnt == 4 && valid(si, sj) && !board[si][sj]) {
                        if (step[k][0] == 1 || k == 4) {
                            while (cnt--) {
                                si = i;
                                sj = j;
                            }
                        } else {
                            si -= step[k][0];
                            sj -= step[k][1];
                        }
                        printf("%d:%d,%d\n", player, si + 1, sj + 1);
                        return 0;
                    }
                }
            }
        }
    }
    puts("No");
    return 0;
}