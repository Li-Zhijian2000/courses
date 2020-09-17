// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e4+5;
const int maxm = 1e5+5;
long cost[maxn], weight[maxn], cnt[maxn];
long dp[maxm];

struct Pack {
    long V;
    Pack(long v): V(v) {}
    void zero_one_pack(long cost, long weight) {
        for (int j = V; j >= cost; j--)
            dp[j] = max(dp[j], dp[j - cost] + weight);
    }
    void complete_pack(long cost, long weight) {
        for (int j = cost; j <= V; j++)
            dp[j] = max(dp[j], dp[j - cost] + weight);
    }
    void multiple_pack(long cost, long weight, long cnt) {
        if (cost * cnt >= V)
            complete_pack(cost, weight);
        else {
            long k = 1;
            while (k < cnt) {
                zero_one_pack(k * cost, k * weight);
                cnt -= k;
                k <<= 1;
            }
            zero_one_pack(cnt * cost, cnt * weight);
        }
    }
};
int main() {
#ifdef local
    freopen("c.txt", "r", stdin);
#endif

    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            int x, w, t;
            scanf("%d%d%d", &x, &w, &t);
            if (w <= 0 || !t) {
                n--;
                i--;
                continue;
            }
            cost[i] = x;
            weight[i] = w;
        }
        int k;
        scanf("%d", &k);
        Pack pack(k);
        memset(dp, 0, 8 * (k+1));
        for (int i = 0; i < n; i++)
            pack.zero_one_pack(cost[i], weight[i]);
        printf("%ld\n", dp[k]);
    }
    return 0;
}


