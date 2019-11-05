// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e3+5;
const int maxk = 1e3+5;
const long inf = 0x7f7f7f7f;
long price[maxn];
long dp[maxn][maxk][2];

struct Stock {
    int N, K;
    Stock(int n, int k): N(n), K(k) {}
    long k_1() {
        long k_i_0 = 0, k_i_1 = -inf;
        for (int i = 1; i <= N; i++) {
            k_i_0 = max(k_i_0, k_i_1 + price[i]);
            k_i_1 = max(k_i_1, -price[i]);
        }
        return k_i_0;
    }
    long k_inf() {
        long k_i_0 = 0, k_i_1 = -inf;
        for (int i = 1; i <= N; i++) {
            k_i_0 = max(k_i_0, k_i_1 + price[i]);
            k_i_1 = max(k_i_1, k_i_0 - price[i]);
        }
        return k_i_0;
    }
    // long k_2() {
    //     for (int k = 0; k <= K; k++)
    //         dp[0][k][1] = -inf;
    //     for (int i = 0; i <= N; i++)
    //         dp[i][0][1] = -inf;
        
    //     for (int i = 1; i <= N; i++)
    //         for (int k = 1; k <= K; k++) {
    //             dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i]);
    //             dp[i][k][1] = max(dp[i-1][k][1], dp[i][k-1][0] - price[i]);
    //         }
    //     return dp[N][K][0];
    // }
    long k_any() {
        if (K * 2 >= N) return k_inf();

        for (int k = 0; k <= K; k++)
            dp[0][k][1] = -inf;
        for (int i = 0; i <= N; i++)
            dp[i][0][1] = -inf;
        
        for (int i = 1; i <= N; i++)
            for (int k = 1; k <= K; k++) {
                dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i]);
                dp[i][k][1] = max(dp[i-1][k][1], dp[i][k-1][0] - price[i]);
            }
        return dp[N][K][0];
    }
};

int main() {
#ifdef local
    freopen("e.txt", "r", stdin);
#endif

    int n, k;
    while (~scanf("%d%d", &n, &k)) {
        for (int i = 1; i <= n; i++)
            scanf("%ld", price + i);
        Stock stock(n, k);
        printf("%ld\n", stock.k_any());
    }
    return 0;
}
