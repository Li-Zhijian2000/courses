#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

const double pi = acos(0.0) * 2.0;
const double eps = 1e-8;
int dcmp(double x) {
  if (fabs(x) < eps) return 0;
  else return x < 0 ? -1 : 1;
}

typedef struct Point {
  double x, y;
  Point(double x=0, double y=0): x(x),y(y) { }
} Vector;
Vector operator +(Vector a, Vector b) { return Vector(a.x+b.x, a.y+b.y); }
Vector operator -(Point a, Point b) { return Vector(a.x-b.x, a.y-b.y); }
bool operator < (Point a, Point b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
bool operator == (Point a, Point b) { return a.x == b.x && a.y == b.y; }

double Dot(Vector a, Vector b) { return a.x*b.x + a.y*b.y; }
double Cross(Vector a, Vector b) { return a.x*b.y - a.y*b.x; }
double Length(Vector n) { return sqrt(Dot(n, n)); }
double LengthSq(Vector n) { return Dot(n, n); }
double Angle(Vector a, Vector b) { return acos(Dot(a, b) / Length(a) / Length(b)); }

// 向量旋转
Vector Rotate(Vector a, double rad) { 
  double c = cos(rad), s = sin(rad);
  return Vector(a.x*c - a.y*s, a.x*s + a.y*c);
}
// 点p是否在(a1, a2)上
// 若不包含端点，即(0, 0) 不在(0, 0), (1, 1)上，'<=' => '<'
// 1：内部，-1：边界，0：外部
int OnSegment(Point p, Point a1, Point a2) {
  int t1 = dcmp(Cross(a1-p, a2-p));
  int t2 = dcmp(Dot(a1-p, a2-p));
  if (!t1 && t2 < 0) return 1;
  else if (!t1 && !t2) return -1;
  else return 0;
}

// 求(a1, a2) 和 (b1, b2) 所在直线的交点，若输入平行，返回nan/inf
Point Intersection(Point a1, Point a2, Point b1, Point b2) {
  double t = Cross(b2-b1, b1-a1) / Cross(b2-b1, a2-a1);
  Vector v1 = a2 - a1;
  return a1 + Point(v1.x * t, v1.y * t);
}

// 规范相交：两线段恰好有一个端点，且不在任何一条线段的端点
// 若相互平行，可调用IsParallelIntersection判断
bool IsSegmentIntersection(Point a1, Point a2, Point b1, Point b2) {
  // 快速排斥定理
  if (min(a1.x, a2.x) > max(b1.x, b2.x) || 
     min(a1.y, a2.y) > max(b1.y, b2.y) || 
     min(b1.x, b2.x) > max(a1.x, a2.x) || 
     min(b1.y, b2.y) > max(a1.y, a2.y) )
    return 0; 

  double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1),
         c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
         
  return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

// 判断线段平行时，是否重合
// 1：部分重合，0：在端点重合，-1：不重合
// Length(a1, a2) < Length(b1, b2)
int IsParallelIntersection(Point a1, Point a2, Point b1, Point b2) {
  if (Length(a1-a2) > Length(b1-b2)) return IsParallelIntersection(b1, b2, a1, a2);
  // 所在直线平行但不重合
  if (dcmp(Cross(a1-b1, b2-b1))) return -1;
  // 若a1, a2都在(b1, b2)外，不重合
  if (OnSegment(a1, b1, b2) == 0 && OnSegment(a2, b1, b2) == 0) return -1;
  // 若a1在端点上且a2在线段外
  if (OnSegment(a1, b1, b2) == -1 && OnSegment(a2, b1, b2) == 0 ||
      OnSegment(a2, b1, b2) == -1 && OnSegment(a1, b1, b2) == 0) return 0;
  return 1;
}

// 判断点是否在凸包内/边界上
// 1：内部，-1：边界，0：外部
int IsPointInPolygon(Point p, const vector<Point>& poly) {
    int wn = 0;
    int n = poly.size();
    for(int i = 0; i < n; ++i) {
        Point p1 = poly[i], p2 = poly[(i+1)%n];
        if(OnSegment(p, p1, p2) != 0) return -1; //在边界上：点在线段内（含端点）
        int k = dcmp(Cross(p2-p1, p-p1));
        int d1 = dcmp(p1.y - p.y);
        int d2 = dcmp(p2.y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) wn++;
        if(k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if(wn != 0) return 1;//内部
    return 0;//外部
}

// 判断两个凸包是否相离
bool IsConvexHullJoint(const vector<Point>& p1, const vector<Point>& p2) {
  int n1 = p1.size(), n2 = p2.size();
  for (int i = 0; i < n1; i++) 
    if (IsPointInPolygon(p1[i], p2) != 0) return false;
  for (int i = 0; i < n2; i++) 
    if (IsPointInPolygon(p2[i], p1) != 0) return false;
  for(int i = 0; i < n1; ++i)
    for(int j = 0; j < n2; ++j)
      if(IsSegmentIntersection(p1[i], p1[(i+1)%n1], p2[j], p2[(j+1)%n2])) return false;
  return true;
}

// 点集凸包
// 如果希望在凸包的边上有输入点，'<=' => '<'
vector<Point> ConvexHull(vector<Point> p) {
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());

  int n = p.size();
  int m = 0;
  vector<Point> ch(n+1);
  for(int i = 0; i < n; i++) {
    while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for(int i = n-2; i >= 0; i--) {
    while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  if(n > 1) m--;
  ch.resize(m);
  return ch;
}

// 多边形的面积
double PolygonArea(const vector<Point>& p) {
  int n = p.size();
  double area = 0;
  for(int i = 1; i < n-1; i++)
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return fabs(area/2);
}

// 多边形周长
double PolygonPerimeter(const vector<Point>& p) {
  int n = p.size();
  double sum = Length(p[n-1]-p[0]);
  for (int i = 0; i < n-1; i++)
    sum += Length(p[i]-p[i+1]);
  return sum;
}

// 返回点集最远点对距离的平方
// 若要返回距离，'LengthSq' => 'Length'
// 如果不介意点集被修改，可以改成传递引用
double FarestPair(vector<Point> p) {
  p = ConvexHull(p);
  int n = p.size();
  if(n == 1) return 0;
  if(n == 2) return LengthSq(p[0] - p[1]);
  p.push_back(p[0]); // 免得取模
  double ans = 0;
  for(int u = 0, v = 1; u < n; u++) {
    // 一条直线贴住边p[u]-p[u+1]
    while(1) {
      // 当Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])时停止旋转
      // 即Cross(p[u+1]-p[u], p[v+1]-p[u]) - Cross(p[u+1]-p[u], p[v]-p[u]) <= 0
      // 根据Cross(A,B) - Cross(A,C) = Cross(A,B-C)
      // 化简得Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
      double diff = Cross(p[u+1]-p[u], p[v+1]-p[v]);
      if(dcmp(diff) <= 0) {
        ans = max(ans, LengthSq(p[u] - p[v])); // u和v是对踵点
        if(dcmp(diff) == 0) ans = max(ans, LengthSq(p[u] - p[v+1])); // diff == 0时u和v+1也是对踵点
        break;
      }
      v = (v + 1) % n;
    }
  }
  return ans;
}

const double inf = 1e150;
// 返回点集最短点对距离的平方
// 若要返回距离，'LengthSq' => 'Length'
// p[lo, hi)，tp为临时使用的变量，注意长度初始化为n
double ClosestPair(const vector<Point>& p, int lo, int hi, vector<Point>& tp) {
  double d = inf;
  if(lo + 1 == hi) return d;
  if(lo + 2 == hi) return LengthSq(p[lo] - p[hi-1]);
  
  int mi = lo + hi >> 1;
  d = min(ClosestPair(p, lo, mi, tp), ClosestPair(p, mi, hi, tp));

  int k = 0;
  for(int i = lo;i < hi; i++) {
    if(fabs(p[mi].x - p[i].x) <= d) tp[k++] = p[i];
  }
  sort(tp.begin(), tp.begin() + k, [](Point a, Point b) { return a.y < b.y; });
  for(int i = 0; i < k; i++) {
    for(int j = i+1; j < k && tp[j].y - tp[i].y < d;j++) {
      d = min(d, LengthSq(tp[i] - tp[j]));
    }
  }
  return d;
}

// 点到直线距离 
double DistToLine(Point p, Point a, Point b) {
  Vector v1 = b - a, v2 = p - a;
  // 高 = 平行四边形面积 / 底
  return fabs(Cross(v1, v2) / Length(v1));
}
// 点p和圆(c, r)的切线
int GetTangents(Point p, Point c, double r, Vector* v) {
  Vector u = c - p;
  double dist = Length(u);
  if (dist < r) return 0;
  if (dcmp(dist - r) == 0) {
    v[0] = v[1] = Rotate(u, pi/2);
    return 1;
  }
  double ang = asin(r/dist);
  v[0] = Rotate(u, -ang);
  v[1] = Rotate(u, ang);
  return 2;
}
#include <iostream>

void g_2018_final1() {
  double x, y, r;
  while (cin >> x >> y >> r) {
    Point a, b, c(x, y);
    cin >> a.x >> a.y >> b.x >> b.y;
    double d = DistToLine(c, a, b);

    Vector v1 = a - c, v2 = b - c;
    double d1 = Length(v1), d2 = Length(v2);
    double arg = Angle(v1, v2) - acos(r / d1) - acos(r / d2);
    if (arg > 0) {
      cout << sqrt(d1*d1 - r*r) + sqrt(d2*d2 - r*r) + arg * pi << '\n';
    }
    else cout << Length(a - b) << '\n';
  }
}
// 判断下一步是左转还是右转。对于每次转弯输出一个字符，左转输出'L'，右转输出'R'，直走不输出。
void b_2018_c6() {
  int n;
  while (cin >> n) {
    vector<Point> vp(n);
    for (int i = 0; i < n; i++) cin >> vp[i].x >> vp[i].y;
    Vector a = vp[1] - vp[0];
    for (int i = 2; i < n; i++) {
      Vector b = vp[i] - vp[i-1];
      // a在b左边 直走不输出
      if (dcmp(Cross(a, b)) < 0) cout << "R ";
      else if (dcmp(Cross(a, b)) > 0) cout << "L ";
      a = b; 
    }
    cout << '\n';
  }
}
// 求线段交点
void e_2018_c6() {
  Point a1, a2, b1, b2;
  while (cin >> a1.x >> a1.y >> a2.x >> a2.y >> b1.x >> b1.y >> b2.x >> b2.y) {
    // 线段平行时，特判两线段只有端点重合的情况
    if (dcmp(Cross(a1-a2, b1-b2)) == 0) { 
      if (IsParallelIntersection(a1, a2, b1, b2) == 0) {
        Point r = (a1 == b1 || a1 == b2) ? a1 : a2;
        printf("%lf %lf\n", r.x, r.y);
      }
      else printf("none\n");
    }
    else {
      Point r = Intersection(a1, a2, b1, b2);
      // 如果直线交点都在线段上
      if (OnSegment(r, a1, a2) && OnSegment(r, b1, b2)) 
        printf("%lf %lf\n", r.x, r.y);
      else printf("none\n");
    }
  }
}
// 判断两个凸包是否相离
void f_2018_c6() {
  int n, m; 
  while (cin >> n >> m) {
    vector<Point> va(n), vb(m);
    for (int i = 0; i < n; i++) cin >> va[i].x >> va[i].y;
    for (int i = 0; i < m; i++) cin >> vb[i].x >> vb[i].y;

    vector<Point> cha = ConvexHull(va), chb = ConvexHull(vb);
    cout << (IsConvexHullJoint(cha, chb) ? "YES" : "NO") << '\n';
  }
}
// 输出点集的周长和面积
void h_2018_c5() {
  int n;
  while (cin >> n) {
    vector<Point> v(n), ch;
    for (int i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    ch = ConvexHull(v);

    double c = PolygonPerimeter(ch), s = fabs(PolygonArea(ch));
    printf("%.2lf %.2lf\n", c, s);
  }
}
// 输入n个点，输出按逆时针极角排序
// 注意：只能排半平面
void d_2016_c6() {
  int n; 
  while (cin >> n) {
    vector<pair<int, Point>> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].first >> v[i].second.x >> v[i].second.y;
    sort(v.begin(), v.end(), [&](pair<int, Point> a, pair<int, Point> b) {
      Point p0(0, 0), p1 = a.second, p2 = b.second;
      double c = Cross(p1-p0, p2-p0);
      return dcmp(c) ? dcmp(c) > 0 : Length(p1-p0) < Length(p2-p0);
    });
    for (int i = 0; i < n; i++) cout << v[i].first << ' ';
    cout << '\n';
  }
}
// 坟墓的一个固定的小的距离上立上栅栏，求至少要围多长的栅栏
// 栅栏长度即为凸包周长加上以固定小距离为半径的圆的周长
void d_2015_c6() {
  const double pi = acos(-1.0);
  int n, r;
  while (cin >> n >> r) {
    vector<Point> v(n), ch;
    for (int i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    ch = ConvexHull(v);
    
    double ans = 2 * pi * r;
    ans += PolygonPerimeter(ch);
    printf("%.lf\n", ans);
  }
}
// 求最远点对和最近点对的平方
void e_2015_c6() {
  int n; cin >> n;
  vector<Point> v(n), ch, tv(n);
  for (int i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
  ch = ConvexHull(v);
  printf("%.lf %.lf\n", ClosestPair(v, 0, n, tv), FarestPair(ch));
}
// 判断n条线段是否两两相交，输出未被覆盖的线段
void a_2014_c6() {
  int n; 
  while (cin >> n) {
    vector<Point> v(2 * n);
    vector<int> cov(n);
    auto judge = [&](Point a1, Point a2, Point b1, Point b2) {
      // 平行
      if (dcmp(Cross(a1-a2, b1-b2)) == 0) {
        if (IsParallelIntersection(a1, a2, b1, b2) >= 0) return true;
        else return false;
      }
      // 不平行
      if (IsSegmentIntersection(a1, a2, b1, b2)) return true;
      return false;
    };
    for (int i = 0; i < 2 * n; i++) cin >> v[i].x >> v[i].y;
    // 判断第i条线段能够覆盖前[0, i-1]条
    for (int i = 0; i < 2 * n; i += 2) {
      for (int j = 0; j < i; j += 2) {
        if (judge(v[i], v[i+1], v[j], v[j+1])) cov[j / 2] = 1;
      }
    }
    for (int i = 0; i < n; i++)
      if (!cov[i]) cout << i + 1 << ' ';
    cout << '\n';
  }
}
// 输出最远点对的平方
void b_2014_c6() {
  int n; 
  while (cin >> n) {
    vector<Point> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    printf("%.lf\n", FarestPair(ConvexHull(v)));
  }
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0);
  g_2018_final1();
  // b_2018_c6();
  // e_2018_c6();
  // f_2018_c6();
  // h_2018_c5();
  // d_2016_c6();
  // d_2015_c6();
  // e_2015_c6();
  // a_2014_c6();
  // b_2014_c6();
}
