// #define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e5 + 5;

struct Good {
  int cost, weight;
}goods[maxn];

int main() {
#ifdef local
  freopen("f.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int n, t;
  while (cin >> n >> t) {
    for (int i = 0; i < n; i++) 
      cin >> goods[i].cost >> goods[i].weight;
    
    sort(goods, goods + n, [](const Good& a, const Good& b) {
      return (float)a.weight / a.cost > (float)b.weight / b.cost;
    });

    double ans = 0;
    for (int i = 0; i < n; i++) {
      int c = goods[i].cost, w = goods[i].weight;
      if (t >= c) {
        t -= c;
        ans += w;
      }
      else {
        ans += t * (float)w / c;
        break;
      }
    }
    printf("%.2lf\n", ans + 1e-5);
  }
  return 0;
}
