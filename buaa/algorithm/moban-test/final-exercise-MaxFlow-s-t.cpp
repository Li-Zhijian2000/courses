#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

const int maxn = 100000 + 10;
const int inf = 1000000000;

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

  // n = t + 1
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
    fill(vis, vis+n, 0);
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
      fill(cur, cur+n, 0);
      flow += DFS(s, inf);
    }
    return flow;
  }
  vector<int> MinCut() { // call this after maxflow
    vector<int> ans;
    for(int i = 0; i < edges.size(); i++) {
      Edge& e = edges[i];
      if(vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
    }
    return ans;
  }

  vector<int> MatchEdge() {
    vector<int> ans;
    for (int i = 0; i < edges.size(); i++) {
      Edge& e = edges[i];
      if (e.from == s || e.to == t) continue;
      if (e.flow > 0) ans.push_back(i);  
    }
    return ans;
  }
};

#include <iostream>
Dinic g;

void s_2018_final() {
  int n, m; cin >> n >> m;
  int s = 0, t = n-1;
  g.init(n);
  for (int i = 0; i < m; i++) {
    int u, v, d; cin >> u >> v >> d;
    u--, v--;
    g.AddEdge(u, v, d);
    g.AddEdge(v, u, d);
  }
  cout << g.MaxFlow(s, t) << '\n';
}
void v_2018_final() {
  int n, m; 
  while (cin >> n >> m) {
    int s = n + m, t = n + m + 1;
    g.init(t+1);

    vi a(n), b(m);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      g.AddEdge(s, i, 1);
    }
    for (int i = 0; i < m; i++) {
      cin >> b[i];
      g.AddEdge(i+n, t, 1);
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (!(b[j] % a[i])) g.AddEdge(i, j+n, inf);
    cout << g.MaxFlow(s, t) << '\n';
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  s_2018_final();
  v_2018_final();
  return 0;
}