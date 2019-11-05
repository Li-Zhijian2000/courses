// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e6+5;
int sum[maxn];

int main()
{
#ifdef local
    freopen("c.txt", "r", stdin);
#endif

    int n;
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            sum[i] = sum[i-1] ^ x;
        }

        int k;
        scanf("%d", &k);
        while (k--) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x > y) swap(x, y);
            printf("%d\n", sum[y] ^ sum[x-1]);
        }
    }
    return 0;
}
