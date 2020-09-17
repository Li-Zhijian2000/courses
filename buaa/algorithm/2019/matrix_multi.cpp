#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 500;
const long inf = 0x3f3f3f3f;
long dp[maxn][maxn];
int pa[maxn][maxn];
long dim[maxn];

long solve(int x, int y) {
  if (x == y) return 0;

  long& res = dp[x][y];
  if (res != dp[0][0]) return res;
  
  long t = dim[x-1] * dim[y];
  for (int i = x; i < y; i++) {
    // res = min(res, solve(x, i) + solve(i+1, y) + t*dim[i]);
    long newres = solve(x, i) + solve(i+1, y) + t*dim[i];
    if (res >= newres) {
      res = newres;
      pa[x][y] = i;
    }
  }
  return res;
}
void print_ans(int x, int y) {
  if (x == y) {
    cout << "A" << x;
    return;
  }
  cout << "(";
  print_ans(x, pa[x][y]);
  print_ans(pa[x][y]+1, y);
  cout << ")";
}
int main() {
#ifdef local
  freopen("matrix.txt", "r", stdin);
#endif

  int n;
  while (cin >> n) {
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= n; i++)
      cin >> dim[i];

    cout << solve(1, n) << '\n';
    print_ans(1, n);
    cout << '\n';
  }
  return 0;
}
