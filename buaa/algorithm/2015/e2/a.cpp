// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int maxn = 1e6+5;
bool vis[maxn];
int sum[maxn];
int main() {
#ifdef local
    freopen("a.txt", "r", stdin);
#endif

    int m = sqrt(maxn + 0.5);
    for (int i = 2; i < m; i++)
        if (!vis[i])
            for (int j = i*i; j < maxn; j += i)
                vis[j] = true;
    
    for (int i = 2; i < maxn; i++)
        sum[i] = sum[i-1] + !vis[i];
    
    int n;
    while (~scanf("%d", &n))
        printf("%d\n", sum[n]);
    return 0;
}
