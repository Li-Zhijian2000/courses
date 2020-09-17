#include <algorithm>
#include <cstring>
using namespace std;

// 物品最大数、背包最大容量
const int maxn = 1005; 
const int maxm = 1005;

// 保证 sigma cost <= maxm ，求 max weight
// cnt 用于多重背包
long cost[maxn], weight[maxn], cnt[maxn];
long dp[maxm];

struct Pack {
  long V;
  void init(long v){
    this->V = v;
    memset(dp, 0, (v+1) * sizeof(dp[0]));
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

Pack p;

bool ok(char c) {
  char t[11] = "AEIOUaeiou";
  for (int i = 0; i < 10; i++)
    if (c == t[i]) return true;
  
  return false;
}
int main() {
  // ios::sync_with_stdio(0);
  // freopen("b.txt", "r", stdin);
  int n, v;
  while (cin >> n >> v) {
    p.init(v);
    for (int i = 0; i < n; i++) {
      char x[1005]; scanf("%s", x);
      int n = strlen(x);
      cost[i] = n;
      weight[i] = 0;
      for (int j = 0; j < n; j++) 
        if (ok(x[j])) weight[i]++;
    }
    
    for (int i = 0; i < n; i++) {
      long c = cost[i], w = weight[i];
      p.Complete(c, w);
    }    
    cout << dp[v] << '\n';
  }
  return 0;
}