#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 505;
long dp[maxn][maxn], w[maxn][maxn];
bool vis[maxn][maxn];
long p[maxn], q[maxn];

long solve(int x, int y) {
  if (x > y) return q[y];
  long&res  = dp[x][y];
  if (vis[x][y]) return res;
  vis[x][y] = true;

  for (int i = x; i <= y; i++) {
    res = min(res, solve(x, i-1) + solve(i+1, y) + w[x][y]);
  }
  return res;
}
int main() {
#ifdef local
  freopen("optional_bst.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int n;
  while (cin >> n) {
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 0; i <= n; i++) cin >> q[i];
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        dp[i][j] = 0x3f3f3f3f;
        vis[i][j] = false;
      }
    
    for (int i = 1; i <= n; i++) {
      w[i][i] = p[i] + q[i-1]+ q[i];
      for (int j = i+1; j <= n; j++) {
        w[i][j] = w[i][j-1] + q[j] + p[j];
      }
    }
    cout << solve(1, n) << '\n';
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
        cout << ((i > j) ? 0 : dp[i][j]) << " ";
      cout << '\n';
    }
  }
  return 0;
}
