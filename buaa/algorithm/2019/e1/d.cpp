// #define local
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> path;

void dfs(int x, int n)
{
    path.push_back(x);
    
    for (int i = 1; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " ";
        else cout << endl;
    }

    for (int i = x + 1; i <= n; i++)
        dfs(i, n);
    
    path.pop_back();
}
int main()
{
#ifdef local
    freopen("d.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    dfs(0, n);
    return 0;
}
