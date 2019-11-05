// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e3+5;
long value[maxn];

int main() {
#ifdef local
    freopen("a.txt", "r", stdin);
#endif
    int t, cse = 0;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        memset(value, 0x7f, (m+1) * sizeof(value[0]));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                long d;
                scanf("%ld", &d);
                value[j] = min(value[j], d);
            }
        long res = 0;
        for (int i = 0; i < m; i++)
            res += value[i];
        printf("Case #%d: %ld\n", ++cse, res);
    }
    return 0;
}
