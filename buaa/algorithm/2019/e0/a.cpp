// #define local
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

map<int, int> m;

int main()
{
#ifdef local
    freopen("a.txt", "r", stdin);
#endif

    int n;
    long long total = 0;
    map<int, int> m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        int height;
        cin >> x;
        auto p = m.equal_range(x);
        if (p.first == m.begin())
            p.first = m.end();
        else if (!m.empty())
            --p.first;
        
        int left = (p.first != m.end())? p.first->second : -1;
        int right = (p.second != m.end())? p.second->second : -1;
        height = max(left, right) + 1;

        m.insert({x, height});
        total += height;
        cout << total << endl;
    }
    return 0;
}