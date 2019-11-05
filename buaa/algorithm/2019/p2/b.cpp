#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const long mod = 1e9 + 7;
const int maxn = 1e5+5;
struct Node {
    int lr, rc;
    int normal;
}nodes[maxn];

long dp(int u, int value) {
    if (!nodes[u].lr && !nodes[u].rc) 
        if (value) return 3;
        else return 1;

    long a0 = dp(nodes[u].lr, 0);
    long a1 = dp(nodes[u].lr, 1);
    long a2 = dp(nodes[u].rc, 0);
    long a3 = dp(nodes[u].rc, 1);    
    if (value) {
        return (a0 * a2 % mod + a0 * a3 % mod + a1 * a2 % mod) % mod;
    }
    else return a1 * a3 % mod;

}
int main() {
#ifdef local
    freopen("b.txt", "r", stdin);
#endif

    int n;
    for (int i = 1; i <= n; i++) {
        int lc, rc, normal;
        cin >> lc >> rc >> normal;
        nodes[i] = (Node){lc, rc, normal};
        // nodes[lc].pa = nodes[rc].pa = i;
    }

    if (nodes[1].normal == -1) 
        cout << dp(1, 0) + dp(1, 1);
    else cout << dp(1, nodes[1].normal);
    return 0;
}

