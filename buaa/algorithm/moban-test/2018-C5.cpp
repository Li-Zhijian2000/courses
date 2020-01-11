// C6-2018级算法第五次上机
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;

const int inf = 0x3f3f3f3f;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

// 二分，二分图
// 若只保留边长 > c 的边，能构成一个二分图，那么存在一个割能割去所有 > c 的边
void b() {
  struct Edge {
    int from, to, dist;
  };
  int n, m; cin >> n >> m;
  vvi G(n);
  vector<Edge> edges;
  for (int i = 0; i < m; i++) {
    int u, v, d; cin >> u >> v >> d;
    u--, v--;
    G[u].push_back(edges.size());
    edges.push_back((Edge){u, v, d});
    G[v].push_back(edges.size());
    edges.push_back((Edge){v, u, d});
  }

  auto ok = [&](long x) {
    vi vis(n);
    function<bool(int u, int color)> IsBipartite;
    //0：未染色，1：染红色，0：染白色
    IsBipartite = [&](int u, int color)->bool {
      if (vis[u]) {
        // 是否二分图
        if (vis[u] == color) return true;
        else return false;
      }
      vis[u] = color;
      for (int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        // 只保留边长 > c 的边
        if (e.dist <= x) continue;
        if (!IsBipartite(e.to, 3-color)) return false;
      }
      return true;
    };
    bool flag = true;
    for (int i = 0; i < n; i++) {
      if (vis[i]) continue;
      flag &= IsBipartite(i, 1);
    }
    return flag;
  };
  long lo = 0, hi = max_element(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.dist < b.dist; })->dist + 1;
  while (lo < hi) {
    long mi = lo + hi >> 1;
    ok(mi) ? hi = mi : lo = mi + 1;
  }
  cout << hi << '\n';
}
// floyd多源最短路，若不连通，dp[i][j] = -1; dp[i][i] = 0
void c() {
  int t; cin >> t;
  while (t--) {
    int n, m; cin >> n >> m;
    vvi dp(n, vi(n, inf));
    for (int i = 0; i < m; i++) {
      int u, v, d; cin >> u >> v >> d;
      u--, v--;
      dp[u][v] = d;
    }
    // for (int i = 0; i < n; i++) dp[i][i] = 0;

    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    
    int ans = -1;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        dp[i][i] = 0;
        if (dp[i][j] == inf) dp[i][j] = -1;
        ans = max(ans, dp[i][j]);
      }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (dp[i][j] == ans) cout << i+1 << ' ' << j+1 << '\n';
  }
}
// 分数背包板子
void f() {
  struct Material {
    int cost, weight;
    double t;
  };
  int n, t; cin >> n >> t;
  vector<Material> v(n);
  for (int i = 0; i < n; i++) {
    int c, w; cin >> c >> w;
    v[i] = (Material){c, w, (double)w / c};
  }
  sort(v.begin(), v.end(), [](Material a, Material b) { return a.t > b.t; });
  double ans = 0;
  for (int i = 0; i < n; i++) {
    Material& m = v[i];
    if (t >= m.cost) {
      t -= m.cost;
      ans += m.weight;
    }
    else {
      ans += t * m.t;
      break;
    }
  }
  printf("%.2lf\n", ans);
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // b();
  // c();
  f();
  return 0;
}