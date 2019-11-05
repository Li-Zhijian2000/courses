// #define local
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 1e5 + 5;

struct Edge {
    int from;
    int to;
    int weight;
    Edge(int f, int t, int w): from(f), to(t), weight(w) {}
    bool operator< (const Edge& b) { return this->weight < b.weight; }
};

vector<Edge> edges;
long long size[maxn];
int id[maxn];

int root(int i)
{
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}
// void merge(int i, int j)
// {
//     if (root(i) != root(j)) {
//         id[i] = j;
//     }
// }
// bool connected(int i, int j) { return root(i) == root(j); }

int main()
{
#ifdef local
    freopen("j.txt", "r", stdin);
    // freopen("my.txt", "w", stdout);
#endif

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            id[i] = i;
            size[i] = 1;
        }
        edges.clear();

        for (int i = 0; i < n - 1; i++) {
            int from, to, w;
            cin >> from >> to >> w, from--, to--;
            edges.push_back(Edge(from, to, w));
        }

        sort(edges.begin(), edges.end());

        long long ans = 0, nedge = 0;
        for (int i = 0; i < n - 1; i++) {
            Edge e = edges[i];
            
            int ru = root(e.from), rv = root(e.to);
            id[rv] = ru;
            ans += e.weight;
            ans += (size[ru] * size[rv] - 1) * (e.weight + 1);
            size[ru] += size[rv];
        }
        cout << ans << endl;
    }
    return 0;
}