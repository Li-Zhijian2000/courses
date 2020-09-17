#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 65;
int n;
long res;

void solve2(int *ori, int *des, int x)
{
    if (!x) return;
    if (ori[x] == des[x]) return solve2(ori, des, x-1);
    int tmp[x];
    for (int i = 1; i < x; i++) tmp[i] = 6-ori[x]-des[x];
    res += (1L << (x-1));
    solve2(tmp, des, x-1);
}
void solve(int *ori, int *des, int x)
{
    if (!x) return;
    if (ori[x] == des[x]) return solve(ori, des, x-1);
    int tmp[x];
    for (int i = 1; i < x; i++) tmp[i] = 6-ori[x]-des[x];
    solve(ori, tmp, x-1);
    res++;
    //solve(tmp, des, x-1);
    solve(tmp, des, x-1);
}

int main()
{
#ifdef local
    freopen("f.txt", "r", stdin);
#endif

    int ori[maxn], des[maxn];
    while (cin >> n) {
        if (!n) break;
        res = 0;
        for (int i = 0; i < n; i++)
            cin >> ori[i+1];
        for (int i = 0; i < n; i++)
            cin >> des[i+1];
        
        solve(ori, des, n);
        cout << res << endl;
    }
    return 0;
}
