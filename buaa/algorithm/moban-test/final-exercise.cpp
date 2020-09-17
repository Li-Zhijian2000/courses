// 2018级算法期末综合练习赛 https://accoding.cn/contest-ng/index.html#/445
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

// 只有全0、全1才失败
// 三个操作分别为置0、置1、交换01，故最优解为优先交换01
void a() {
  int t; cin >> t;
  while (t--) {
    string a, b; cin >> a >> b;
    int pre_and = 1, pre_or = 0;
    int n = a.size();
    for (int i = 0; i < n; i++) {
      pre_and &= a[i] - '0';
      pre_or |= a[i] - '0';
    }
    if (pre_or == 0 || pre_and == 1) cout << "-1\n";
    else {
      int ans1 = 0, ans2 = 0;
      for (int i = 0; i < n; i++)
        if (a[i] == '0' && b[i] == '1') ans1++;
        else if (a[i] == '1' && b[i] == '0') ans2++;
      cout << min(ans1, ans2) + abs(ans1 - ans2) << '\n';
    }
  }
}
void b() {
  int n; cin >> n;
  while (n--) {
    string s; cin >> s; 
    function<bool(int lo, int hi)> IsW;
    IsW = [&](int lo, int hi)->bool {
      if (lo == hi) return 1;
      if (s[lo] != '(') return 0;
      
      int x = 0, flag = 0, loc = 0;
      for (int i = lo; i < hi; i++) {
        if (s[i] == '(') x++;
        else if (s[i] == ')') x--;
        if (x < 0) return 0;
        if (!x) {
          flag++;
          if (flag == 1) loc = i;
        }
      }
      if (x) return 0;
      if (flag == 1) return IsW(lo+1, hi-1);
      if (flag == 2) return IsW(lo+1, loc) && IsW(loc+2, hi-1);
      return 0;
    };
    cout << (!(s.size() % 2) && IsW(0, s.size()) ? "Yes\n" : "No\n");
  }
}
// MP变种
// 返回 a 是否 胜 b
// n^2暴力、可用FFT，nlogn
void c() {
  auto Match = [](char a, char b) {
  return a == 'R' && b == 'S' || 
         a == 'S' && b == 'P' || 
         a == 'P' && b == 'R';
  };

  int n, m; cin >> n >> m;
  string a, b; cin >> a >> b;

  int ans = 0, x = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i + j >= n) break;
      if (Match(b[j], a[i + j])) x++;
    }
    ans = max(ans, x);
    x = 0;
  }
  cout << ans << '\n';
}
// 前缀和
void d() {
  const int mod = 10007;
  int n, q; 
  while (cin >> n >> q) {
    vi a(n+1), sum(n+1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      sum[i] += sum[i-1] % mod + a[i] % mod;
      sum[i] %= mod;
    }
    for (int i = 0; i < q; i++) {
      int l, r; cin >> l >> r;
      cout << (sum[r] - sum[l-1] + mod) % mod << '\n';
    }
  }
}
// 奶牛问题板子，类似题只需改动出生、生育、死亡年份
void e() {
  // 出生2年后成年，成年期10年，8年后死亡，最多50年
  const int a = 2, b = 10, c = 8;
  // num[i]表示当前年龄为i的数目
  vi num(a+b+c);

  int t; cin >> t;
  while (t--) {
    int q; cin >> q;
    fill(num.begin(), num.end(), 0);
    num[0] = 1;
    q--;
    while (q--) {
      // 长大一岁
      for (int i = a+b+c-1; i >= 1; i--) num[i] = num[i-1];
      num[0] = 0;
      // 新出生
      for (int i = a; i < a + b; i++) num[0] += num[i];
    }
    int ans = 0;
    for (int i = 0; i < a+b+c; i++) ans += num[i];
    cout << ans * 2 << '\n';
  }
}
// 注意到题目中“把游戏光盘放回去的时候总要保证每个展示架的游戏仍然按照字典序从小到大排列”，故为汉诺塔
// 最优解为将前n-2个放到2号位，第n-1个放到3号位，第n个放到1号位
// 若只需保证结束时从小到大，最优解为n-2 + 2 + n-3 = 2n-3
void f() {
  int n;
  while (cin >> n) {
    vi play(n+1);
    auto move = [](int from, int to, bool play) {
      printf("get game from board %d\n", from + 1);
      if (!play) puts("playing");
      printf("put game to board %d\n", to + 1); 
    };
    function<void(int from, int to, int n)> hannoi;
    hannoi = [&](int from, int to, int n)->void {
      if (n == 1) {
        move(from, to, play[1]);
        play[1] = 1;
        return;
      }
      int nto = 3-from-to;
      hannoi(from, nto, n-1);
      move(from, to, play[n]);
      play[n] = 1;
      hannoi(nto, to, n-1);
    };
    if (n < 3) {
      if (n == 2) move(0, 1, 0);
      move(0, 2, 0);
    }
    else {
      hannoi(0, 1, n-2);
      move(0, 2, 0);
      move(0, 0, 0);
    }
    puts("leave");
  }
}
void g() {
  int n; cin >> n;
  vi v(n);
  function<void(int lo, int hi, int level)> QuickSort;
  QuickSort = [&](int lo, int hi, int level)->void {
    int i = lo, j = hi - 1, mid = v[lo + hi >> 1];
    while (i <= j) {
      while (v[i] < mid) i++;
      while (v[j] > mid) j--;
      if (i <= j) {
        swap(v[i], v[j]);
        i++, j--;
      }
    }
    if (level == 2) {
      for (; i < hi; i++) cout << v[i] << (i != hi-1 ? ' ' : '\n');
      return;
    }
    QuickSort(0, i, level + 1);
  };
  for (int i = 0; i < n; i++) cin >> v[i];
  QuickSort(0, n, 1);
}
// 输入一个序列，查询每个数出现次数
void h() {
  int n, t;
  while (cin >> n >> t) {
    vi v(n);
    vector<pii> vp(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.begin() + n);
    // 计数
    for (int i = 0, sum = 1; i <= n; i++) {
      if (i == n || v[i] != v[i-1]) {
        vp.push_back(pii(v[i-1], sum));
        sum = 1;
      }
      else sum++;
    }
    while (t--) {
      int x; cin >> x;
      auto p = lower_bound(vp.begin(), vp.end(), pii(x, 0));
      if (p->first == x) cout << p->second << ' ';
      else cout << "0 ";
    }
    cout << '\n';
  }
}
// 返回一个数是第几大
void i() {
  int n;
  while (cin >> n) {
    vector<long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.begin() + n);
    v.erase(unique(v.begin(), v.end()), v.end());
    
    long x; cin >> x;
    auto p = lower_bound(v.begin(), v.end(), x);
    cout << v.end() - p << '\n';
  }
}
// 霍夫曼树
void j() {
  int n;
  while (cin >> n) {
    priority_queue<int, vi, greater<int>> pq;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int x; cin >> x;
      pq.push(x);
    }
    while (pq.size() > 1) {
      int a = pq.top(); pq.pop();
      int b = pq.top(); pq.pop();
      ans += a + b;
      pq.push(a + b);
    }
    cout << ans << '\n';
  }
}
// nth_element: [begin, k) < [k, end)，因此v[k] 是第k小的数
void k() {
  const int maxn = 3000001;
  vector<long> v(maxn);
  int a, b, c, a1, k;
  while (cin >> a >> b >> c >> a1 >> k) {
    v[0] = a1;
    for (int i = 1; i < maxn; i++)
      v[i] = ((1LL * v[i-1] * a ^ b) + c) % 1000000007;
    nth_element(v.begin(), v.begin() + k-1, v.end());
    cout << v[k-1] << '\n';
  }
}
// 三节点霍夫曼
void l() {
  int n;
  while (cin >> n) {
    priority_queue<int, vi, greater<int>> pq;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int x; cin >> x;
      pq.push(x);
    }
    while (pq.size() > 2) {
      int a = pq.top(); pq.pop();
      int b = pq.top(); pq.pop();
      int c = pq.top(); pq.pop();
      ans += a + b + c;
      pq.push(a + b + c);
    }
    cout << ans << '\n';
  }
}
// 物品最大数、背包最大容量
const int maxn = 505; 
const int maxm = 1e5 + 5;
// 保证 sigma cost <= maxm ，求 max weight
// cnt 用于多重背包
struct Material {
  long cost, wegiht, cnt;
};
struct Pack {
  long V;
  Material materials[maxn];
  long dp[maxm];

  void init(long v){
    this->V = v;
    fill(dp, dp + v + 1, 0);
  }
  void ZeroOne(long cost, long weight) {
    for (int j = V; j >= cost; j--)
      dp[j] = max(dp[j], dp[j - cost] + weight);
  }
  void Complete(long cost, long weight) {
    for (int j = cost; j <= V; j++)
      dp[j] = max(dp[j], dp[j - cost] + weight);
  }
  void Multiple(long cost, long weight, long cnt) {
    if (cost * cnt >= V)
      Complete(cost, weight);
    else {
      long k = 1;
      while (k < cnt) {
        ZeroOne(k * cost, k * weight);
        cnt -= k;
        k <<= 1;
      }
      ZeroOne(cnt * cost, cnt * weight);
    }
  }
};
Pack pack;
// 组合背包板子
void m() {
  int n, v;
  while (cin >> n >> v) {
    pack.init(v);
    for (int i = 0; i < n; i++) {
      Material& m = pack.materials[i];
      cin >> m.cnt >> m.cost >> m.wegiht;
    }
    for (int i = 0; i < n; i++) {
      Material& m = pack.materials[i];
      pack.Multiple(m.cost, m.wegiht, m.cnt);
    }
    cout << pack.dp[v] << '\n';
  }
}
// RMQ板子
void n() {
  // [0, n)
  auto RMQInit = [&](vi& v, vvi& d) {
    int n = v.size();
    for (int i = 0; i < n; i++) d[i][0] = v[i];
    for (int j = 1; (1<<j) <= n; j++)
      for (int i = 0; i + (1<<j) - 1 < n; i++)
        d[i][j] = max(d[i][j-1], d[i + (1<<(j-1))][j-1]);
  };
  // [l, r], l,r in [0, n)
  auto RMQ = [&](int l, int r, vvi& d) {
    int k = 0;
    while ((1<<(k+1)) <= r-l+1) k++;
    return max(d[l][k], d[r-(1<<k)+1][k]);
  };

  int n; cin >> n;
  vi v(n);
  vvi d(n, vi(log(n) + 10));
  for (int i = 0; i < n; i++) cin >> v[i];
  RMQInit(v, d);
  
  int m; cin >> m;
  while (m--) {
    int l, r; cin >> l >> r;
    l--, r--;
    cout << RMQ(l, r, d) << '\n';
  }
}
// 贪心
void o() {
  typedef pair<long, long> pll;
  int n; cin >> n;
  vector<pll> vp(n);
  for (int i = 0; i < n; i++) cin >> vp[i].first >> vp[i].second;
  sort(vp.begin(), vp.end());
  // 将同位置、费用高的清除
  for (int i = 1; i < vp.size(); i++) 
    if (vp[i].first == vp[i-1].first) vp[i] = vp[i-1];
  vp.erase(unique(vp.begin(), vp.end()), vp.end());
  
  n = vp.size();
  long ans = 0, loc = vp[0].first, cost = vp[0].second;
  for (int i = 1; i < n; i++) {
    // 尽可能用费用低的，注意边界
    if (i != n-1 && cost <= vp[i].second) continue;
    ans += cost * (vp[i].first - loc);
    loc = vp[i].first;
    cost = vp[i].second;
  }
  cout << ans << '\n';
}
// 树形dp
// 树的最长链等于子节点的最长链+次长链
// dp[i] 表示i结点的高度，叶节点为0
void p() {
  int n; cin >> n;
  // 二叉树
  vvi nodes(n+1, vi(2));
  vi dp(n+1);
  function<void(int r)> GetHeight;
  GetHeight = [&](int r)->void {
    if (!r) return;
    
    int lc = nodes[r][0], rc = nodes[r][1];
    // 树形dp要先递归更新子节点高度
    GetHeight(lc);
    GetHeight(rc);
    dp[r] = max(dp[lc], dp[rc]) + 1;
  };
  for (int i = 1; i <= n; i++) cin >> nodes[i][0] >> nodes[i][1];
  // 保证根为1
  GetHeight(1);
  int ans = 0;
  for (int i = 1; i <= n; i++) ans = max(ans, dp[nodes[i][0]] + dp[nodes[i][1]]);
  cout << ans << '\n';
}
// 树形dp
// 相邻辈分无法同时参加聚会，每个人有一个权值、求参加的最大权值
// dp[0][i]表示不参加聚会，则其子节点可参加可不参加，sum(max(dp[0][v], dp[1][v]))
// dp[1][i]表示参加聚会，则其子节点一定不能参加，sum(dp[0][v])
void q() {
  int n; cin >> n;
  vvi nodes(n+1), dp(2, vi(n+1));
  vi weight(n+1), pa(n+1);
  function<void(int r)> Update;
  Update = [&] (int r)->void {
    if (nodes[r].empty()) {
      dp[0][r] = 0;
      dp[1][r] = weight[r];
      return;
    }
    for (int i = 0; i < nodes[r].size(); i++) {
      int j = nodes[r][i];
      Update(j);
    }
    dp[1][r] = weight[r];
    for (int i = 0; i < nodes[r].size(); i++) {
      int j = nodes[r][i];
      dp[0][r] += max(dp[0][j], dp[1][j]);
      dp[1][r] += dp[0][j];
    }
  };
  for (int i = 1; i <= n; i++) cin >> weight[i];
  int c, p;
  // p是c父母，0 0输入结束
  while (cin >> c >> p && (c || p)) {
    nodes[p].push_back(c);
    pa[c] = p;
  }
  int r = 1;
  // 找根结点
  while (pa[r]) r = pa[r];
  Update(r);
  cout << max(dp[0][r], dp[1][r]) << '\n';
}
// 与左右两人相比，若思念值高，则获得的花瓣要多
// dp[i] 表示获得花瓣，刷表
void r() {
  int n; 
  while (cin >> n) {
    vi a(n), dp(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++)
      if (a[i] < a[i+1]) dp[i+1] = max(dp[i+1], dp[i]+1);
    for (int i = n-1; i >= 0; i--)
      if (a[i] < a[i-1]) dp[i-1] = max(dp[i-1], dp[i]+1);
    long sum = 0;
    for (int i = 0; i < n; i++) 
      sum += dp[i];
    cout << sum << '\n';
  }
}
// 思路同q题
// 环形取数问题，相邻不取，n为偶数时为最大点权独立集
void t() {
  int n;
  while (cin >> n) {
    vvi dp(2, vi(n));
    vi v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    // 边界情况
    if (n == 1) {
      cout << v[0] << '\n';
      continue;
    }
    // 不取第一个
    dp[1][0] = dp[0][0] = 0;
    for (int i = 1; i < n; i++) {
      dp[1][i] = dp[0][i-1] + v[i];
      dp[0][i] = max(dp[0][i-1], dp[1][i-1]);
    }
    int ans1 = max(dp[0][n-1], dp[1][n-1]);
    // 取第一个，那么不能取最后一个
    dp[0][n-1] = dp[1][n-1] = 0;
    for (int i = n-2; i >= 0; i--) {
      dp[1][i] = dp[0][i+1] + v[i];
      dp[0][i] = max(dp[0][i+1], dp[1][i+1]);
    }
    int ans2 = max(dp[0][0], dp[1][0]);
    cout << max(ans1, ans2) << '\n';
  }
}
//二分
void u() {
  int n, k;
  while (cin >> n >> k) {
    k--;
    vector<long> vi(n);
    for (int i = 0; i < n; i++) cin >> vi[i];

    if (!k) {
      cout << *max_element(vi.begin(), vi.end()) << '\n';
      continue;
    }
    sort(vi.begin(), vi.end());

    auto ok = [&vi, &n, &k](long x) {
      int i = upper_bound(vi.begin(), vi.end(), x) - vi.begin();
      long t = 0;
      for (; i < n; i++) {
        // 向上取整
        t += (vi[i] - x + k - 1) / k;
        if (t > x) return 0;
      }
      return 1;
    };
    long lo = 0, hi = vi[n-1]+1;
    while (lo < hi) {
      long mi = lo + hi >> 1;
      // 循环不变量：保证[hi, n) 满足ok，[0, lo)不满足
      ok(mi) ? hi = mi : lo = mi + 1;
    }
    cout << lo << '\n';
  }
}
// LCIS 最长上升公共子序列
void w() {
  int n, m;
  const int maxn = 1e4+2;
  vi a(maxn), b(maxn);
  vector<vector<short>> dp(maxn, vector<short>(maxn));
  while (cin >> n >> m) {
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    fill(dp[0].begin(), dp[0].end(), 0);
    for (int i = 1; i <= n; i++) {
      short val = 0;
      for (int j = 1; j <= m; j++) {
        if (a[i] == b[j]) dp[i][j] = val + 1;
        else dp[i][j] = dp[i-1][j];
        if (b[j] < a[i]) val = max(val, dp[i-1][j]);
      }
    }

    short ans = 0;
    for (int i = 1; i <= m; i++) ans = max(ans, dp[n][i]);
    cout << ans << '\n';
  }
}
// 三进制
void x() {
  int n;
  while (cin >> n) {
    vi pow {1, 3, 9, 27, 81, 243}, a(6), b(6);
    for (int i = 5; i >= 0; i--) {
      a[i] = n / pow[i];
      n %= pow[i];
    }
    for (int i = 0; i <= 5; i++) {
      if (a[i] == 2) {
        b[i] = 1;
        a[i] = 0;
        a[i+1]++;
      }
      if (a[i] == 3) {
        a[i] = 0;
        a[i+1]++;
      }
    }
    int i = 5;
    while (!a[i] && !b[i]) i--;
    cout << pow[i--];
    for (; i >= 0; i--)
      if (a[i]) cout << '+' << pow[i];
      else if (b[i]) cout << '-' << pow[i];
    cout << '\n';
  }
}
// 若已经能取到[1, m]，则再加上m+1的砝码，就能取到[1, 2m+1]
void y() {
  int n, m;
  while (cin >> n >> m) {
    vector<long> vi(n);
    for (int i = 0; i < n; i++) cin >> vi[i];
    sort(vi.begin(), vi.begin() + n);
    long sum = 0;
    int i = 0, ans = 0;
    while (i < n) {
      if (sum >= m) break;
      if (vi[i] <= sum + 1) {
        sum += vi[i];
        i++;
      }
      else {
        sum += sum + 1;
        ans++;
      }
    }
    while (sum < m) {
      sum += sum + 1;
      ans++;
    }
    cout << ans << '\n';
  }
}
// LCS板子
void z() {
  string a, b;
  while (cin >> a >> b) {
    const int maxn = 105;
    vvi dp(maxn, vi(maxn));
    auto eq = [](char a, char b) {
      if (a == '#' || b == '#') return false;
      if (a == '?' || b == '?') return true;
      return a == b;
    };
    int n = a.size(), m = b.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (eq(a[i], b[j])) dp[i+1][j+1] = dp[i][j] + 1;
        else dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
      }
    }
    cout << dp[n][m] << '\n';
  }
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // a();
  // b();
  // c(); // 暴力
  // d();
  // e();
  // f();
  // g();
  // h();
  // i();
  // j();
  // k();
  // l();
  // m();
  // n();
  // o();
  // p();
  q();
  // r();
  // t();
  // u();
  // w();
  // x();
  // y();
  // z();
  return 0;
}