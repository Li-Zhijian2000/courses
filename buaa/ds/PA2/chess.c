#include <stdio.h>
#define N 21
#define MAXN N*N

int chess[MAXN];
int direction[8] = {-N-1, -N, -N+1, -1, 1, N-1, N, N+1};

int isvalid(int i)
{
    int quotient = i / N, remainder = i % N;
    return !(quotient == 0 || quotient == 20 || remainder == 0 || remainder == 20);
}
int main()
{
    const int maxn = MAXN;
    int i, j, k, player, cnt;
    for (i = 0; i < maxn; i++) {
        if (isvalid(i))
            scanf("%d", chess + i);
        else chess[i] = 3;
    }
    for (i = 0; i < maxn; i++) {
        if (isvalid(i) && chess[i]) {
            player = chess[i];
            for (j = 0; j < 8; j++) {
                cnt = 1;
                int pos = i;
                while (chess[pos += direction[j]] == player) {
                    cnt++;
                    // printf("%d %d %d:%d,%d\n", j, cnt, player, pos / N, pos % N);
                }
                if (cnt >= 4 && !chess[pos]) {
                    if (j >= 4) {
                        for (k = 0; k < 4; k++)
                            pos -= direction[j];
                    }
                    else pos -= direction[j];
                    printf("%d:%d,%d\n", player, pos / N, pos % N);
                    return 0;
                }
            }
        }
    }
    puts("No");
    return 0;
}