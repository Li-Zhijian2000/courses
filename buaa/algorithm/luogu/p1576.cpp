// #define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 2005;
const int inf = 0x3f3f3f3f;
struct Edge {
    int u, v, w;
    Edge(int u, int v, int w): u(u), v(v), w(w) {}
    friend bool operator <(const Edge& a, const Edge& b) {
      return a.w < b.w;
    }
};
vector<Edge> edges;
vector<int> G[maxn];
bool vis[maxn];
double d[maxn];
int n, m;

void AddEdge(int u, int v, int w) {
  edges.push_back(Edge(u, v, w));
  G[u].push_back(edges.size() - 1);
}
typedef pair<int, int> pii;
int pa[maxn];
void dijkstra(int u) {
    for (int i = 0; i < n; i++) {
      vis[i] = 0;
      d[i] = inf;
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    d[u] = 100;
    pq.push(pii(d[u], u));

    while (!pq.empty()) {
        pii top = pq.top();
        pq.pop();
        int u = top.second, w = top.first;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = 0; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if (d[e.v] > d[e.u] / (100-e.w) * 100) {
                d[e.v] = d[e.u] / (100-e.w) * 100;
                pa[e.v] = e.u;
                pq.push(pii(d[e.v],e.v));
            }
        }
    }
}
int main() {
#ifdef local
  freopen("p1576.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    AddEdge(u, v, w);
    AddEdge(v, u, w);
  }
  int a, b;
  cin >> a >> b;
  a--, b--;
  dijkstra(b);
  printf("%.8lf\n", d[a]);
  return 0;
}
