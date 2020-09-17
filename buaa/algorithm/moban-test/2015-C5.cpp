// 2015级算法第五次上机
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

// 二进制计数器位翻转的运行代价以及摊还代价
void c() {
  int n, x;
  vi a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vi bits(32);
  int sum = x;
  for (int i = 0; i < 32; i++, x /= 2) bits[i] = x % 2;
  auto increase = [&]() {
    // 复位次数
    int k = 0;
    for (int i = 0; i < 32; i++) {
      if (bits[i])
    }
  }
  for (int i = 0; i < n; i++) {
    cout << "Case " << i+1 << ":\n";
    
  }
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  return 0;
}