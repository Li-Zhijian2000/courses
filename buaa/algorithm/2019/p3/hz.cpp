#include <iostream>
#include <algorithm>
#define maxn 505
using namespace std;

int main()
{
    freopen("optional_bst.txt", "r", stdin);
	ios::sync_with_stdio(0);
	int n,p[maxn],q[maxn],i,j,k,l,w[maxn][maxn];
	long temp,dp[maxn][maxn];
	cin >> n;
	for(i = 1; i<=n; i++)
		cin >> p[i];
	for(i = 0; i <= n; i++)
		cin >> q[i];
	for(i = 1; i <= n; i++)
	{
		w[i][i-1] = q[i-1];
		dp[i][i-1] = q[i-1];
		dp[i][i] = 0x3f3f3f3f;
		for(j = i; j <= n; j++)
		{
			w[i][j] = w[i][j-1] + q[j]+p[j];
			dp[i][j] = 0x3f3f3f3f;
		}
	}
	for(l = 1; l <= n; l++)
		for(i = 1; i<= n-l+1; i++)
		{
			j = i+l-1;
			for(k = i ; k <= j; k++)
			{
				temp = dp[i][k-1]+dp[k+1][j]+w[i][j];
				dp[i][j] = min(temp,dp[i][j]);
			}
		}
	cout << dp[1][n] << endl;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
        cout << ((i > j) ? 0 : dp[i][j]) << " ";
      cout << '\n';
    }
	return 0;
}
