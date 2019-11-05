#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 205;
int E[maxn][maxn];
bool vis[maxn];
int d[maxn];

int solve(int i) {
    if (vis[i]) return d[i];
    vis[i] = true;

    for (int j = 1; j < i; j++)
        if (E[j][i])
            d[j] = min(d[j], E[j][i] + solve(i));
     
}
int main() {
#ifdef local
    freopen("p1359.txt", "r", stdin);
#endif

    int n;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++)
            cin >> E[i][j];
    }
    memset(d, 0x7f, sizeof(d));
    d[n] = 0;
    solve(n);
    cout << d[n] << endl;
    return 0;
}
