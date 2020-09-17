#include <cmath>
#include <vector>
using namespace std;

const long double pi = acos(0.0) * 2.0;
typedef struct Complex {
    double x, y;
    Complex(double x=0, double y=0): x(x), y(y) { }
} CD;
Complex operator +(Complex a, Complex b) { return Complex(a.x + b.x, a.y + b.y); }
Complex operator -(Complex a, Complex b) { return Complex(a.x - b.x, a.y - b.y); }
Complex operator *(Complex a, Complex b) { 
  return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
// Cooley-Tukey的FFT算法，迭代实现。inverse = false时计算逆FFT
inline void FFT(vector<CD> &a, bool inverse) {
  int n = a.size();
  // 原地快速bit reversal
  for(int i = 0, j = 0; i < n; i++) {
    if(j > i) swap(a[i], a[j]);
    int k = n;
    while(j & (k >>= 1)) j &= ~k;
    j |= k;
  }

  for(int le = 1; le < n; le <<= 1) {
    CD wn(cos(pi/le), (inverse ? -1 : 1) * sin(pi/le));
    for(int p = 0; p < n; p += le << 1) {
      CD w(1,0);
      for(int k = p; k < le + p; k++, w = w * wn) {
        CD tmpx = a[k], tmpy = w * a[k+le];
        a[k] = tmpx + tmpy;
        a[k+le] = tmpx - tmpy;
      }
    }
  }
  if(inverse)
    for(int i = 0; i < n; i++) a[i].x /= n;
}
// 用FFT实现的快速多项式乘法
inline vector<double> operator * (const vector<double>& v1, const vector<double>& v2) {
  int s1 = v1.size(), s2 = v2.size(), S = 2;
  while(S < s1 + s2) S <<= 1;

  vector<CD> a(S), b(S); // 把FFT的输入长度补成2的幂，不小于v1和v2的长度之和

  for(int i = 0; i < s1; i++) a[i] = v1[i];
  FFT(a, false);
  for(int i = 0; i < s2; i++) b[i] = v2[i];
  FFT(b, false);
  for(int i = 0; i < S; i++) a[i] = a[i] * b[i];
  FFT(a, true);
  vector<double> res(s1 + s2 - 1);
  for(int i = 0; i < s1 + s2 - 1; i++) res[i] = a[i].x; // 虚部均为0
  return res;
}


#include <iostream>
void a() {
  string a, b;
  while (cin >> a >> b) {
    int s1 = a.size(), s2 = b.size();
    int flag = 1;
    if (a[0] == '-') {
      flag *= -1;
      a = a.substr(1, s1 - 1);
      s1--;
    }
    if (b[0] == '-') {
      flag *= -1;
      b = b.substr(1, s2 - 1);
      s2--;
    }
    vector<double> v1(s1), v2(s2);

    for (int i = 0; i < s1; i++) v1[i] = a[s1 - i - 1] - '0';
    for (int i = 0; i < s2; i++) v2[i] = b[s2 - i - 1] - '0';
    vector<double> res = v1 * v2;
    
    int len = res.size();
    vector<int> ans(len + 10, 0);
    for (int i = 0; i < len; i++) ans[i] = fabs(res[i]) + 0.5;
    // 进位
    for(int i = 0; i < len; i++) {
      if(ans[i] >= 10) {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
        len += (i == len-1);
      }     
    }
    while(!ans[len-1] && len > 0) len--;
    if(!len) cout << "0\n";
    else {
      if (flag == -1) cout << '-';
      while (len--) cout << ans[len];
      cout << endl;
    }
  }
}

#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

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
  if (OnSegment(a1, b1, b2) != 0 && OnSegment(a2, b1, b2)) return -1;
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
vector<Point> ConvexHull(const vector<Point>& p) {
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

// 多边形的有向面积
double PolygonArea(const vector<Point>& p) {
  int n = p.size();
  double area = 0;
  for(int i = 1; i < n-1; i++)
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area/2;
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

const double inf = 1e90;
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

void b() {
  int n;
  while (cin >> n) {
    vector<Point> vp(n);
    for (int i = 0; i < n; i++) cin >> vp[i].x >> vp[i].y;
    Vector a = vp[1] - vp[0];
    for (int i = 2; i < n; i++) {
      Vector b = vp[i] - vp[i-1];
      if (dcmp(Cross(a, b)) < 0) cout << "R ";
      else if (dcmp(Cross(a, b)) > 0) cout << "L ";
      a = b;
    }
    cout << '\n';
  }
}
void e() {
  Point a1, a2, b1, b2;
  while (cin >> a1.x >> a1.y >> a2.x >> a2.y >> b1.x >> b1.y >> b2.x >> b2.y) {
    if (dcmp(Cross(a1-a2, b1-b2)) == 0) { 
      if (IsParallelIntersection(a1, a2, b1, b2) == 0) {
        Point r = (a1 == b1 || a1 == b2) ? a1 : a2;
        printf("%lf %lf\n", r.x, r.y);
      }
      else printf("none\n");
    }
    else {
      Point r = Intersection(a1, a2, b1, b2);
      if (OnSegment(r, a1, a2) && OnSegment(r, b1, b2)) 
        printf("%lf %lf\n", r.x, r.y);
      else printf("none\n");
    }
  }
}
void f() {
  int n, m; 
  while (cin >> n >> m) {
    vector<Point> va(n), vb(m);
    for (int i = 0; i < n; i++) cin >> va[i].x >> va[i].y;
    for (int i = 0; i < m; i++) cin >> vb[i].x >> vb[i].y;

    sort(va.begin(), va.begin() + n);                                                                 
    sort(vb.begin(), vb.begin() + m);
    vector<Point> cha = ConvexHull(va), chb = ConvexHull(vb);
    cout << (IsConvexHullJoint(cha, chb) ? "YES" : "NO") << '\n';
  }
}

#include <cstring>
void c() {
  const int maxn = 105;
  int d[maxn][maxn];
  char map[maxn][maxn];
  memset(d, 0x3f, sizeof(d));

  int n, m; cin >> n >> m;
  int h, a, b; cin >> h >> a >> b;
  d[a][0] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) 
      cin >> map[i][j];
  for (int i = 1; i <= n; i++) map[i][m+1] = '0';
  for (int j = 1; j <= m + 1; j++) {
    for (int i = 1; i <= n; i++) {
      if (map[i][j] == '*') continue;

      int t = 0x3f3f3f3f;
      for (int k = i-1; k <= i+1; k++) t = min(t, d[k][j-1]);
      d[i][j] = min(d[i][j], t + map[i][j] - '0');
    }
  }
  if (d[b][m+1] < h) cout << h - d[b][m+1] << '\n';
  else cout << "doctor win\n";
}

const int maxn = 1e5+5;
int m, n; 
long loc[maxn];
bool ok(long x) {
  int t = 1, i = 0;
  while ((i = upper_bound(loc, loc + n, loc[i] + x) - loc - 1) 
    != n - 1) {
    t++;
    if (t > m) return 0;
  }
  return 1;
}
void d() {
  ios::sync_with_stdio(0);  
  int l;
  while (cin >> l >> n >> m) {
    loc[0] = 0; loc[n+1] = l;
    for (int i = 1; i <= n; i++) cin >> loc[i];
    n += 2;
    sort(loc, loc + n);
    long lo = 0, hi = loc[n - 1] + 1;

    while (lo < hi) {
      long mi = lo + hi >> 1;
      ok(mi) ? hi = mi : lo = mi + 1;
    }
    printf("%ld\n", lo);
  }
}

typedef pair<int, int> pii;
// void MergeSort(vector<pii>& v, int lo, int hi) {
//     if (hi - lo < 2) return;

//     int mi = lo + hi >> 1;
//     MergeSort(v, lo, mi), MergeSort(v, mi, hi); 

//     vector<pii> left(v.begin() + lo, v.begin() + mi);
//     vector<pii> right(v.begin() + mi, v.begin() + hi);     

//     for (int i = 0, j = 0; i < left.size() || j < right.size(); ) {
//         if (i < left.size() && (j == right.size() || left[i] <= right[j]))  {
//             v[lo++] = left[i++];
//         }
//         if (j < right.size() && (i == left.size() || left[i] > right[j])) {
//             v[lo] = right[j++];
//             v[lo].second += left.size() - i;
//             lo++;
//         }
//     }
// }
void g() {
  int n; cin >> n;
  vector<pii> v(n);
  for (int i = 0; i < n; i++) {
    int a; cin >> a;
    v[i] = pii(a, i);
  }
  sort(v.begin(), v.begin() + n);
  auto p = max_element(v.begin(), v.begin() + n, [](pii a, pii b) { return a.second < b.second; });
  int ans = 0, maxi = p->second;
  for (; p != v.end(); ++p) ans = max(ans, maxi - p->second);
  cout << ans << '\n';
}
int main() {
  freopen("input.txt", "r", stdin);
  ios::sync_with_stdio(0);
  // a();
  // b();
  // c();
  // d();
  // e();
  // f();
  // g();
  return 0;
}