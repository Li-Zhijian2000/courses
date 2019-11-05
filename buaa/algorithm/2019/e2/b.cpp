// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 505;
long cost[maxn], weight[maxn];
const int maxm = 30005;
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
    freopen("b.txt", "r", stdin);
#endif

    int n, v;
    while (cin >> n >> v) {
        Pack pack(v);
        for (int i = 0; i < n; i++) {
            cin >> cost[i] >> weight[i];            
        }
        memset(dp, 0, (v+1) * sizeof(dp[0]));
        for (int i = 0; i < n; i++) 
            pack.complete_pack(cost[i], weight[i]);
        
        cout << dp[v] << endl;
    }
    return 0;
}
