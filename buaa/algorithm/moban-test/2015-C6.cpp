// 2015级算法第六次上机
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

const int inf = 0x3f3f3f3f;

// 给定n种长度不大于1000的只包含大小写字母的字符串，以及大字符串的最大长度k，
// 求大魔法师拼接得到的大字符串中a, e, i, o, u 和 A, E, I, O, U 十种字母的最大个数。
// 预处理后可转换为完全背包
const int maxn = 1005, maxm = 1005;
struct Material {
  // sum cost <= v, max weight
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
void b() {
  int n, k; 
  while (cin >> n >> k) {
    pack.init(k);
    for (int i = 0; i < n; i++) {
      string s; cin >> s;
      Material& m = pack.materials[i];
      // cost 为字符串长度，weight为字符串中对应字母出现次数
      m.cost = s.size();
      m.wegiht = count_if(s.begin(), s.end(), [](char c) { 
        string t = "aeiouAEIOU";
        return t.find(c) != string::npos;
      });
    }
    for (int i = 0; i < n; i++) {
      Material& m = pack.materials[i];
      pack.Complete(m.cost, m.wegiht);
    }
    cout << pack.dp[k] << '\n';
  }
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  b();
  return 0;
}