// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1005;
int a[maxn];

int main() {
#ifdef local
    freopen("a.txt", "r", stdin);
#endif
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < m; i++)
            scanf("%d", a + i);
        sort(a, a + m, [](const int& lhs, const int& rhs) {
            return lhs > rhs;
        });
        int ares = 0, sres = 0;
        for (int i = 0; i < m; i += 2) {
            ares += a[i];
            sres += a[i+1];
        }
        const char *res = ares > sres ? "HuiGeNB" : 
                    ares < sres ? "ShuiShuiNB" : 
                    "NBNB";
        puts(res);
    }
    return 0;
}
