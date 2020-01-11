// E0-算法第0次练习赛-数据结构复习
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

// 看K部电影所带来的愉悦值为K部电影的时长(t)之和乘以K部电影中最小的愉悦值(v)
// 把电影按照愉悦值从大到小排序，每次比对已选择电影中时长最短和未选择电影中愉悦值最大
void b() {
  int n, k;
  cin >> n >> k;
  vector<pii> v(n);
  for (int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;
  // 心情从大到小
  sort(v.begin(), v.end(), [](pii a, pii b) { return a.second > b.second; });
	
  //随着i的增加，愉悦度在减少。愉悦度减少的同时，  
	//在保证长度的个数为k个的情况下尽可能让长度变长，
	//求得每次愉悦度和长度和的乘积，取最大的那个。
  priority_queue<int, vi, greater<int>> pq;
  long sum = 0, res = 0;
  for (int i = 0; i < n; i++) {
      sum += v[i].first;
      pq.push(v[i].first);
      if (pq.size() > k) {
        sum -= pq.top(); pq.pop();
      }
      res = max(res, sum * v[i].second);
  }
  cout << res << '\n';
}
// 并查集板子
void d() {
  int n, m; cin >> n >> m;
  vi id(n+2);
  // 需要在右节点虚构一个虚拟黑暗结点
  for (int i = 1; i <= n+1; i++) id[i] = i;
  auto root = [&](int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
  };

  int ans = n;
  while (m--) {
    // id[l..r] = r+1;
    int l, r; cin >> l >> r;
    l = root(l);
    while (l <= r) {
      id[l] = l+1;
      ans--;
      l = root(l);
    }
  cout << ans << '\n';
  }
}

// 可将其视作一个图，结果就是每个结点到最近叶结点的路径之和/n
// 最短路bfs
// 简单版建图
void f() {
  int n; cin >> n;
  vvi G(n);
  for (int i = 0; i < n-1; i++) {
    int u, v; cin >> u >> v;
    u--, v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  queue<int> q;
  vi vis(n), d(n, inf);
  // 添加叶子结点
  for (int i = 0; i < n; i++) {
    if (G[i].size() == 1) {
      q.push(i);
      d[i] = 0;
    }
  }
  while (!q.empty()) {
    int u = q.front(); q.pop();
    vis[u] = 1;
    for (int i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
      if (!vis[v]) {
        d[v] = min(d[v], d[u]+1);
        q.push(v);
      }
    }
  }
  double ans = 0;
  for (int i = 0; i < n; i++) ans += d[i];
  printf("%.4lf\n", ans / n);
}
// 复杂版建图
void f2() {
  struct Edge {
    int from, to;
  };
  int n; cin >> n;
  vvi G(n);
  vector<Edge> edges;
  auto AddEdge = [&](int u, int v) {
    G[u].push_back(edges.size());
    edges.push_back((Edge){u, v});
  };
  for (int i = 0; i < n-1; i++) {
    int u, v; cin >> u >> v;
    u--, v--;
    AddEdge(u, v);
    AddEdge(v, u);
  }
  queue<int> q;
  vi vis(n), d(n, inf);
  // 添加叶子结点
  for (int i = 0; i < n; i++) {
    if (G[i].size() == 1) {
      q.push(i);
      d[i] = 0;
    }
  }
  while (!q.empty()) {
    int u = q.front(); q.pop();
    vis[u] = 1;
    for (int i = 0; i < G[u].size(); i++) {
      Edge& e = edges[G[u][i]];
      if (!vis[e.to]) {
        d[e.to] = min(d[e.to], d[u]+1);
        q.push(e.to);
      }
    }
  }
  double ans = 0;
  for (int i = 0; i < n; i++) ans += d[i];
  printf("%.4lf\n", ans / n);
}
//道恩对客人按照熟悉程度进行编号1-n，其中1号他最熟悉。然后客人之间有m个到场顺序限制。
// 现在请你生成一个排序，使得在满足到场限制的条件下，使得1号尽可能早的入场，然后2号，3号……以此类推
// 反向建边，按照1...n的顺序拓扑排序，为保证字典序最小，用优先队列存边
void g() {
  int n, m; cin >> n >> m;
  vector<priority_queue<int, vi, greater<int>>> G(n);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    u--, v--;
    // 反向建边
    G[v].push(u);
  }
  function<void(int u)> dfs;
  vi vis(n);
  dfs = [&](int u)->void {
    if (vis[u]) return;
    vis[u] = 1;
    while (!G[u].empty()) {
      int v = G[u].top(); G[u].pop();
      if (!vis[v]) dfs(v);
    }
    cout << u+1 << ' ';
  };
  for (int i = 0; i < n; i++) dfs(i);
  cout << '\n';
}

// bellman-ford板子
// 理论上只需要存边
// 这个魔法阵缺少了3条边，且已经知道这3条边的起点和终点（有向）。对于每条边，克莱恩要赋予其一个能量值c，为了避免邪神出现，修补过程以及结束后也不能出现负环。
// 因为不能出现负环，所以修补s->t的最小花费实际上为t->s最短路径的相反数
void h() {
  struct Edge {
    int from, to ,dist;
  };
  int n, m; cin >> n >> m;
  vector<Edge> edges;
  for (int i = 0; i < m; i++) {
    int u, v, d; cin >> u >> v >> d;
    edges.push_back((Edge){u, v, d});
  }

  int s, t;
  while (cin >> s >> t) {
    vi d(n, inf);
    auto BellmanFord = [&](int s) {
      d[s] = 0;
      // 迭代n-1次
      for (int i = 0; i < n-1; i++) {
        // 注意运行中加边
        for (Edge& e: edges) {
          int u = e.from, v = e.to;
          d[v] = min(d[v], d[u] + e.dist);
        }
      }
    };
    BellmanFord(t);
    cout << -d[s] << '\n';
    edges.push_back((Edge){s, t, -d[s]});
  }
}
// 对于每一个城镇，最近的治安点距离为多少
// 可添加一个点，连接所有的治安点，跑一边dijkstra
void i() {
  struct Edge {
    int from, to, dist;
  };
  int t; cin >> t;
  while (t--) {
    int n, m, k; cin >> n >> m >> k;
    // 添加一个超级点
    n++;
    vvi G(n);
    vector<Edge> edges;
    auto AddEdge = [&](int u, int v, int d) {
      G[u].push_back(edges.size());
      edges.push_back((Edge){u, v, d});
    };
    for (int i = 0; i < k; i++) {
      int v; cin >> v;
      AddEdge(0, v, 0);
    }
    for (int i = 0; i < m; i++) {
      int u, v, d; cin >> u >> v >> d;
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
    Dijkstra(0);
    for (int i = 1; i < n; i++) cout << d[i] << ' ';
    cout << '\n';
  }
}
// 扫描到边(x, y, z)时， 此时需要合并两个集合，并添加一条边，形成一颗新树。
// 为了保证(x, y)一定在最后的最小生成树中，那么对于 u in Sx & v in Sy & (x, y) != (u, v)
// uv边的权值应该是大于z的。为了是图最后的边权值最小，uv的边权值应该为z+1
void j() {
  struct Edge {
    int from, to, dist;
  };
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<Edge> edges;
    for (int i = 0; i < n-1; i++) {
      int u, v, d; cin >> u >> v >> d;
      u--, v--;
      edges.push_back((Edge){u, v, d});
    }
    int m = edges.size();
    // 给边排序
    vi r(m);
    for (int i = 0; i < m; i++) r[i] = i;
    sort(r.begin(), r.end(), [&](int a, int b) { return edges[a].dist < edges[b].dist; });

    // 并查集
    vi id(n);
    for (int i = 0; i < n; i++) id[i] = i;
    auto root = [&](int i) {
      while (i != id[i]) {
          id[i] = id[id[i]];
          i = id[i];
      }
      return i;
    };
    // 该集合的点的个数，初始时一个点为一个集合
    vector<long> cnt(n, 1);
    long ans = 0;
    for (int i = 0; i < m; i++) {
      Edge& e = edges[r[i]];
      int x = root(e.from), y = root(e.to);
      id[x] = y;
      ans += e.dist; // 勿忘
      ans += (cnt[x] * cnt[y] - 1) * (e.dist + 1);
      cnt[y] += cnt[x];
    }
    cout << ans << '\n';
  }
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // b();
  // d();
  // f();
  // g();
  // h();
  // i();
  j();
}