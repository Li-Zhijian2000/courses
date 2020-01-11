#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

#define all(x) x.begin(), x.end()

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<long> vl;
typedef vector<vector<long>> vvl;

void a() {
  int n; cin >> n;
  vi v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
function<void(vi::iterator, vi::iterator)> QuickSort;
// [first, last)
QuickSort = [&](vi::iterator first, vi::iterator last)->void {
  if (first >= last) return;
  auto mid = first + (last - first) / 2;
  nth_element(first, mid, last);

  QuickSort(first, mid);
  QuickSort(mid+1, last);
};
  QuickSort(all(v));
  for (int i = 0; i < n; i++) cout << v[i] << ' ';
  cout << '\n';
}

const int inf = 0x3f3f3f3f;
void b() {
  int n;
  while (cin >> n) {
    vi dp(n+1);
    for (int i = 1; i <= n; i++) cin >> dp[i];
    dp[0] = inf;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j < i; j++)
        dp[i] = min(dp[i], dp[j] + dp[i-j]);
    cout << dp[n] << '\n';
  }
}
void c() {
  int n;
  while (cin >> n) {
    vvi dp(n+1, vi(n+1, inf)), pa(n+1, vi(n+1)), vis(n+1, vi(n+1));
    // Ai 的大小为 pi-1 * pi
    vi p(n+1);
    for (int i = 0; i <= n; i++) {
      cin >> p[i];
      dp[i][i] = 0;
      vis[i][i] = 1;
    }
    
    function<int(int i, int j)> solve = [&](int i, int j)->int {
      if (vis[i][j]) return dp[i][j];
      vis[i][j] = 1;
      for (int k = i; k < j; k++) {
        int t = solve(i, k) + solve(k+1, j) + p[i-1] * p[k] * p[j];
        // 优先计算左边的矩阵
        if (t <= dp[i][j]) {
          dp[i][j] = t;
          pa[i][j] = k;
        }
      }
      return dp[i][j];
    };
    function<void(int i, int j)> PrintAns = [&](int i, int j)->void {
      if (i == j) {
        cout << 'A' << i;
        return;
      }
      cout << '(';
      PrintAns(i, pa[i][j]);
      PrintAns(pa[i][j]+1, j);
      cout << ')';
    };
    cout << solve(1, n) << '\n';
    PrintAns(1, n);
    cout << '\n';
  }
}
void d() {
  string s1, s2; 
  while (cin >> s1 >> s2) {
    int n = s1.size(), m = s2.size();
    vvi dp(n+1, vi(m+1));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
        if (s1[i] == s2[j]) dp[i+1][j+1] = max(dp[i+1][j+1],  dp[i][j] + 1);
      }

    vector<string> ans;
    function<void(int i, int j, string s)> PrintAns = [&](int i, int j, string s)->void {
      if (i < 0 || j < 0) return;
      if (s1[i] == s2[j]) {
        s += s1[i];
        if (s.size() == dp[n][m]) {
          reverse(all(s));
          ans.push_back(s);
        }
        else PrintAns(i-1, j-1, s);
      }
      else {
        if (dp[i][j+1] <= dp[i+1][j]) 
          PrintAns(i, j-1, s);
        if (dp[i+1][j] <= dp[i][j+1]) 
          PrintAns(i-1, j, s);
      }
    };
    PrintAns(n-1, m-1, "");
    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());
    for (string s: ans) cout << s << '\n';
  }
}
void e() {
  int n; cin >> n;
  vi p(n+1), q(n+1);
  vvi w(n+1, vi(n+1)), dp(n+1, vi(n+1, inf)), vis(n+1, vi(n+1));
  for (int i = 1; i <= n; i++) cin >> p[i];
  for (int i = 0; i <= n; i++) cin >> q[i];
  for (int i = 1; i <= n; i++) 
    w[i][i-1] = q[i-1];
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++) 
      w[i][j] = w[i][j-1] + p[j] + q[j];

  function<int(int i, int j)> solve = [&](int i, int j)->int{
    if (j == i-1) return q[j];
    if (vis[i][j]) return dp[i][j];
    vis[i][j] = 1;
    for (int k = i; k <= j; k++) 
      dp[i][j] = min(dp[i][j], solve(i, k-1) + solve(k+1, j) + w[i][j]);
    return dp[i][j];
  };
  cout << solve(1, n) << '\n';
}
void f() {
  // s2 < s1
  string s1, s2; cin >> s1 >> s2;

  auto PreFunc = [&](string s) {
    int m = s.size();
    vi f(m);
    f[0] = -1;
    int j = -1;
    for (int i = 1; i < m; i++) {
      while (j >= 0 && s[j+1] != s[i]) j = f[j];
      if (s[j+1] == s[i]) j++;
      f[i] = j;
    }
    return f;
  };
  auto KMP = [&](string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vi f = PreFunc(s2), ans;
    int j = -1;
    for (int i = 0; i < n; i++) {
      while (j >= 0 && s2[j+1] != s1[i]) j = f[j];
      if (s2[j+1] == s1[i]) j++;
      if (j == m-1) {
        ans.push_back(i - m + 1);
        j = f[j];
      }
    }
    return ans;
  };
  vi ans = KMP(s1, s2);
  

}
void FracPack() {
  typedef pair<double, double> pdd;
  int n;
  double t;
  while (cin >> n >> t) {
    vector<pdd> vp(n);
    for (int i = 0; i < n; i++) cin >> vp[i].first >> vp[i].second;
    sort(all(vp), [](pdd a, pdd b) { return a.second / a.first > b.second / b.first; });
    double ans = 0;
    for (int i = 0; i < n; i++) {
      double c = vp[i].first, w = vp[i].second;
      if (t >= c) {
        t -= c;
        ans += w;
      }
      else {
        ans += t * w / c;
        break;
      }
    }
    printf("%.2lf\n", ans);
  }
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // a();
  // b();
  // c();
  // d();
  // e();`
  // f();
  FracPack();
  return 0;
}