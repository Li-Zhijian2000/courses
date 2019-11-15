// #define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 9;
int ans[maxn];
int n, m;
void dfs(int cur) {
  if (cur == m) {
    for (int i = 0; i < m; i++) cout << ans[i] << " ";
    cout << '\n';
  }
  else {
    for (int i = 1; i <= n; i++) {
      int ok = 1;
      for (int j = 0; j < cur; j++)
        if (ans[j] == i) ok = 0;
      if (ok) {
        ans[cur] = i;
        dfs(cur + 1);
      }
    }
  }
}
int main() {
#ifdef local
  freopen("b.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin >> n >> m;
  dfs(0);
  return 0;
}
