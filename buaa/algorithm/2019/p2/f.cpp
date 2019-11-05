// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e5+5;
long cnt[maxn];
long dp[maxn];

int main() {
#ifdef local
    freopen("f.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    dp[1] = cnt[1];
    for (int i = 2; i <= maxn; i++) {
        dp[i] = max(dp[i-1], dp[i-2] + cnt[i] * i);
    }
    cout << dp[maxn] << endl;
    return 0;
}
