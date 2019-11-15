// #define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstring>
using namespace std;

vector<int> woods;

long ok(long l) {
  long ans = 0;
  for (int i = 0; i < woods.size(); i++) {
    ans += woods[i] / l;
  }
  return ans;
}
long solve(int lo, int hi, int target) {
  while (lo < hi) {
    int mi = lo + (hi - lo >> 2);
    (ok(mi) < target) ? hi = mi : lo = mi + 1;
  }
  return lo-1;
}
int main() {
#ifdef local
  freopen("p2440.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    int w;
    cin >> w;
    woods.push_back(w);
  }
  if (*min_element(woods.begin(), woods.end()) * n < k) {
    cout << 0 << '\n';
    return 0;
  }
  long ans = solve(0, accumulate(woods.begin(), woods.end(), 0L) / n + 1, k);
  cout << ans << '\n';
  return 0;
}
