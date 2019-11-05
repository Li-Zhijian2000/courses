// #define local
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 300 + 5;

struct Edge {
    Edge(int f, int t, int w): from(f), to(t), weight(w) {}
    int from;
    int to;
    int weight;
};
vector<Edge> edges;
long long d[maxn];

int main()
{
#ifdef local
    freopen("h.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int from, to, w;
        cin >> from >> to >> w;
        edges.push_back(Edge(from, to, w));
    }

    int from, to;
    const long long inf = 1e6;
    while (cin >> to >> from) {
        for (int i = 0; i < n; i++)
            d[i] = inf;
        
        d[from] = 0;
        for (int i = 0; i < n; i++) {
            for (Edge e: edges) {
                d[e.to] = min(d[e.to], d[e.from] + e.weight);
            }
        }
        cout << -d[to] << endl;
        edges.push_back(Edge(to, from, -d[to]));
    }
    return 0;
}