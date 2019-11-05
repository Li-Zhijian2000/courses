#define local
#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
#ifdef local
    freopen("b.txt", "r", stdin);
#endif

    int n;
    while (~scanf("%d", &n)) {
        printf("%ld\n", (f0[n]+f1[n]) % mod);
    }
    return 0;
}
