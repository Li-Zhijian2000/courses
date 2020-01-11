#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 5;

int m, n; 
long loc[maxn];
bool ok(long x) {
  int t = 1, i = 0;
  while ((i = upper_bound(loc, loc + n, loc[i] + x) - loc) != n) {
    t++;
    if (t > m) return 0;
  }
  return 1;
}
int main() {
  ios::sync_with_stdio(0);  
  cin >> m >> n;
  for (int i = 0; i < n; i++) cin >> loc[i];
  sort(loc, loc + n);
  long lo = 0, hi = loc[n - 1] - loc[0] + 1;
  while (lo < hi) {
    long mi = lo + hi >> 1;
    ok(mi) ? hi = mi : lo = mi + 1;
  }
  printf("%.1f\n", (double)lo / 2);
}