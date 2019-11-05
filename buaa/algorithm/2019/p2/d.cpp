// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 505;
int p1[maxn], p2[maxn], t[2][maxn], dp[2][maxn];

int main() {
#ifdef local
    freopen("d.txt", "r", stdin);
#endif
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", p1 + i);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", p2 + i);
        }
        for (int i = 1; i < n; i++) {
            scanf("%d", &t[0][i]);
        }
        for (int i = 1; i < n; i++) {
            scanf("%d", &t[1][i]);
        }
        for (int i = 1; i <= n; i++) {
            int& a1 = dp[0][i];
            int& a2 = dp[1][i];

            a1 = p1[i] + min(dp[0][i-1], dp[1][i-1] + t[1][i-1]);
            a2 = p2[i] + min(dp[1][i-1], dp[0][i-1] + t[0][i-1]);
        }
        printf("%d\n", min(dp[0][n], dp[1][n]));
    }
    return 0;
}
