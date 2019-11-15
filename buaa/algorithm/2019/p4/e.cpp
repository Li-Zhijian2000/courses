// #define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;

int main() {
#ifdef local
  freopen("e.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int n;
  vector<pii> vp;
  cin >> n; 
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    vp.push_back(pii(-y, x));
  }
  sort(vp.begin(), vp.end());
  long ans = 0, t = 0;
  for (int i = 0; i < n; i++) {
    ans += (-vp[i].first) * t;
    t += vp[i].second;
  }
  cout << ans << '\n';
  return 0;
}
