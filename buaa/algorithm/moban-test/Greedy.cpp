#include <iostream>
using namespace std;

#include <vector>
#include <algorithm>
// Magry的朋友很多 - Wonderland的邀请篇 https://accoding.cn/contest-ng/index.html#/87/problems
// 活动区间选择
void RangeArrange() {
  typedef pair<int, int> pii;

  int n; 
  while (cin >> n) {
    // first - 结束时间 second - 开始时间
    // [start, end)
    vector<pii> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].second >> v[i].first;
    sort(v.begin(), v.begin() + n);

    int cur = 0, ans = 0;
    for (int i = 0; i < n; i++) {
      // 因为左闭右开，所以当前大于开始时间的活动不能取
      if (cur > v[i].second) continue;
      ans++;
      cur = v[i].first;
    }
    cout << ans << '\n';
  }
}

// 可得长生否 https://accoding.cn/contest-ng/index.html#/87/problems
// 动态规划求边长为1的最长路径
// 刷表法：按拓扑序依次更新
// 思路同最短路
void LongestPath() {
  struct Node {
    int value, x, y;
  };

  int m, n;
  while (cin >> m >> n) {
    vector<Node> vn;
    // 刷表法：将初始路径初始化为1
    vector<vector<int>> d(m, vector<int>(n, 1)), map(m, vector<int>(n));
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++) {
        int value; cin >> value;
        map[i][j] = value;
        vn.push_back((Node){value, i, j});
      }
    
    // value序即为拓扑序，更普遍方法是建图dfs
    sort(vn.begin(), vn.end(), [](Node& a, Node& b) { return a.value < b.value; });
    for (int i = 0; i < vn.size(); i++) {
      int value = vn[i].value, x = vn[i].x, y = vn[i].y;
      int t = d[x][y] + 1;
  
      if (x > 0 && map[x-1][y] > value) d[x-1][y] = max(d[x-1][y], t);
      if (x < m - 1 && map[x+1][y] > value) d[x+1][y] = max(d[x+1][y], t);
      if (y > 0 && map[x][y-1] > value) d[x][y-1] = max(d[x][y-1], t);
      if (y < n - 1 && map[x][y+1] > value) d[x][y+1] = max(d[x][y+1], t);
    }
    int ans = 0;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        ans = max(ans, d[i][j]);
    cout << ans << '\n';
  }
}


// 简单的贪心 https://accoding.cn/problem/572/index
int SimpleGreedy() {
  int n;
  while (cin >> n) {
    vector<int> vi(n);
    for (int i = 0; i < n; i++) cin >> vi[i];
    sort(vi.begin(), vi.begin() + n);

    long ans = 0, i;
    // 两种过河策略：
    // 1、让最小的两个过河，让次小的回来，再让最大的两个过河，最小的回来。运送最大两个的时间 = v[i] + v[1] * 2 + v[0]
    // 2、让最小的依次陪最大的两个过河，运送最大两个的时间 = v[i] + v[i-1] + v[0] * 2
    for (i = n-1; i > 2; i -= 2)
      ans += (vi[i-1] > vi[1] * 2 - vi[0]) ? vi[i] + vi[1] * 2 + vi[0] : vi[i] + vi[i-1] + vi[0] * 2;
    if (i == 0) ans += vi[0];
    if (i == 1) ans += vi[1];
    if (i == 2) ans += vi[0] + vi[1] + vi[2]; 
    
    cout << ans << '\n';
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  ios::sync_with_stdio(0);
  // RangeArrange();
  // LongestPath();
  double a;
  cin >> a;
  cout << a << '\n';
  // SimpleGreedy();
  return 0;
}