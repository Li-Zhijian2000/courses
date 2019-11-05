// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 25005;
int a[maxn], dp[maxn];

int main() {
#ifdef local
  freopen("b.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    dp[i] = 1;
    cin >> a[i];
  }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j < i; j++)
      if (a[j] < a[i])
        dp[i] = max(dp[i], dp[j]+1);
  
  int res = 0;
  for (int i = 1; i <= n; i++)
    res = max(res, dp[i]);
  cout << res << '\n';
  return 0;
}
