// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1e5+5;
int a[maxn];
int main() {
#ifdef local
    freopen("e.txt", "r", stdin);
#endif
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++)
            scanf("%d", a + i);
        nth_element(a, a + (n-1)/2, a + n);
        printf("%d\n", a[(n-1)/2]);
    }
    return 0;
}
