#define local
#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = 32;
long long catalan[maxn] = {1};

int main()
{
#ifdef local
    freopen("e.txt", "r", stdin);
#endif

    for (int i = 0; i < maxn - 1; i++)
        catalan[i + 1] = catalan[i] * 2 * (2*i+1) / (i+2);

    int n;
    while (cin >> n)
        cout << catalan[n] << endl;
    return 0;
}