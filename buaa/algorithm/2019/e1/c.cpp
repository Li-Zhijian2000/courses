// #define local
#include <iostream>
#include <algorithm>
using namespace std;

const long maxn = 1e6 + 5;
long a[maxn], b[maxn];

int main()
{
#ifdef local
    freopen("c.txt", "r", stdin);
#endif

    long n, k;
    cin >> n >> k;
    while (k--) {
        long x, y;
        cin >> x >> y;
        b[x]++, b[x + y]--;
    }

    long max_sum = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = a[i - 1] + b[i];
        max_sum = max(max_sum, a[i]);
    }
    cout << max_sum << endl;
    return 0;
}
