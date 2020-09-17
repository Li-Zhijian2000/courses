#define local
#include <iostream>
#include <algorithm>
using namespace std;

const long maxn = 105;
const long maxm = 10005;

long cost[maxn];
long dp[maxm];

int main()
{
#ifdef local
    freopen("p1164.txt", "r", stdin);
#endif

    long n, m;
    cin >> n >> m;
    dp[0] = 1;
    for (long i = 1; i <= n; i++) {
        cin >> cost[i];
    }

    for (long i = 1; i <= n; i++) {
        for (long c = m; c >= cost[i]; c--) {
            dp[c] += dp[c - cost[i]];
        }
    }
    
    cout << dp[m] << endl; 
    return 0;
}