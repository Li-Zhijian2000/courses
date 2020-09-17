// #define local
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1e6+4;
int res[maxn];

void dfs(int i)
{
    int t = 2 * i;
    if (t + 1 < maxn) {
        res[t] = res[t+1] = res[i] + 1;
        dfs(t);
        dfs(t + 1);
    }

}
int main()
{
#ifdef local
    freopen("b.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    res[1] = 1;
    dfs(1);

    int n;
    while (cin >> n) {
        cout << res[n] << endl;
    }
    return 0;
}
