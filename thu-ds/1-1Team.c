#include <stdio.h>
#define maxn 500000+5

int team[3][maxn], ischeck[maxn], index[3];

int main()
{
    int n, aim;
    scanf("%d", &n);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            scanf("%d", &x);
            team[i][j] = x;
        }
    }
    scanf("%d", &aim);
    int cur = 0, i;
    while(1) {
        for (i = 0; i < 3; ++i) {
            while (1) {
                int cur = team[i][index[i]++];
                if (cur == aim) {
                    printf("%c\n", 'A' + i);
                    return 0;
                }
                else if(!ischeck[cur]) {
                    ischeck[cur] = 1;
                    break;
                }
            }
        }
    }

    return 0;
}