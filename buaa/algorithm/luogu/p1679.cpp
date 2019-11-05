// #define local
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

long pow4(int x) { long t = x * x; return t * t; }
const long max_cost = 1e5 + 5;
const long inf = 1e9;
long dp[max_cost];

int main()
{
#ifdef local
    freopen("p1679.txt", "r", stdin);
#endif

    long n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        dp[i] = inf;

    vector<long> cost(1, 0);
    for (int i = 1; pow4(i) <= n; i++)
        cost.push_back(pow4(i));
    for (int i = 1; i < cost.size(); i++)
        for (long c = cost[i]; c <= n; c++) {
            dp[c] = min(dp[c], dp[c - cost[i]] + 1);
            // if (dp[c] < 1000) cout << dp[c] << " " << cost[i] << endl;
        }
            
    cout << dp[n] << endl;
    return 0;
}