// #define local
#include <iostream>
#include <algorithm>
using namespace std;
int a[100000];

int main()
{
#ifdef local
    freopen("f.txt", "r", stdin);
#endif

    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++) 
            cin >> a[i];
        sort(a, a+n);
        for (int i = 0; i < n; i++)
            cout << a[i] << (i != n-1? " " : "\n");
    }
    return 0;
}
