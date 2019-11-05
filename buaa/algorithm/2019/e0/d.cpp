// #define local
#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = 200000 + 5;
// int pre[maxn], nxt[maxn];
bool is_light[maxn];
int fa[maxn];

int find(int i)
{
    while (i != fa[i]) {
        fa[i] = fa[fa[i]];
        i = fa[i];
    }
    return i;
}

int main()
{
#ifdef local
    freopen("d.txt", "r", stdin);
#endif
    int n, m, total;
    cin >> n >> m;
    total = n;
    for (int i = 1; i <= n + 1; i++)
        fa[i] = i;

    while (m--) {
        int lo, hi;
        cin >> lo >> hi;

        for (int i = lo; i <= hi; ) {
            if (i == find(i)) {
                fa[i] = i + 1;
                total--;
            }
            i = fa[i];
        }
        cout << total << endl;
    }
}
