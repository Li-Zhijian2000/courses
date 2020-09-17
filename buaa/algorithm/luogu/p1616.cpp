// #define local
#include <iostream>
#include <algorithm>
using namespace std;

const long max_cost = 1e5 + 5;
const long maxn = 1e4 + 5;
long dp[max_cost], cost[maxn], weight[maxn];

int main()
{
#ifdef local
    freopen("p1616.txt", "r", stdin);
#endif

    long total_cost, n;
    cin >> total_cost >> n;
    for (int i = 1; i <= n; i++)
        cin >> cost[i] >> weight[i];
    
    for (int i = 1; i <= n; i++)
        for (long c = cost[i]; c <= total_cost; c++)
            dp[c] = max(dp[c], dp[c - cost[i]] + weight[i]);
    
    cout << dp[total_cost] << endl;
    return 0;
}