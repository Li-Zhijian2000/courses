#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 205;
int map[maxn][maxn];
int dp[maxn];
int main() {
#ifdef local
    freopen("p1060.txt", "r", stdin);
#endif

    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> map[i][j];
        memset(dp, 0, sizeof(dp));
        
    }
    return 0;
}
