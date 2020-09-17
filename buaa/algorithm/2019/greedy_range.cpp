#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 505;
pii ranges[maxn];

int main() {
#ifdef local
  freopen("acch.txt", "r", stdin);
#endif
  int n;
  ios::sync_with_stdio(0);
  while (cin >> n) {
    for (int i = 0; i < n; i++)
      cin >> ranges[i].second >> ranges[i].first;
    sort(ranges, ranges + n);
    int ans = 0, t = 0;
    for (int i = 0; i < n; i++) {
      if (t < ranges[i].second) {
        ans++;
        t = ranges[i].first;
      }
    }
    cout << ans << '\n';
  }  
  return 0;
}
