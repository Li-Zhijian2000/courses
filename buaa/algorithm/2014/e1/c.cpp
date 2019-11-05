// #define local
#include <iostream>
#include <algorithm>
using namespace std;

bool solve(int a, int b)
{
    if (a < b) return solve(b, a);

    if (!(a % b)) return true;
    if (a > 2 * b) return true;

    return !solve(a-b, b);
}
int main()
{
#ifdef local
    freopen("c.txt", "r", stdin);
#endif

    int a, b;
    while (cin >> a >> b) {
        cout << (solve(a, b)? "Nova" : "LaoWang") << endl;
    }
    return 0;
}
