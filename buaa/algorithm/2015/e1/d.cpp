// #define local
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e6+5;
int price[maxn];

int main()
{
#ifdef local
    freopen("d.txt", "r", stdin);
#endif

    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++)
            scanf("%d", price + i);
        
        int cur_min = 0x7f7f7f7f, res = 0;
        for (int i = 0; i < n; i++) {
            cur_min = min(cur_min, price[i]);
            res = max(res, price[i] - cur_min);
        }
        if (res > 0) cout << res << endl;
        else cout << "No solution" << endl;
    }

    return 0;
}
