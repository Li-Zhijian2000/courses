// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 1006;
int row[maxn], col[maxn];
bool ans[maxn];

void solve(int a[], int len, int total) {
  priority_queue<pii> pq;
  memset(ans, 0, sizeof(ans));  
  for (int i = 1; i <= len; i++) {
    pq.push(pii(a[i], i));
  }
  for (int i = 0; i < total; i++) {
    pii t = pq.top();
    pq.pop();
    ans[t.second] = true;
  }
  for (int i = 1; i <= len; i++) {
    if (ans[i]) cout << i << " ";
  }
  cout << '\n';
}
int main() {
#ifdef local
  freopen("p1056.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);0
  int m, n, k, l, d;
  cin >> m >> n >> k >> l >> d;
  for (int i = 0; i < d; i++) {
      int x, y, p, q;
      cin >> x >> y >> p >> q;
      if (x == p) col[min(y, q)]++;
      else row[min(x, p)]++;
  }
  solve(row, m, k);
  solve(col, n, l);
  return 0;
}
