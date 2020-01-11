#include <algorithm>
using namespace std;

// 物品最大数、背包最大容量
const int maxn = 505; 
const int maxm = 30005;
// 保证 sigma weight <= maxm ，求 max cost
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

#include <iostream>

// E2-组合背包 https://accoding.cn/contest-ng/index.html#/415/problems
Pack p;
int main() {
  ios::sync_with_stdio(0);
  int n, v;
  while (cin >> n >> v) {
    p.init(v);
    for (int i = 0; i < n; i++) {
      Material& m = p.materials[i];
      cin >> m.cost >> m.wegiht >> m.cnt;      
    }
    for (int i = 0; i < n; i++) {
      Material& m = p.materials[i];
      if (m.cnt == 1)
        p.ZeroOne(m.cost, m.wegiht);
      else if (m.cnt == 233)
          p.Complete(m.cost, m.wegiht);
      else p.Multiple(m.cost, m.wegiht, m.cnt);
    }    
    cout << p.dp[v] << '\n';
  }
  return 0;
}