#define local
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1005;
struct Edge {
    int u, v, cap, flow;
    Edge(int u, int v, int c, int f): u(u), v(v), cap(c), flow(f) {}
};
struct Dinic {
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];
    
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }    
    void AddEdge(int u, int v, int cap) {
    	edges.push_back(Edge(u, v, cap, 0));
    	edges.push_back(Edge(v, u, 0, 0));
      m = edges.size();
      G[u].push_back(m-2);
      G[v].push_back(m-1);
    }    
    bool BFS() {
        memset(vis, 0, sizeof(vis));
        d[s] = 0; vis[s] = 1;
        
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < G[u].size(); i++) {
                Edge& e =edges[G[u][i]];
                if (!vis[e.v] && e.cap > e.flow) {
                    vis[e.v] = 1;
                    d[e.v] = d[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return vis[t];
    }
    int DFS(int u, int a) {
        if (u == t || !a) return a;
        int flow = 0;
        for (int& i = cur[u]; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if (d[u] + 1 == d[e.v]) {
                int f = DFS(e.v, min(a, e.cap - e.flow));
                if (f > 0) {
                    e.flow += f;
                    edges[G[u][i]^1].flow -= f;
                    flow += f;
                    a -= f;
                    if (!a) break;
                }
            }
        }
        return flow;
    }
    int MaxFlow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, inf);
        }
        return flow;
    }
};
Dinic solver;
int main() {
#ifdef local
  freopen("p2756.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int m, n;
  cin >> m >> n;  
  solver.init(n);

  int s = 0, t = n+1;
  for (int i = 1; i <= m; i++) solver.AddEdge(s, i, 1);
  for (int i = m+1; i <= n; i++) solver.AddEdge(i, t, 1);
  int i, j;
  while (cin >> i >> j) {
    if (i == -1 && j == -1) break;
    solver.AddEdge(i, j, 1);
  }
  int ans = solver.MaxFlow(s, t);
  cout << ans << '\n';
  if (!ans) cout << "No Solution!\n";
  else {
    for (Edge& e: solver.edges) {
      if (e.cap == 0) continue;
      if (e.u == s || e.v == t) continue;
      if (e.flow > 0) cout << e.u << ' ' << e.v << '\n';
    }
  }
  return 0;
}
