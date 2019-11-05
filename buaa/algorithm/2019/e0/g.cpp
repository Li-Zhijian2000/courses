#define local
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 100000 + 5;
bool visited[maxn];
priority_queue<int, vector<int>, greater<int>> edges[maxn];

void dfs(int u)
{
    if (visited[u]) return;
    
    while (!edges[u].empty()) {
        int v = edges[u].top();
        edges[u].pop();
        dfs(v);
    }
    visited[u] = true;
    cout << u + 1 << " ";
}
int main()
{
#ifdef local
    freopen("g.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    while (m--) {
        int from, to;
        cin >> from >> to, from--, to--;
        edges[to].push(from);
    }

    for (int i = 0; i < n; i++) {
        dfs(i);
    }
    cout << endl;
    return 0;
}