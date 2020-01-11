// #define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 205;
const int inf = 0x3f3f3f3f;
int d[maxn][maxn];

int main() {
#ifdef local
  freopen("c.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int t; cin >> t;
  while (t--) {
    int n, m; cin >> n >> m;
    memset(d, 0x3f, sizeof(d));
    for (int i = 0; i < m; i++) {
      int u, v, w; cin >> u >> v >> w;
      u--, v--;
      d[u][v] = w;
    }
    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          if (i != j) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    
    int maxs = -1;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (d[i][j] == inf) d[i][j] = -1;
        maxs = max(maxs, d[i][j]);
      }
    // cout << "max: " << maxs << '\n';
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (d[i][j] == maxs) cout << i + 1 << ' ' << j + 1 << '\n';
      }
    } 
  }
  return 0;
}
