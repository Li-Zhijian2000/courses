#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e5+5;
int a[maxn];

int partition(int* A, int lo, int hi) {
    swap(A[lo], A[lo + rand()%(hi - lo)]);
    int p = lo;
    while (lo < hi) {
        while (lo < hi && a[hi] > a[p]) 
            hi--;
        while (lo < hi && a[lo] < a[p]) 
            lo++;

        swap(a[lo], lo != hi ? a[hi] : a[p]);
        if (hi - lo >= 4) lo++, hi--;
    }
    return lo;
}
void quick_sort(int* A, int lo, int hi) {
    if (hi - lo < 2) return;
    // puts("yes");
    int mi = partition(A, lo, hi - 1);
    // puts("yes2");
    quick_sort(A, lo, mi), quick_sort(A, mi + 1, hi);
}
int main() {
#ifdef local
    freopen("p1177.txt", "r", stdin);
#endif

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    quick_sort(a, 0, n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    putchar('\n');
    return 0;
}