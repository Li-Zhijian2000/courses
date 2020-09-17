// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e3+5;
long tree[maxn][maxn];
long dp[maxn];

int main() {
#ifdef local
    freopen("b.txt", "r", stdin);
#endif

    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= i; j++)
                scanf("%ld", &tree[i][j]);
        
        memset(dp, 0, (n+1) * 8);
        for (int i = n-1; i >= 0; i--) {
            for (int j = 0; j <= i; j++) 
                dp[j] = max(dp[j], dp[j+1]) + tree[i][j];
        }

        
        printf("%ld\n", dp[0]);
    }
    return 0;
}
