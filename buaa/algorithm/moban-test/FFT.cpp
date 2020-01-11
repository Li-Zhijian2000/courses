#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;

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
// a.size() 必须为 2^k
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
  vector<double> res(S);
  for(int i = 0; i < S; i++) res[i] = a[i].x; // 虚部均为0
  return res;
}


#include <iostream>
#include <map>
// 石头剪刀布，想哥给出一个长度为n的序列，而叶姐给出长度为m的序列。
// 叶姐显然有特权，她可以选择跳过想哥序列的一段开头，才开始将RSP序列进行匹配，以寻求从这一位置开始最多获胜次数。
// 字符串匹配，用a匹配b，注意本题匹配开始位置为b[0, n)
void c_2018_final() {
  // a <= b, m <= n
  int n, m; cin >> n >> m;
  string a, b; cin >> b >> a;

  map<char, char> mcc {{'R', 'S'}, {'S', 'P'}, {'P', 'R'}};

  // 转换匹配字串
  for (int i = 0; i < m; i++) a[i] = mcc[a[i]];
  reverse(a.begin(), a.end());
  // s1 匹配 s2
  auto solve = [&](string& s1, string& s2, char c) {
    int m = a.size(), n = b.size();
    vector<double> a(m), b(n);
    for (int i = 0; i < m; i++) 
      if (s1[i] == c) a[i] = 1;
    for (int i = 0; i < n; i++) 
      if (s2[i] == c) b[i] = 1;
    return a * b;
  };
  vector<double> t1, t2, t3;
  t1 = solve(a, b, 'R');
  t2 = solve(a, b, 'S');
  t3 = solve(a, b, 'P');

  int len = t1.size();
  vi ans(len);
  for (int i = 0; i < len; i++) 
    ans[i] = (int)(fabs(t1[i]) + 0.5) + (int)(fabs(t2[i]) + 0.5) + (int)(fabs(t3[i]) + 0.5);

  cout << *max_element(ans.begin()+m-1, ans.end()) << '\n';
}

// 高精度乘法
/* 
input:
-12345678
-12345678
output:
152415765279684
*/
// 高精度乘法
void a_2018_c6() {
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

    vector<double> sum = v1 * v2;
    int s = sum.size();
    vi ans(s);
    for (int i = 0; i < s; i++) ans[i] = fabs(sum[i]) + 0.5;
    // 进位
    for(int i = 1; i < s; i++) {
      ans[i] += ans[i-1]/10;
      ans[i-1] %= 10;
    }
    while(s > 0 && ans[s-1] <= 0) s--;
    // 注意-0
    if(!s) cout << "0\n";
    else {
      if (flag == -1) cout << '-';
      for(int i = s-1;i >= 0;i--) cout << ans[i];
      cout << '\n';
    }
  }
}
// 形成三角形概率
void f_2015_c6() {
  int t; cin >> t;
  while (t--) {
    long n; cin >> n;
    // 3 <= n <= 1e4, a[i] <= 1e5
    vector<long> a(n), num(1e6);
    // num：a[i] 的出现次数
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      num[a[i]]++;
    }
    sort(a.begin(), a.end());
    int s1 = a[n-1]+1;
    vector<double> v1(s1);
    for (int i = 0; i < s1; i++) v1[i] = num[i];
    vector<double> v2 = v1 * v1;
    // num[i] 即为 两两相加出现的次数
    int s = v2.size();
    for (int i = 0; i < s; i++) num[i] = fabs(v2[i] + 0.5);
    // 减掉取两个相同的组合
    for (int i = 0; i < n; i++) num[a[i] + a[i]]--;
    for (int i = 1; i < s; i++) num[i] /= 2;
    // 求前缀和，加快求解
    vector<long> sum(s);
    for (int i = 1; i < s; i++) sum[i] = sum[i-1] + num[i];
    long cnt = 0, total = n * (n-1) * (n-2) / 6;
    for (int i = 0; i < n; i++) {
      cnt += sum[s-1] - sum[a[i]];
      //减掉一个取大，一个取小的
      cnt -= (n-i-1) * i;
      //减掉一个取本身，另外一个取其它
      cnt -= n-1;
      cnt -= (n-i-1) * (n-i-2) / 2;
    }
    printf("%.6lf\n", (double)cnt / total);
  }
}

// 多项式乘法
int a() {
  int n, m; cin >> n >> m;

  vector<double> v1(n + 1), v2(m + 1);
  for (int i = 0; i <= n; i++) cin >> v1[i];
  for (int i = 0; i <= m; i++) cin >> v2[i];

  vector<double> ans = v1 * v2;
  ans.resize(n+m+1);
  for (int i = 0; i < ans.size(); i++) {
    int x = fabs(ans[i]) + 0.5;
    cout << x << ' ';
  }
  cout << '\n';
  return 0;
}
// 给定一个数组，问有多少对a[i]+a[j]==a[k],i,j,k两两不同。
// 把数组中所有元素转化为指数，该元素的出现次数转换为系数，例如原数组为 1 1 1 2 3 3 4 4 转换后为则可看成3*x^1 + x^2 + 2*x^3 + 2*x^4 ，与自身进行卷积后，得到的就是所有加法出现的结果和出现的次数。最后统计每个出现的和值的次数即可。
// 考虑负数，0+x，0+0，最后结果减去0的个数减一的二倍
int c() {
  const int offset = 50000;
  long n; cin >> n;
  // a[i] = [-50000, 50000], (a[i] + offset) * 2 < 2 * 1e5
  vector<long> a(n), num(1e6);
  int zero = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (!a[i]) zero++;
    a[i] += offset;
    num[a[i]]++;
  }
  sort(a.begin(), a.end());
  int s1 = a[n-1]+1;
  vector<double> v1(s1);
  for (int i = 0; i < s1; i++) v1[i] = num[i];
  vector<double> v2 = v1 * v1;
  int s = v2.size();
  for (int i = 0; i < s; i++) num[i] = fabs(v2[i] + 0.5);

  for (int i = 0; i < n; i++) num[a[i]+a[i]]--;
  long ans = 0;
  for (int i = 0; i < n; i++) ans += num[a[i]+offset];
  ans -= 2 * (n-1) * zero;
  cout << ans << '\n';
}

// a 匹配 b 含通配符
// 返回匹配在b中位置
vi FFTMatch(string s1, string s2) {
  reverse(s1.begin(), s1.end());
  int m = s1.size(), n = s2.size(), len = 2;
  while(len < m + n) len <<= 1;

  vi a(len), b(len);
  for (int i = 0; i < m; i++)
    a[i] = (s1[i] != '*') ? (s1[i]-'a'+1) : 0;
  for (int i = 0; i < n; i++)
    b[i] = (s2[i] != '*') ? (s2[i]-'a'+1) : 0;

  vector<CD> t1(len), t2(len), p(len);
  for (int i = 0; i < len; i++) {
    t1[i] = a[i] * a[i] * a[i];
    t2[i] = b[i];
  }
  FFT(t1, 0);
  FFT(t2, 0);
  for (int i = 0; i < len; i++)
    p[i] = p[i] + t1[i] * t2[i];

  for (int i = 0; i < len; i++) {
    t1[i] = a[i];
    t2[i] = b[i] * b[i] * b[i];
  }
  FFT(t1, 0);
  FFT(t2, 0);  
  for (int i = 0; i < len; i++)
    p[i] = p[i] + t1[i] * t2[i];

  for (int i = 0; i < len; i++) {
    t1[i] = a[i] * a[i];
    t2[i] = b[i] * b[i];
  }
  FFT(t1, 0);
  FFT(t2, 0);    

  for (int i = 0; i < len; i++)
    p[i] = p[i] - 2 * t1[i] * t2[i];  
  
  FFT(p, 1);

  vi ans;
  for (int k = 0; k <= n-m; k++) {
    if ((int)(fabs(p[k+m-1].x) + 0.5) == 0)
      ans.push_back(k);
  }
  return ans;
}

int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // c_2018_final();
  a_2018_c6();
  // f_2015_c6();
  // c();
  return 0;
}