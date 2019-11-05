// #define local
#include <iostream>
#include <algorithm>
using namespace std;

const long maxn = 1e6 + 5;
long a[maxn], sum[maxn];

int main()
{
#ifdef local
    freopen("b.txt", "r", stdin);
#endif
    long n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    long max_sum_k = -1e13;
    for (int i = k; i <= n; i++)
        max_sum_k = max(max_sum_k, sum[i] - sum[i-k]);
    cout << max_sum_k << endl;
    return 0;
}
