// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
long dp[2][55];
long solve(int n, bool flag)
{
    if (!n) return 1;
    if (n < 0) return 0;
    if (dp[flag][n]) return dp[flag][n];

    long res = 0;
    res += solve(n-1, true);
    res += solve(n-2, true);
    if (flag) res += solve(n-3, false);
    dp[flag][n] = res;
    return res;
}
int main()
{
#ifdef local
    freopen("f.txt", "r", stdin);
#endif

    int n;
    while (cin >> n) {
        for (int i = 0; i < 56; i++)
            dp[0][i] = dp[1][i] = 0;
        cout << solve(n, true) << endl;
    }
    return 0;
}
