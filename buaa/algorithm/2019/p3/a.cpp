// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 505, maxm = 505;
const int inf = 0x3f3f3f3f;
int p[maxn][maxm], f[maxn][maxn];
int dp[maxn][maxm];

int main() {
#ifdef local
  freopen("a.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int n, m;
  while (cin >> n >> m) {
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        cin >> p[i][j];
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        cin >> f[i][j];    
    
    for (int i = 0; i <= n; i++) dp[i][1] = p[i][1];

    for (int j = 2; j <= m; j++) {
      for (int i = 1; i <= n; i++) {
        int m = inf;
        for (int k = 1; k <= n; k++)
          m = min(m, dp[k][j-1]+f[k][i]);
        dp[i][j] = p[i][j] + m;
      }
    }
    // for (int i = 0; i <= n; i++) {
    //   for (int j = 1; j <= m; j++)
    //     cout << dp[i][j] << " ";
    //   cout << '\n';
    // }
    int res = inf;
    for (int i = 1; i <= n; i++)
      res = min(res, dp[i][m]);
    cout << res << '\n';
  }
  return 0;
}