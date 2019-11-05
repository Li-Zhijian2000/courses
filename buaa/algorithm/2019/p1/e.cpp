//#define local
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Point {
    int pos;
    int flag;
    Point(int p=0, int f=0): pos(p), flag(f) {}
    bool operator< (const Point& rhs) { return this->pos < rhs.pos; }
}a[300005];
int main()
{
#ifdef local
    freopen("e.txt", "r", stdin);
#endif

    int n, k;
    while (~scanf("%d%d", &n, &k)) {
        int l, r;
        for (int i = 0; i < k; i++) {
            scanf("%d%d", &l, &r);
            a[i] = Point(l, 1);
            a[i+k] = Point(r+1, -1); 
        }
        sort(a, a + 2*k);
        long res = 0, sum = 0;
        for (int i = 0; i < 2 * k; i++) {
            int lo = a[i].pos;
            while (a[i].pos == a[i+1].pos) {
                sum += a[i].flag;
                i++;
            }
            sum += a[i].flag;
            res += (sum % 2) * (a[i+1].pos - lo);
        }
        printf("%ld\n", res);
    }
    return 0;
}
