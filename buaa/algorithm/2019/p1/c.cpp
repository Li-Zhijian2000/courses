// #define local
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 6010;
queue<string> str;
char res[maxn];
bool solve()
{
    if (str.empty()) return false;
    if (str.front() == "int") {
        str.pop();
        strcat(res, "int");
        return true;
    }
    if (str.front() == "pair") {
        str.pop();
        strcat(res, "pair<");
        int flag = true;
        flag &= solve();
        strcat(res, ",");
        flag &= solve();
        strcat(res, ">");
        return flag;
    }
    return false;
}
int main()
{
#ifdef local
    freopen("c.txt", "r", stdin);
#endif

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        while (!str.empty()) str.pop();
        memset(res, 0, sizeof(res));
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            str.push(s);
        }
        if (n == 1) cout << "Error occurred" << endl;
        else if (solve())
            printf("%s\n", res);
        else cout << "Error occurred" << endl;
    }
    return 0;
}
