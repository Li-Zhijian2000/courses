// #define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <numeric>
using namespace std;

int main() {
#ifdef local
  freopen("g.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n; 
    vector<int> vi;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      vi.push_back(x);
    }
    long ans = accumulate(vi.begin(), vi.end(), 0L);
    ans += (n - 2) * (long)*min_element(vi.begin(), vi.end());
    cout << ans << '\n';
  }
  return 0;
}
