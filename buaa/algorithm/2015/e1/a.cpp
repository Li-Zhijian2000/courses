// #define local
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 10005;
long xpow[maxn];

const long mod = 1e6+7;

int main()
{
#ifdef local
    freopen("a.txt", "r", stdin);
#endif

    xpow[0] = 1;
    long n, x, t, cse = 0;
    while (cin >> n >> x >> t) {
        cse++;
        printf("Case #%ld:\n", cse);
        for (int i = 1; i <= n; i++)
            xpow[i] = (x * xpow[i-1]) % mod;
        
        while (t--) {
            long res = 0;
            for (int i = 0; i <= n; i++) {
                long ti;
                cin >> ti;
                res += (ti * xpow[i]) % mod;
                res %= mod;
            }
            cout << res << endl;
        }
    }
    return 0;
}
