#define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e5+5;
struct Bag {
  long cost, weight;
  double frac;
  Bag(long c, long w, double f): cost(c), weight(w), frac(c) {}
  bool operator<(const Bag& rhs) { return this->frac < rhs.frac; }
};

int main() {
#ifdef local
  freopen("p1060.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int n;
  while (cin >> n) {
    vector<Bag> vb;
    for (int i = 0; i < n; i++) {
      int c, w;
      cin >> c >> w;
      vb.push_back(Bag(c, w, double(c) / w));
    }
    sort(vb.begin(), vb.end());
  }
  return 0;
}
