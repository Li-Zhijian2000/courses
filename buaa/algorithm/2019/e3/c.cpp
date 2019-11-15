// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 505;
int map[maxn][maxn];
int dp[maxn][maxn];

int main() {
#ifdef local
    freopen("c.txt", "r", stdin);
#endif
    int n, m;
    while (cin >> n >> m) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (!i || !j) dp[i][j] = 0;
                else cin >> map[i][j];
            }
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                dp[i][j] = map[i][j] + max(dp[i][j-1], dp[i-1][j]);
        cout << dp[n][m] << endl;
    }
    return 0;
}
