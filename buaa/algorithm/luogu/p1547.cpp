// #define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 2005;
const int maxm = 10005;
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
int d[maxn];
int n, m;

int r[maxm], p[maxn];
int find(int x) { return p[x] == x ? x : x = find(p[x]); }
long kruskal() {
  for (int i = 0; i < n; i++) p[i] = i;
  for (int i = 0; i < m; i++) r[i] = i;
  sort(r, r+m, [](const int a, const int b) { return edges[a] < edges[b]; });
  
  long ans = 0, max_w = 0;
  for (int i = 0, j = 0; i < m; i++) {
    Edge& e = edges[r[i]];
    int x = find(e.u), y = find(e.v);
    if (x != y) {
      j++;
      ans += e.w;
      p[x] = y;
    }
    if (j == n-1) {
      max_w = e.w;
      break;
    }
  }
  cout << max_w << '\n';
  return ans;
}
int main() {
#ifdef local
  freopen("p1547.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back(Edge(u, v, w));
  }
  kruskal();
  return 0;
}
