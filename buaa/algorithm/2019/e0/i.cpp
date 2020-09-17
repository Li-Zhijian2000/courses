// #define local
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<long long, int> pli;
const int maxn = 1e4 + 5;
const int inf = 1e6 + 5;
struct Edge {
    int to;
    int weight;
    Edge(int t, int w): to(t), weight(w) {}
};
vector<Edge> edges[maxn];
bool visited[maxn];
long long d[maxn];

int main()
{
#ifdef local
    freopen("i.txt", "r", stdin);
#endif

    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        priority_queue<pli, vector<pli>, greater<pli>> pq;
        for (int i = 0; i < n; i++) {
            d[i] = inf;
            visited[i] = false;
            edges[i].clear();
        }
            
        while (k--) {
            int x;
            cin >> x, x--;
            pq.push(pli(0, x));
            d[x] = 0;
        }

        while (m--) {
            int from, to, w;
            cin >> from >> to >> w, from--, to--;
            edges[from].push_back(Edge(to, w));
            edges[to].push_back(Edge(from, w));
        }

        while (!pq.empty()) {
            pli x = pq.top();
            pq.pop();
            int v = x.second;

            if (visited[v]) continue;
            visited[v] = 1;
            
             for (Edge e: edges[v]) {
                 if (d[e.to] > d[v] + e.weight) {
                     d[e.to] = d[v] + e.weight;
                     pq.push(pli(d[e.to], e.to));
                 }
             }
        }
        for (int i = 0; i < n; i++)
            printf("%lld ", d[i]);
        cout << endl;
    }
    return 0;
}