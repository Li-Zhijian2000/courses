#include <iostream>
using namespace std;
const int maxn = 255;
const int mod = 1000007;
long dp[maxn];

int main() {
  ios::sync_with_stdio(0);
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 3;
  for (int i = 3; i < maxn; i++) {
    dp[i] = (dp[i-1] + 2 * dp[i-2]) % mod;
  }
    
  int n;
  while (cin >> n) {
    n /= 3;
    cout << dp[n] % mod<< '\n';
  }
  return 0;
}