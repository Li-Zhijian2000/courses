#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);

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

#include <iostream>

const int maxn = 55;

Point p[maxn];
double r[maxn];

bool InCircle(Point o, double r, Point x) {
  return Length(x - o) < r + eps;
}
int main() {
  // freopen("a.txt", "r", stdin);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;

    for (int i = 0; i < n; i++) cin >> p[i].x;
    for (int i = 0; i < n; i++) cin >> p[i].y;
    for (int i = 0; i < n; i++) cin >> r[i];

    Point p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (InCircle(p[i], r[i], p1) ^ InCircle(p[i], r[i], p2)) ans++;
    }
    cout << ans << '\n';
  }
}