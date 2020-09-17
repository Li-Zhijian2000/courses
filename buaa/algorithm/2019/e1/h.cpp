// #define local
#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_set>
using namespace std;

list<string> nodes;
unordered_set<string> all_nodes;
int u[15], v[15];

void init(int n)
{
    nodes.clear();
    all_nodes.clear();

    for (int i = 1; i <= n; i++) {
        string s = "";
        for (int j = 1; j <= n; j++)
            if (j != i) s += j + '0';
        
        for (int j = 0; j <= s.size(); j++) {
            string tmp = s.substr(0, j-0) + string(1, i+'0') + s.substr(j, s.size() - j);
            if (all_nodes.find(tmp) == all_nodes.end()) {
                all_nodes.insert(tmp);
                nodes.push_back(tmp);
            }
        }
    }
}

int main()
{
#ifdef local
    freopen("h.txt", "r", stdin);
#endif
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < k; i++) {
            cin >> u[i] >> v[i];
            u[i]--, v[i]--;
        }
            
        
        init(n);

        for (int i = k-1; i >= 0; i--) {
            int n = nodes.size();
            auto p = nodes.begin();
            for (int j = 0; j < n; j++) {
                string s = *p;
                if (s[u[i]] < s[v[i]]) {
                    string tmp = s;
                    swap(tmp[u[i]], tmp[v[i]]);
                    nodes.push_back(tmp);
                    p++;
                }
                else {
                    auto tmp = p;
                    p++;
                    nodes.erase(tmp);
                }
            }
        }
        cout << nodes.size() << endl;        
    }
    return 0;
}
