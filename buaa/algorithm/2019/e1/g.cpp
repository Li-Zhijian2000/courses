// #define local
#include <iostream>
#include <algorithm>
using namespace std;

const long mod = 987654323;

long pow(long q, long n)
{
    if (n == 1) return q;

    if (n % 2) return (q * pow(q, n-1)) % mod;
    else {
        long t = pow(q, n / 2);
        return (t * t) % mod;
    }
}
long sum(long n, long a1, long q)
{
    if (n == 1) return a1;

    if (n % 2) return (sum(n-1, a1, q) + a1 * pow(q, n-1)) % mod;
    
    return sum(n/2, a1, q) * (1 + pow(q, n/2)) % mod;
}
int main()
{
#ifdef local
    freopen("g.txt", "r", stdin);
#endif

    long t;
    cin >> t;
    while (t--) {
        long n, a1, q;
        cin >> n >> a1 >> q;
        if (q == 1) cout << (n * a1 % mod) << endl;
        else cout << sum(n, a1, q) << endl;
    }
    return 0;
}
