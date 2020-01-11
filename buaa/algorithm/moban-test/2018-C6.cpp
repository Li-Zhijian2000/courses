// C6-2018级算法第六次上机
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;

const int inf = 0x3f3f3f3f;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

// dp，刷表，没到一个点，更新该点能到的地方，若能到之处为'*'，则不更新
void c() {
  // n * m
  int n, m; cin >> n >> m;
  // (a, 0), (b, m+1)
  int h, a, b; cin >> h >> a >> b;

  vvi map(n+2, vi(m+2)), dp(n+2, vi(m+2, inf));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c; cin >> c;
      map[i][j] = c;
    }
  }

  dp[a][0] = 0;
  map[b][m+1] = '0';
  // 一列一列更新
  for (int j = 0; j <= m; j++) {
    for (int i = 1; i <= n; i++) {
      // 刷表
      for (int k = -1; k <= 1; k++) {
        int& t = dp[i+k][j+1];
        int& m = map[i+k][j+1];
        if (m != '*') t = min(t, dp[i][j] + m - '0');
      }
    }
  }
  if (dp[b][m+1] < h) cout << h - dp[b][m+1] << '\n';
  else cout << "doctor win\n";
}
// 二分，选定跨度x，看该跨度能否过河，注意应为lower_bound
// 与路由器那道题几乎一样
void d() {
  // 河宽，n个石砖，最多m步
    int l, n, m; 
    while (cin >> l >> n >> m) {
    vi loc(n+2);
    loc[0] = 0; loc[n+1] = l;
    for (int i = 1; i <= n; i++) cin >> loc[i];
    n = loc.size();
    sort(loc.begin(), loc.begin()+n);

    auto ok = [&](long x) {
      // 要跨最后一步
      int t = 1, i = 0;
      // 防止重叠
      while ((i = upper_bound(loc.begin(), loc.begin() + n, loc[i] + x) - loc.begin() - 1) 
             != n - 1) {
        t++;
        if (t > m) return false;
      }
      return true;
    };
    long lo = loc[0], hi = loc[n-1] + 1;
    while (lo < hi) {
      long mi = lo + hi >> 1;
      ok(mi) ? hi = mi : lo = mi + 1;
    }
    cout << lo << '\n';
  }
}
// 存一下值和下标，<𝑎_𝑖,𝑖>
// 按照值的大小由小到大排序
// 然后顺序遍历，记录一下最大的下标maxi。
// 𝑎𝑛𝑠=max⁡(𝑎𝑛𝑠,𝑚𝑎𝑥𝑖− 𝐴[𝑖].𝑠𝑒𝑐𝑜𝑛𝑑)
void g() {
  int n; cin >> n;
  vector<pii> v(n);
  for (int i = 0; i < n; i++) {
    int a; cin >> a;
    v[i] = pii(a, i);
  }
  sort(v.begin(), v.begin() + n);
  auto p = max_element(v.begin(), v.begin() + n, [](pii a, pii b) { return a.second < b.second; });
  int ans = 0, maxi = p->second;
  for (; p != v.end(); ++p) ans = max(ans, maxi - p->second);
  cout << ans << '\n';
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // c();
  d();
  // g();
  return 0;
}