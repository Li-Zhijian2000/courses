// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<long, long> pll;

int main() {
#ifdef local
  freopen("e.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int n, k;
  while (cin >> n >> k) {
    priority_queue<pll> pq;
    vector<pll> v;

    for (int i = 1; i <= n; i++) {
      int p;
      cin >> p;
      v.push_back(pll(p, i));
    }
    int i;
    for (i = 0; i < min(n, k + 1); i++) {
      pq.push(v[i]);
    }
    int j = 1;
    long res = 0;
    while (!pq.empty() || i < n) {
      pll t = pq.top();
      pq.pop();
      res += t.first * (j + k - t.second);
      j++;
      if (i < n) pq.push(v[i++]);
    }
    cout << res << '\n';
  }
  return 0;
}
