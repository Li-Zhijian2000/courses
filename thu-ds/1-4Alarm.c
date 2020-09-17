#include <stdio.h>
#define maxn 200000 + 5
const double eps = 1e-12;

typedef struct 
{
    int a, b;
}line;

line lines[maxn];

int less(int x, int y, line A)
{
    double a = A.a, b = A.b;
    return x / a + y / b - 1 <=  eps && !(1 - x / a - y / b < eps);
}

int linebsearch(int x, int y, int n) 
{
    int lo = 0, hi = n, mi;
    while (lo < hi) {
        mi = (lo + hi) / 2;
        less(x, y, lines[mi]) ? (hi = mi) : (lo = mi + 1);
    }
    return hi;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        lines[i].a = a;
        lines[i].b = b;
    }

    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", linebsearch(x, y, n));
    }
    return 0;
}
