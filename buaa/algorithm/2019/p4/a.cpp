// #define local
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 3000 + 5;
typedef pair<int, int> pii;
struct Edge {
    Edge(int t, int w): to(t), weight(w) {}
    int to;
    int weight;
};
vector<Edge> edges[maxn];
bool vis[maxn];
long d[maxn];

void dijkstra(int u) {
    memset(d, 0x7f, sizeof(d));
    memset(vis, 0, sizeof(vis));
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    d[u] = 0;
    pq.push(pii(d[u], u));

    while (!pq.empty()) {
        pii top = pq.top();
        pq.pop();
        int v = top.second;
        vis[v] = true;
        for (Edge e: edges[v]) {
            int u = e.to;
            if (!vis[u] && d[u] > d[v] + e.weight) {
                d[u] = d[v] + e.weight;
                pq.push(pii(d[u], u));
            }
        }
    }
}

int main()
{
#ifdef local
    freopen("a.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    int n, m, from, to;
    cin >> n >> m >> from >> to;
    for (int i = 0; i < m; i++) {
        int from, to, w;
        cin >> from >> to >> w;
        edges[from].push_back(Edge(to, w));
        edges[to].push_back(Edge(from, w));
    }

    dijkstra(from);
    cout << d[to] << '\n';
    return 0;
}