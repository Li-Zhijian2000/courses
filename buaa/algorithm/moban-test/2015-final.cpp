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
typedef vector<vi> vvi;
typedef vector<long> vl;
typedef vector<vl> vvl;
typedef pair<int, int> pii;
typedef pair<long, long> pll;

void a() {
  int n, k;
  while (cin >> n >> k) {
    vi sum(n);
    for (int i = 1; i < n; i++) {
      cin >> sum[i];
      sum[i] += sum[i-1];
    }
    vi v;
    for (int i = 0; i < n-1; i++)
      for (int j = i + 1; j < n; j++) {
        int x = sum[j] - sum[i];
        v.push_back(x);
        v.push_back(x);
      }
    nth_element(v.begin(), v.begin() + k-1, v.end());
    // cout << v.size() << '\n';
    cout << v[k-1] << '\n';
  }
}
void c() {
  int n;
  while (cin >> n) {
    vi v(n);
    for (int i = 0; i < n; i++) cin >> v[i]; 
    long ans;
    {
      priority_queue<long, vector<long>, greater<long>> pq;
      for (int i = 0; i < n; i++) pq.push(v[i]);
      while (pq.size() > 1) {
        long t1 = pq.top(); pq.pop();
        long t2 = pq.top(); pq.pop();
        pq.push(t1 * t2 + 1);
      }     
      ans = pq.top();
    }
    {
      priority_queue<long> pq;
      for (int i = 0; i < n; i++) pq.push(v[i]);
      while (pq.size() > 1) {
        long t1 = pq.top(); pq.pop();
        long t2 = pq.top(); pq.pop();
        pq.push(t1 * t2 + 1);
      }
      ans -= pq.top();
    }
    cout << ans << '\n';
  }
}
void d() {
  function<int(int a, int b)> gcd = [&](int a, int b)->int { return !b ? a : gcd(b, a%b); };
  int a, b;
  while (cin >> a >> b) {
    cout << gcd(a, b) << '\n';
  }
}
void e() {
  // 体力、距离、时间
  int m, s, t;
  while (cin >> m >> s >> t) {
    int i, ans = 0;
    for (i = 1; i <= t; i++) {
      if (m >= 10) {
        ans += 60;
        m -= 10;
      }
      else if (s-i + m >= 10 && ) ans += 17;
      else m += 4;
      if (ans >= s) break;
      m++;
    }
    if (ans >= s) cout << "Yes\n" << i << '\n';
    else cout << "No\n" << ans << '\n';
  }
}
void f() {
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<string> vs(n);
    vi v(n);
    for (int i = 0; i < n; i++) {
      cin >> vs[i];
      v[i] = i;
    }
    long ans = 0;
    function<void(int lo, int hi)> MergeSort = [&](int lo, int hi)->void {
      if (hi - lo < 2) return;
      int mi = lo + hi >> 1;
      MergeSort(lo, mi), MergeSort(mi, hi);

      vi left(v.begin()+lo, v.begin()+mi), right(v.begin()+mi, v.begin()+hi);
      int n = left.size(), m = right.size();
      for (int i = 0, j = 0; i < n || j < m; ) {
        if (i < n && (j == m || vs[left[i]] <= vs[right[j]])) v[lo++] = left[i++];
        if (j < m && (i == n || vs[left[i]] > vs[right[j]])) {
          v[lo++] = right[j++];
          ans += n - i;
        }
      }
    };
    MergeSort(0, n);
    cout << ans << '\n';
  }

}
void g() {
  const int mod = 10007;
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vi a(n+1);
    for (int i = 0; i <= n; i++) cin >> a[i];
    int m; cin >> m;
    vi b(m+1);
    for (int i = 0; i <= m; i++) cin >> b[i];

    int c; cin >> c;
    while (c--) {
      int x, y; cin >> x >> y;
      int ans1 = a[0], ans2 = b[0];
      int powx = 1, powy = 1;
      for (int i = 1; i <= n; i++) {
        powx *= x;
        powx %= mod;
        ans1 += powx * a[i];
        ans1 %= mod;
      }
      for (int i = 1; i <= m; i++) {
        powy *= y;
        powy %= mod;
        ans2 += powy * b[i];
        ans2 %= mod;
      }
      cout << (ans1 * ans2 % mod) << '\n';
    }

  }
}
void i();
void j() {
  const int maxn = 505;
  int n, k;
  while (cin >> n >> k) {
    vvl dp(n+1, vl(10000));
    vi v(n+1);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
      cin >> v[i];
      sum += v[i];
      dp[i][v[i]] = 1;
    }
    for (int i = 1; i <= n; i++)
      for (int j = 0; j <= sum; j++)
        if (j >= v[i]) dp[i][j] += dp[i-1][j-v[i]] + dp[i-1][j];
        else dp[i][j] += dp[i-1][j];
    long ans = 0;
    for (int i = k; i <= sum; i++) ans += dp[n][i];
    cout << ans << '\n';
  }
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // a();
  // c();
  // d();
  e();
  // f();
  // g();
  // h();
  // i();
  // j();
  return 0;
}

const double eps = 1e-8;
int dcmp(double x) {
  if (fabs(x) < eps) return 0;
  else return x < 0 ? -1 : 1;
}
typedef struct Point {
  double x, y;
  Point(double x=0, double y=0): x(x), y(y) {}
} Vector;
Vector operator +(Vector a, Vector b) { return Vector(a.x+b.x, a.y+b.y); }
Vector operator -(Point a, Point b) { return Vector(a.x-b.x, a.y-b.y); }

double Dot(Vector a, Vector b) { return a.x*b.x + a.y*b.y; }
double Cross(Vector a, Vector b) { return a.x*b.y - a.y*b.x; }
double Length(Vector n) { return sqrt(Dot(n, n)); }

void i() {
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<Point> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    sort(all(v), [&](Point a, Point b) {
      Point p0(0, 0);
      int flag = dcmp(Cross(a-p0, b-p0));
      return flag ? flag > 0 : Length(a-p0) < Length(b-p0);
    });
    int i;
    for (i = 2; i < n; i++) {
      if (Cross(v[i-1]-v[i-2], v[i]-v[i-1])) break;
    }
    cout << (i == n ? "Yes" : "No") << '\n';
  }
}


