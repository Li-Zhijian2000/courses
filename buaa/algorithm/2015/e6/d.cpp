#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-8;

int dcmp(double x) {
  if (fabs(x) < eps) return 0;
  else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector n1, Vector n2) { return Vector(n1.x+n2.x, n1.y+n2.y); }
Vector operator - (Point n1, Point n2) { return Vector(n1.x-n2.x, n1.y-n2.y); }

double Dot(Vector n1, Vector n2) { return n1.x*n2.x + n1.y*n2.y; }
double Cross(Vector n1, Vector n2) { return n1.x*n2.y - n1.y*n2.x; }
double Length(Vector n) { return sqrt(Dot(n, n)); }
double Angle(Vector n1, Vector n2) { return acos(Dot(n1, n2) / Length(n1) / Length(n2)); }

bool operator < (Point p1, Point p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool operator == (Point p1, Point p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

// 点集凸包
// 如果希望在凸包的边上有输入点，把两个 <= 改成 <
// 如果不介意点集被修改，可以改成传递引用
vector<Point> ConvexHull(vector<Point> p) {
  // 预处理，删除重复点
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());

  int n = p.size();
  int m = 0;
  vector<Point> ch(n+1);
  for(int i = 0; i < n; i++) {
    while(m > 1 && dcmp(Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for(int i = n-2; i >= 0; i--) {
    while(m > k && dcmp(Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
    ch[m++] = p[i];
  }
  if(n > 1) m--;
  ch.resize(m);
  return ch;
}

#include <iostream>

int main() {
  // freopen("d.txt", "r", stdin);
  int n, r;
  while (~scanf("%d%d", &n, &r)) {
    vector<Point> p, ch;
    for (int i = 0; i < n; i++) {
      double x, y; scanf("%lf%lf", &x, &y);
      p.push_back(Point(x, y));
    }
    ch = ConvexHull(p);
    double ans = 2 * pi * r;
    for (int i = 0; i < ch.size(); i++) {
      int ni = (i + 1) % ch.size();
      ans += Length(ch[i] - ch[ni]);
    }
    printf("%.0lf\n", ans + eps);
  }
  return 0;
}