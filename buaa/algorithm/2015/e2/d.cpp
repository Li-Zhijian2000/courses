// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 1e5+5;
typedef pair<int, int> pii;
struct Edge {
    int to;
    int weight;
    Edge(int t, int w): to(t), weight(w) {}
};

vector<Edge> edges[maxn];
int d[maxn];
bool vis[maxn];

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
int main() {
#ifdef local
    freopen("d.txt", "r", stdin);
#endif
    
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) edges[i].clear();
        while (m--) {
            int from, to, w;
            scanf("%d%d%d", &from, &to, &w);
            edges[from].push_back(Edge(to, w));
            edges[to].push_back(Edge(from, w));
        }

        dijkstra(1);
        for (int i = 2; i <= n; i++)
            printf("%d ", (d[i] < 0x7f7f7f7f ? d[i] : -1));
        putchar('\n');
    }
    return 0;
}
