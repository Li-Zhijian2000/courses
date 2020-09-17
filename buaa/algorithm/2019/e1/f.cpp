// #define local
#include <iostream>
#include <algorithm>
using namespace std;

int fib[40];

int main()
{
#ifdef local
    freopen("f.txt", "r", stdin);
#endif

    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= 35; i++)
        fib[i] = fib[i - 2] + fib[i - 1];
    
    long i;
    while (cin >> i)
        cout << fib[i] << endl;
    return 0;
}
