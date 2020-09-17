// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int fib[35];


int main() {
#ifdef local
    freopen("e.txt", "r", stdin);
#endif
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < 35; i++)
        fib[i] = fib[i-1] + fib[i-2];
    
    int n;
    while (~scanf("%d", &n))
        printf("%d\n", fib[n]);
    return 0;
}
