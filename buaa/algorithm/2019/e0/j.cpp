#define local
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 1e5 + 5;
struct Edge {
    int from;
    int to;
    long weight;
    Edge(int f, int t, int w): from(f), to(t), weight(w) {}
    bool operator< (const Edge& b) { return this->weight < b.weight; }
};

vector<Edge> edges;
long w[maxn];
int id[maxn];

int root(int i)
{
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

int main()
{
#ifdef local
    freopen("j.txt", "r", stdin);
#endif

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            id[i] = i;
        }
        edges.clear();

        for (int i = 0; i < n; i++) {
            cin >> w[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    edges.push_back(Edge(i, j, w[i] + w[j]));
                    // edges.push_back(Edge(j, i, w[i] + w[j]));
                }
            }
        }
        sort(edges.begin(), edges.end());

        long ans = 0;
        for (int i = 0; i < n - 1; i++) {
            Edge e = edges[i];
            
            int ru = root(e.from), rv = root(e.to);
            id[rv] = ru;
            ans += e.weight;
        }
        cout << ans << endl;
    }
    return 0;
}