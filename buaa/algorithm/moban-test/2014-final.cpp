#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;
#define all(x) x.begin(), x.end()

const int inf = 0x3f3f3f3f;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
typedef pair<long, long> pll;

void a() {
  int n, k;
  while (cin >> n >> k) {
    vector<pii> vp(n);
    for (int i = 0; i < n; i++) {
      cin >> vp[i].first;
      vp[i].second = i + 1;
    }
    sort(all(vp));
    pii x = vp[n-k];
    cout << "map" << x.second << " : " << x.first << '\n';
  }
}
void b() {
  int n; 
  while (cin >> n) {
    vi v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    int k; cin >> k;
    auto p = upper_bound(all(v), k);
    cout << *p << '\n';
  }
}
// void d() {
//   int n, k;
//   while (cin >> n >> k) {
//     vi v(n);
//     vvi dp(2, vi(n));
//     for (int i = 0; i < n; i++) cin >> v[i];
//     int ans = 0, cur = 0;

//   }  
// }
void d() {
  int n, k;
  while (cin >> n >> k) {
    vi v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(all(v), [](int a, int b) { return a > b; });
    vi sum(n+1);
    for (int i = n-1; i >= 0; i--) sum[i] = sum[i+1] + v[i];
    int ans = 0, cur = 0;
    function<void(int u)> dfs = [&](int u) {
      if (u == n) return;
      if (cur >= k) {
        ans += pow(2, n-u) + 0.5;
        return;
      }
      if (k - cur > sum[u]) return;
      dfs(u+1);
      cur += v[u];
      if (cur >= k) ans++;
      dfs(u+1);
      cur -= v[u];
    };
    dfs(0);
    cout << ans << '\n';
  }
}
#include <stack>
void e() {
  int n, k;
  while (cin >> n >> k) {
    while (k--) {
      vi v(n+1);
      for (int i = 1; i <= n; i++) cin >> v[i];
      int flag = 1, t = 0;
      stack<int> s;
      s.push(0);
      for (int i = 1; i <= n; i++) {
        if (v[i] > t) {
          for (int j = t+1; j < v[i]; j++) s.push(j);
          t = v[i];
        }
        else if (v[i] < v[i-1] && v[i] == s.top()) s.pop();
        else {
          flag = 0;
          break;
        }
      }
      cout << (flag ? "YES" : "NO") << '\n';
    }
    cout << '\n';
  }
}
void f() {
  int n;
  while (cin >> n) {
    auto bin = [&](int x) {
      vi v;
      while (x > 0) {
        v.push_back(x%2);
        x /= 2;
      }
      return v;
    };
    vi v = bin(n);
    int c1 = count_if(all(v), [](int a) { return a == 1; });
    int c2 = 0;
    for (int i = 0; i < v.size(); i++)
      if (v[i] == 0) 
        for (int j = i+1; j < v.size(); j++) 
          if (v[j] == 1) c2++; 
    // cout << c1 << ' ' << c2 << '\n';
    cout << (!((n-1)&n) || (c1+c2) % 2 ? "xiaoming" : "xiaoyao") << '\n';
  }
}
void h() {
  int n, m;
  while (cin >> n >> m) {
    vector<vector<char>> map(n, vector<char>(m));
    vvi vis(n, vi(m));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        cin >> map[i][j];
    
    function<void(int x, int y)> dfs = [&](int x, int y)->void {
      vis[x][y] = 1;
      int step[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
      for (int i = 0; i < 4; i++) {
        int nx = x + step[i][0], ny = y + step[i][1];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && map[nx][ny] == map[x][y]) dfs(nx, ny);
      }
    };
    long ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) 
        if (!vis[i][j]) {
          dfs(i, j);
          ans++;
        }
    cout << ans << '\n';
  }
}
int main() {
#ifdef local
  // freopen("input.txt", "r", stdin);
#endif
  // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // a();
  // b();
  // c();
  // d();
  // e();
  f();
  // g();
  // h();
  return 0;
}