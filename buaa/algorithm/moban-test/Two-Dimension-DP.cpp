#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

// C4-最小乘法 https://accoding.cn/contest-ng/index.html#/428/problems
namespace a{
const int maxn = 1005;
long dp[maxn][maxn];
char s[maxn];
// s[i, j)
long convert(int i, int j) {
  char t[maxn];
  strncpy(t, s + i, j - i);
  t[j-i] = 0;
  return atol(t);
}
int main2() {
  int n;
  while (cin >> n) {
    memset(dp, 0, sizeof(dp));
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 1; i <= len; i++) {
      dp[i][0] = convert(0, i);
    }
    for (int i = 2; i <= len; i++)
      for (int j = 1; j <= n; j++)
        for (int k = j; k < i; k++)
          dp[i][j] = max(dp[i][j], dp[k][j-1] * convert(k, i));
    cout << dp[len][n] << '\n';
  }  
  return 0;
}
}
// 身可死，武士之名不可弃 https://accoding.cn/contest-ng/index.html#/98/problems
// 带方向的TSP，多路dp
#include <cmath>
#include <vector>
#include <algorithm>

namespace b{
struct Point {
  double x, y;
  Point(double x=0, double y=0): x(x),y(y) { }
};
typedef Point Vector;

Vector operator +(Vector a, Vector b) { return Vector(a.x+b.x, a.y+b.y); }
Vector operator -(Point a, Point b) { return Vector(a.x-b.x, a.y-b.y); }
bool operator <(Point a, Point b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
bool operator ==(Point a, Point b) { return a.x == b.x && a.y == b.y; }

double Dot(Vector a, Vector b) { return a.x*b.x + a.y*b.y; }
double Cross(Vector a, Vector b) { return a.x*b.y - a.y*b.x; }
double Length(Vector n) { return sqrt(Dot(n, n)); }
double LengthSq(Vector n) { return Dot(n, n); }

const double inf = 1e80;
double dp[1005][1005];
int main() {
  freopen("input.txt", "r", stdin);
  ios::sync_with_stdio(0);
  int n; 
  while (cin >> n) {
    vector<Point> p(n);
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;

    sort(p.begin(), p.end());

    for (int i = 0; i < n; i++) 
      for (int j = 0; j < n; j++)
        dp[i][j] = inf;
    dp[0][0] = 0;
    dp[1][0] = Length(p[0] - p[1]);
    for (int i = 1; i < n; i++)
      for (int j = 0; j <= i; j++) {
        if (i == j + 1) 
          for (int k = 0; k < j; k++)
            dp[i][j] = min(dp[i][j], dp[j][k] + Length(p[i] - p[k]));
        else dp[i][j] = min(dp[i][j], dp[i-1][j] + Length(p[i-1] - p[i]));
      }
    double ans = inf;
    for (int i = 0; i < n; i++) ans = min(ans, dp[n-1][i] + Length(p[n-1] - p[i]));
    printf("%.2lf\n", ans);
  }
  return 0;
}
}
// 最长公共子序列 打印解