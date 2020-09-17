// #define local
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 100000 + 5;
vector<int> edges[maxn];
int d[maxn];
bool visited[maxn];

int main()
{
#ifdef local
    freopen("f.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int from, to;
        cin >> from >> to, from--, to--;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (edges[i].size() == 1) {
            visited[i] = true;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v: edges[u]) {
            if (!visited[v]) {
                // cout << u << " " << v << endl;
                d[v] = d[u] + 1;
                visited[v] = true;
                q.push(v);
            }
        }
    }
    
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += d[i];
    
    printf("%.4lf\n", (double)sum / n);
    return 0;
}
