// C4-2018级算法第四次上机
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

const int inf = 0x3f3f3f3f;

// 堆优化dijkstra
void a() {
  struct Edge {
    int from, to, dist;
  };
  int n, m, s, t; cin >> n >> m >> s >> t;
  s--, t--;
  vvi G(n);
  vector<Edge> edges;
  auto AddEdge = [&](int u, int v, int d) {
    G[u].push_back(edges.size());
    edges.push_back((Edge){u, v, d});
  };
  for (int i = 0; i < m; i++) {
    int u, v, d; cin >> u >> v >> d;
    u--, v--;
    // 无向图
    AddEdge(u, v, d);
    AddEdge(v, u, d);
  }

  vi d(n, inf);
  auto Dijkstra = [&](int s) {
    vi vis(n);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    d[s] = 0;
    pq.push(pii(d[s], s));
    while (!pq.empty()) {
        pii top = pq.top(); pq.pop();
        int u = top.second;
        vis[u] = 1;
        for (int i = 0; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if (!vis[e.to] && d[e.to] > d[u] + e.dist) {
                d[e.to] = d[u] + e.dist;
                pq.push(pii(d[e.to], e.to));
            }
        }
    }
  };
  Dijkstra(s);
  cout << d[t] << '\n';
}
// 给定n, m，输出从 1∼n 中选择m个数的所有排列。 要求按照字典序输出。
void b() {
  int n, m; cin >> n >> m;
  vi ans(m);
  function<void(int cur)> dfs;
  dfs = [&](int cur)->void {
    if (cur == m) {
      for (int i = 0; i < m; i++) cout << ans[i] << " ";
      cout << '\n';
    }
    else {
      for (int i = 1; i <= n; i++) {
        int ok = 1;
        for (int j = 0; j < cur; j++)
          if (ans[j] == i) ok = 0;
        if (ok) {
          ans[cur] = i;
          dfs(cur + 1);
        }
      }
    }
  };
  dfs(0);
}
// 食物链
// dp[i] = sum(子节点)，简单路径终点（出度为0）dp[i] = 1
// ans = sum（入度为0）的结点
void c() {
  struct Edge {
    int from, to;
  };
  int n, m; cin >> n >> m;
  vvi G(n);
  vector<Edge> edges;
  vi indegree(n);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    u--, v--;
    G[u].push_back(edges.size());
    edges.push_back((Edge){u, v});
    indegree[v]++;
  }

  vi vis(n), dp(n);
  function<int(int u)> dfs;
  dfs = [&](int u)->int {
    if (vis[u]) return dp[u];
    vis[u] = 1;
    // 出度为0
    if (!G[u].size()) return dp[u] = 1;

    for (int i = 0; i < G[u].size(); i++) {
      Edge& e = edges[G[u][i]];
      dp[u] += dfs(e.to);
    }
    return dp[u];
  };
  long ans = 0;
  for (int i = 0; i < n; i++) dfs(i);
  for (int i = 0; i < n; i++) {
    // 入度为0，单独生物不成食物链
    if (!indegree[i] && G[i].size()) ans += dp[i];
  }
  cout << ans << '\n';
}
// 最小乘法dp
// dp(i, j)表示s[0...i)含j个乘号的最大值，保证i > j
// convert(i, j) atoi(s[i...j))
// dp(i, j) = max(dp(i, j), dp(k, j-1) * convert(k, i)), k in [j, i)
// bound case: dp[i][0]
void d() {
  int n;
  while (cin >> n) {
    string s; cin >> s;
    int len = s.size();
    vector<vector<long>> dp(len+1, vector<long>(n+1));
    
    auto convert = [&](int i, int j) { return atol(s.substr(i, j-i).c_str()); };
    for (int i = 1; i <= len; i++) dp[i][0] = convert(0, i);

    for (int i = 2; i <= len; i++)
      for (int j = 1; j <= n; j++)
        for (int k = j; k < i; k++)
          dp[i][j] = max(dp[i][j], dp[k][j-1] * convert(k, i));
    
    cout << dp[len][n] << '\n';
  }
}
// 时间？销售的时间越短越好，因为剩余未在销售态的鱼需要喂养。
// 消耗量？单位饲料消耗量越大越好。
// 按照 消耗量/时间 排序
void e() {
  int n; cin >> n;
  vector<pii> vp(n);
  // t, d
  for (int i = 0; i < n; i++) cin >> vp[i].first >> vp[i].second;
  sort(vp.begin(), vp.end(), [](pii a, pii b) { return (double)a.second / a.first > (double)b.second / b.first; });
  long t = vp[0].first, ans = 0;
  for (int i = 1; i < n; i++) {
    ans += t * vp[i].second;
    t += vp[i].first;
  }
  cout << ans << '\n';
}
void f() {
  int t;
  cin >> t;
  while (t--) {
    int n; cin >> n;
    vi v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    long ans = 0;
    for (int i = 0; i < n; i++) ans += v[i];
    ans += (n-2) * *min_element(v.begin(), v.end());
    cout << ans << '\n';
  }
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // a();
  // b();
  // c();
  // d();
  // e();
  f();
  return 0;
}