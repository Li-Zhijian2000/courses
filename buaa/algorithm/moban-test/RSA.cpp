#include <vector>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

typedef vector<int> vi;
typedef vector<long> vl;
typedef pair<long, long> pll;

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

long gcd(long a, long b) { return b == 0 ? a : gcd(b, a%b); }
long gcd(long a, long b, long& x, long& y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  long t = gcd(b, a%b, y, x);
  y -= x * (a/b);
  return t;
}
long Inverse(long a, long n) {
  long x, y, d = gcd(a, n, x, y);
  return d == 1 ? (x+n) % n : -1;
}
long PowMod(long a, long b, long n) {
  auto bin = [&](long x, int r) {
    vi v;
    while (x > 0) {
      v.push_back(x % r);
      x /= r;
    }
    return v;
  };
  long d = 1, c=0;
  vi v = bin(b, 2);
  for (int i = v.size()-1; i >= 0; i--) {
    c *= 2;
    d = (d * d) % n;
    if (v[i] == 1) {
      c++;
      d = (d * a) % n;
    }
    cout << c << ": " << d << '\n';
  }
  return d;
}
pair<pll, pll> GenKey() {
  vi prime = GenPrimes(1L << 15);
  long p = prime[rand() % prime.size()], q = prime[rand() % prime.size()];
  cout << p << ' ' << q << '\n';
  long n = p * q, phi = (p-1) * (q-1);
  long e = 65537, d = Inverse(e, phi);
  cout << e << ' ' << d << ' ' << phi << '\n';
  return make_pair(pll(e, n), pll(d, n));
}
long encrypt(long m, pll pubkey) {
  return PowMod(m, pubkey.first, pubkey.second);
}
long decrypt(long m, pll prikey) {
  return PowMod(m, prikey.first, prikey.second);
}

int main() {
  long e = 65537, phi = 1810907081;
  // cout << PowMod(e, phi-2, phi) << '\n';
  cout << Inverse(e, phi) << '\n';
  // auto key = GenKey();

  // string info; cin >> info;
  // long m = 0;
  // for (int i = info.size()-1; i >= 1; i--)  m = (m+info[i]-'a') * 26;
  // m += info[0] - 'a';
  // long c = encrypt(m, key.first);
  // m = decrypt(c, key.second);
  // while (m) {
  //   char ch = m % 26 + 'a';
  //   cout << ch;
  //   m /= 26;
  // }
  // cout << '\n';
  // return 0;
}