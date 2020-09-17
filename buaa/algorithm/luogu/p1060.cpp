#define local
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const long maxn = 3 * 1e5 + 5;
long cost[maxn], weight[maxn];
long dp[maxn];
long inf = 1e8;
int main()
{
#ifdef local
    freopen("p1060.txt", "r", stdin);
#endif

    long m, n;
    cin >> m >> n;
    for (long i = 1; i <= n; i++) {
        cin >> cost[i] >> weight[i];
        weight[i] *= cost[i];
        dp[i] = -inf;
    }

    for (long i = 1; i <= n; i++) {
        for (long c = m; c >= cost[i]; c--) {
            dp[c] = max(dp[c], dp[c-cost[i]] + weight[i]);
        }
    }
    cout << dp[m] << endl;
    return 0;
}