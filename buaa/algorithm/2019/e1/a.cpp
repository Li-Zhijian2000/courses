// #define local
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
#ifdef local
    freopen("a.txt", "r", stdin);
#endif

    long t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << (((n & 0xFFFF) << 16) | (n >> 16)) << endl;
    }
    return 0;
}
