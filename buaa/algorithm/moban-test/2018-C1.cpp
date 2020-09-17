// C4-2018级算法第一次上机
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
typedef pair<long, long> pll;

const int inf = 0x3f3f3f3f;

// 使用冒泡排序将一个序列由小到大排序，请问这个过程中，序列中的元素一共交换了多少次？
// 归并排序裸题
void a() {
  int n; cin >> n;
  vi v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  long ans = 0;
  function<void(int lo, int hi)> MergeSort;
  MergeSort = [&](int lo, int hi)->void {
    if (hi - lo < 2) return;
    int mi = lo + hi >> 1;
    MergeSort(lo, mi), MergeSort(mi, hi);

    vi left(v.begin()+lo, v.begin()+mi), right(v.begin()+mi, v.begin()+hi);
    for (int i = 0, j = 0; i < left.size() || j < right.size(); ) {
      if (i < left.size() && (j == right.size() || left[i] <= right[j]))  {
        v[lo++] = left[i++];
      }
      if (j < right.size() && (i == left.size() || left[i] > right[j])) {
        v[lo++] = right[j++];
        ans += left.size() - i;
      }
    }
  };
  MergeSort(0, n);
  cout << ans << '\n';
}

// 优先队列模拟
void b() {
  int n, k;
  while (cin >> n >> k) {
    vi v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    priority_queue<int> pq(v.begin(), v.end());
    while (k--) {
      int t = pq.top(); pq.pop();
      pq.push(t >> 1);
    }
    long ans = 0;
    while (!pq.empty()) {
      int t = pq.top(); pq.pop();
      ans += t;
    }
    cout << ans << '\n';
  }
}

// 递归处理先序遍历
void c() {
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    if (v[0] != "pair") {
      cout << "Error occurred\n";
      continue;
    }
    string ans;
    int i = 0;
    function<bool()> ok;
    ok = [&]()->bool {
      if (i == n) return false;
      string s = v[i];
      i++;
      if (s == "pair") {
        ans += s + "<";
        if (!ok()) return false;
        ans += ",";
        if (!ok()) return false;
        ans += ">";
      }
      else ans += s;
      return true;
    };
    if (ok() && i == n) cout << ans << '\n';
    else cout << "Error occurred\n";
  }
}


// 希尔伯特曲线，模拟递归
void d() {

}
// 差分处理，将原序列上的区间操作转换为单点操作
// B[i]=A[i]−A[i−1]
// A[l,r] 每个数加上一个d，可以转换操作为B[l]+d,B[r+1]−d
// 运用离散化思想
void e() {
  int n, k; 
  while (cin >> n >> k) {
    vector<pii> vp(2*k);
    int cnt = 0;
    for (int i = 0; i < k; i++) {
      int l, r; cin >> l >> r;
      vp[cnt++] = pii(l, 1);
      vp[cnt++] = pii(r+1, 0);
    }
    sort(vp.begin(), vp.end());
    long sum = 0, ans = 0;
    for (int i = 0; i < cnt; i++) {
      if (vp[i].second) sum--;
      else sum++;
      // 若为奇数，说明开关次数为奇数，亮着
      if (sum % 2) ans += vp[i+1].first - vp[i].first;
    }
    cout << ans << '\n';
  }
}
// 过河问题
// dp[0][i] 表示跨一步、二步到达i的次数
// dp[1][i] 表示跨三步到i的次数
void f() {
  vector<vector<long>> dp(2, vector<long>(55));
  dp[0][0] = dp[0][1] = 1; dp[0][2] = 2;
  for (int i = 3; i < 55; i++) {
    dp[0][i] = dp[0][i-1] + dp[0][i-2] + dp[1][i-1] + dp[1][i-2];
    dp[1][i] = dp[0][i-3];
  }
  int n;
  while (cin >> n) {
    cout << dp[0][n] + dp[1][n] << '\n';
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
  // e();
  f();
  return 0;
}