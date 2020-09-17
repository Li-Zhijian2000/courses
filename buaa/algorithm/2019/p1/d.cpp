// #define local
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<long, long> pll;
long pow2(long a, long b) {
    long t = a - b;
    return t * t;
}
pll solve(long i, int n) {
    if (n < 1) return pll(1, 1);
    long halfside = 1L << (n-1), sz = pow2(halfside << 1, 0);
    if (i <= (sz >> 2)) {
        pll subpos = solve(i, n-1);
        return pll(subpos.second, subpos.first);
    }
    else if (i <= (sz >> 1)) {
        pll subpos = solve(i - (sz >> 2), n-1);
        return pll(subpos.first+halfside, subpos.second);
    }
    else if (i <= ((sz >> 2) * 3)) {
        pll subpos = solve(i - (sz >> 1), n-1);
        return pll(subpos.first+halfside, subpos.second+halfside);
    }
    else {
        pll subpos = solve(i - (sz >> 2) * 3, n-1);
        return pll(halfside+1-subpos.second, halfside+1-subpos.first+halfside);
    }
}
int main() {
#ifdef local
    freopen("d.txt", "r", stdin);
#endif

    int n;
    long a, b;
    while (~scanf("%d%ld%ld", &n, &a, &b)) {
        pll apos = solve(a, n), bpos = solve(b, n);
        // cout << apos.first << ", " << apos.second << ")(" << bpos.first << ", " << bpos.second << endl;
        printf("%ld\n", pow2(apos.first, bpos.first) + pow2(apos.second, bpos.second));
    }
    return 0;
}
