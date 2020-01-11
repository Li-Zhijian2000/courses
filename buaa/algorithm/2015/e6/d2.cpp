#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 20000 + 10;
const int INF = 1000000000;

struct Edge {
  int from, to, cap, flow;
};

bool operator < (const Edge& a, const Edge& b) {
  return a.from < b.from || (a.from == b.from && a.to < b.to);
}

struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;    // 边数的两倍
  vector<int> G[maxn];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  bool vis[maxn];         // BFS使用
  int d[maxn];           // 从起点到i的距离
  int cur[maxn];        // 当前弧指针

  
  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap) {
    edges.push_back((Edge){from, to, cap, 0});
    edges.push_back((Edge){to, from, 0, 0});
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    d[s] = 0;
    while(!Q.empty()) {
      int x = Q.front(); Q.pop();
      for(int i = 0; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]];
        if(!vis[e.to] && e.cap > e.flow) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int x, int a) {
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for(int& i = cur[x]; i < G[x].size(); i++) {
      Edge& e = edges[G[x][i]];
      if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i]^1].flow -= f;
        flow += f;
        a -= f;
        if(a == 0) break;
      }
    }
    return flow;
  }

  int MaxFlow(int s, int t) {
    this->s = s; this->t = t;
    int flow = 0;
    while(BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }
};

Dinic g;

// #define local
#include<iostream>
int main() {
#ifdef local
freopen("test/d.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int n, s, t;
  while (cin >> n) {
    s = 0, t = 2 * n + 1;
    g.init(t + 1);

    for (int i = 1; i <= n; i++) g.AddEdge(s, i, 1);
    for (int i = n + 1; i <= 2 * n; i++) g.AddEdge(i, t, 1);

    for (int i = 1; i <= n; i++) {
      int v;
      cin >> v;
      if (v) g.AddEdge(i, v + n, 1);
    }
    for (int i = 1; i <= n; i++) {
      int v;
      cin >> v;
      if (v) g.AddEdge(v, i + n, 1);
    }
    cout << n - g.MaxFlow(s, t) << '\n';
  }
  return 0;
}