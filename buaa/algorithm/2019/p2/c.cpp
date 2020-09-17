// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e3+5;
long value[maxn];
long dp[maxn];

long solve(int n) {
    if (dp[n]) return dp[n];
    
    dp[n] = value[n];
    for (int i = 1; i < n; i++) {
        long a = solve(i);
        long b = solve(n - i);
        dp[n] = min(dp[n], a + b);
    }
    return dp[n];   
}
int main() {
#ifdef local
    freopen("c.txt", "r", stdin);
#endif

    int n;
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++)
            scanf("%ld", value + i);
        memset(dp, 0, (n+1) * 8);
        
        printf("%ld\n", solve(n));
    }
    return 0;
}
