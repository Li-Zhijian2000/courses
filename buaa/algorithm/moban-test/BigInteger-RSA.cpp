#include <vector>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;
struct BigInt;
typedef vector<int> vi;
typedef pair<BigInt, BigInt> pbb;
struct BigInt {
  static const int base = 1e4;
  static const int width = 4;
  static const int maxn = 1e4;
  int a[maxn];
  int len;
  int sign;

  BigInt(long num=0) { *this = num; }
  // 无法判断“0000000...0000000000"
  BigInt(string s) {
    if (s[0] == '-') {
      sign = -1;
      s = s.substr(1, s.size()-1);
    }
    else sign = 1;
    fill(a, a+maxn, 0);
    int n = s.size();
    // 向上取整
    len = (n + width - 1) / width;
    int j = 0;
    for (int i = n-1; i >= 0; i -= width) {
      int t = 0;
      int k = max(i - width + 1, 0);
      for (int j = k; j <= i; j++) t = t*10 + s[j] - '0';
      a[j++] = t;
    }
    clean();
  }
  void clean() {
    while (a[len-1] == 0 && len > 1) len--;
    if (len == 1 && a[len-1] == 0) sign = 0;
  }
  BigInt operator= (long num) {
    if (num < 0) {
      sign = -1;
      num = -num;
    }
    else if (num == 0) sign = 0;
    else sign = 1;

    fill(a, a+maxn, 0);
    len = 0;
    do {
      a[len++] = num % base;
      num /= base;
    } while (num > 0);
    return *this;
  }
  BigInt operator- () {
    BigInt a(*this);
    a.sign *= -1;
    return a;
  }
  // 可算同正同负
  BigInt operator+ (BigInt b) {
    BigInt a(*this);
    if (a.sign * b.sign == -1) return a - -b;
    int big = max(a.len , b.len);
    for (int i = 0; i < big; i++) {
      a.a[i] += b.a[i];
      if (a.a[i] >= base) {
        a.a[i] %= base;
        a.a[i+1]++;
      }
    }
    if (a.a[big] != 0) big++;
    a.len = big;
    a.clean();
    return a;
  }
  BigInt operator- (BigInt b) {
    BigInt a(*this);
    if (a.sign * b.sign == -1) return a + -b;
    if (a.sign == -1 && b.sign == -1) return -b - -a;
    if (a < b) {
      BigInt t = b - a;
      return -t;
    }

    int big = a.len;
    for (int i = 0, j; i < big; i++) {
      if (a.a[i] < b.a[i]) {
        j = i + 1;
        while (a.a[j] == 0) j++;
        a.a[j--]--;
        while (j > i) a.a[j--] += base - 1;
        a.a[i] += base - b.a[i];
      }
      else a.a[i] -= b.a[i];
    }
    a.sign = 1;
    a.len = big;
    a.clean();
    return a;
  }
  BigInt operator* (BigInt b) {
    BigInt res;
    for (int i = 0, j; i < len; i++) {
      int up = 0;
      for (j = 0; j < b.len; j++) {
        int tmp = a[i] * b.a[j] + res.a[i+j] + up;
        if (tmp >= base) {
          int t = tmp - tmp / base * base;
          up = tmp / base;
          res.a[i+j] = t;
        }
        else {
          up = 0;
          res.a[i+j] = tmp;
        }
      }
      if (up) {
        res.a[i+j] = up;
      }
    }
    res.sign = sign * b.sign;
    res.len = len + b.len;
    res.clean();
    return res;
  }
  // BigInt operator/ (long b) {
  //   BigInt res;
  //   long down = 0;
  //   for (int i = len-1; i >= 0; i--) {
  //     res.a[i] = (a[i] + down * base) / b;
  //     down = a[i] + down * base - res.a[i] * b;
  //   }
  //   res.len = len;
  //   res.clean();
  //   return res;
  // }
  bool operator< (BigInt b) {
    if (sign == -1 && b.sign == 1) return true;
    if (sign == 1 && b.sign == -1) return false;
    if (sign == -1 && sign == -1) return (-b < -*this);
    if (len < b.len) return true;
    if (len > b.len) return false;
    int t = len - 1;
    while (a[t] == b.a[t] && t >= 0) t--;
    if (t >= 0 && a[t] < b.a[t]) return true;
    else return false;
  }
  bool operator== (BigInt b) { return !(*this < b) && !(b < *this); }
  BigInt operator<< (int x) {
    BigInt res;
    res.len = len + x;
    for (int i = 0; i < len; i++) res.a[i+x] = a[i];
    return res;
  }
  pbb operator/ (BigInt b) {
    pbb res;
    BigInt& quo = res.first;
    BigInt& rem = res.second;
    quo.len = len - b.len + 1;
    rem = *this;

    int k = log2(base);
    vi pow(k+5);
    pow[0] = 1;
    for (int i = 1; i <= k; i++) pow[i] = pow[i-1] * 2;
    for (int i = quo.len-1; i>= 0; i--) {
      BigInt t = b << i;
      for (int j = k; j >= 0; j--) {
        BigInt t2 = BigInt(pow[j]) * t;
        if (!(rem < t2)) {
          quo.a[i] += pow[j];
          rem = rem - t2;
        }
      }
    }
    quo.sign = sign * b.sign;
    rem.sign = sign * b.sign;
    quo.clean();
    rem.clean();
    return res;
  }
  void print() {
    if (sign == -1 && a[len-1] != 0) putchar('-');
    printf("%d", a[len-1]);
    for (int i = len-2; i >= 0; i--) printf("%04d", a[i]);
    puts("");
  }
};

BigInt gcd(BigInt a, BigInt b) {
  return b == 0 ? a : gcd(b, (a/b).second);
}
BigInt gcd(BigInt a, BigInt b, BigInt& x, BigInt& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  BigInt t = gcd(b, (a/b).second, y, x);
  y = y - x*(a/b).first;
  return t;
}
BigInt Inverse(BigInt a, BigInt n) {
  BigInt x, y, d = gcd(a, n, x, y);
  return d == 1 ? ((x+n) / n).second : -1;
}
BigInt MulMod(BigInt a, BigInt b, BigInt n) {
  return (a * b / n).second;
}

// BigInt PowMod(BigInt a, BigInt p, BigInt n) {
//   if (p == BigInt(0)) return 1;
//   BigInt res = PowMod(a, (p/2), n);
//   res = (res * res / n).second;
//   if ((p/BigInt(2)).second == BigInt(1)) res = (res * a / n).second;
//   return res;
// }
BigInt PowMod(BigInt a, BigInt b, BigInt n) {
  auto bin = [](BigInt x, int r) {
    vi v;
    while (!(x == BigInt(0))) {
      auto t = x / BigInt(2);
      v.push_back(t.second.a[0]);
      x = t.first;
    }
    return v;
  };
  BigInt d = 1, c = 0;
  vi v = bin(b, 2);
  for (int i = v.size()-1; i >= 0; i--) {
    d = ((d * d) / n).second;
    c = c * 2;
    if (v[i] == 1) {
      c = c + 1;
      d = ((d * a) / n).second;
    }
  }
  return d;
}


const string p = "479001599";
const string q = "87178291199";
const string m = "234";

vi GenPrimes(int n) {
  vi prime;
  vi vis(n);
  int m = sqrt(n+0.5);
  for (int i = 2; i <= m; i++) {
    if (!vis[i]) {
      for (int j = i*i; j < n; j += i) vis[j] = 1;
    }
  }

  for (int i = 2; i < n; i++) if (!vis[i]) prime.push_back(i);
  return prime;
}
// 公钥，私钥
pair<pbb, pbb> GenKey() {
  vi prime = GenPrimes(1L << 20);
  long a = prime[rand() % prime.size()], b = prime[rand() % prime.size()];
  cout << a << ' ' << b << '\n';
  BigInt p(a), q(b), n = p * q, phi = (p - 1) * (q - 1);
  BigInt e = 65537;
  BigInt d = Inverse(e, phi);
  e.print(); d.print(); phi.print();
  return make_pair(pbb(e, n), pbb(d, n));
}
BigInt encrypt(BigInt m, pbb pubkey) {
  return PowMod(m, pubkey.first, pubkey.second);
}
BigInt decrypt(BigInt m, pbb prikey) {
  return PowMod(m, prikey.first, prikey.second);
}
int main() {
  // auto key = GenKey();
  // auto c = encrypt(BigInt(m), key.first);
  // // c.print();
  // auto d = decrypt(c, key.second);
  // // d.print();
  return 0;
}