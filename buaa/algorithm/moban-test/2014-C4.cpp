// C4-2014级算法第四次上机
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>
#define all(x) x.begin(), x.end()
using namespace std;

const int inf = 0x3f3f3f3f;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

void a() {
  vi coin {1, 5, 10, 50, 100, 500};
  vi num(6);
  while (cin >> num[0]) {
    for (int i = 1; i < 6; i++) cin >> num[i];
    int t; cin >> t;
    int ans = 0;
    for (int i = 5; i >= 0; i--) {
      if (coin[i] * num[i] >= t) {
        ans += t / coin[i];
        t %= coin[i];
      }
      else {
        ans += num[i];
        t -= num[i] * coin[i];
      }
    }
    cout << ans << '\n';
  }
}
void d() {
  struct Node {
    char c;
    int lc, rc, depth;
  };
  int t; cin >> t;
  while (t--) {
    string s; cin >> s;
    vi cnt(128);
    for (int i = 0; i < s.size(); i++) cnt[s[i]]++;
    
    vector<Node> nodes(1);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < 128; i++) {
      if (cnt[i]) {
        pq.push(pii(cnt[i], nodes.size()));
        nodes.push_back((Node){i, 0, 0, 0});
      }
    }
      
    while (pq.size() > 1) {
      pii t1 = pq.top(); pq.pop();
      pii t2 = pq.top(); pq.pop();
      pq.push(pii(t1.first + t2.first, nodes.size()));
      nodes.push_back((Node){0, t1.second, t2.second, 0});
    }

    // bfs 更新结点深度
    vi len(128);
    queue<int> q;
    int x = pq.top().second;
    q.push(x);
    nodes[x].depth = 0;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      if (nodes[x].c) {
        len[nodes[x].c] = nodes[x].depth;
        continue;
      }
      int lc = nodes[x].lc, rc = nodes[x].rc, d = nodes[x].depth;
      if (lc) {
        nodes[lc].depth = d + 1;
        q.push(lc);
      }
      if (rc) {
        nodes[rc].depth = d + 1;
        q.push(rc);
      }
    }

    int ans = 0;
    // 输出字符串的编码长度
    for (int i = 0; i < s.size(); i++) ans += len[s[i]];
    cout << ans << '\n';
  }
}
void e() {
  // convert decimal x to n bits binary
  auto d2b = [](int x, int n) { 
    vi bin(n);
    for (int i = 0; i < n; i++, x /= 2) {
      if (!x) break;
      bin[i] = x % 2;
    }
    return bin;
  };
  auto increase = [](vi& v) {
    int n = v.size(), k = 0;
    for (int i = 0; i < n; i++) {
      if (v[i] == 1) {
        v[i] = 0;
        k++;
      }
      else {
        v[i] = 1;
        break;
      }
    }
    return k;
  };
  // 计数次数，初值
  int n, x; cin >> n >> x;
  vi v = d2b(x, 31);
  for (int i = 0; i < n; i++) {
    cout << "Case " << i + 1 << ":\n";
    int t; cin >> t;
    while (t--) {
      int k = increase(v);
      if (k == v.size()) {
        cout << k << ' ' << 0 << '\n';
        x = 0;
      }
      else {
        cout << k + 1 << ' ' << 2 << '\n';
        x++;
      }
    }
    cout << "Sum: " << x << '\n';
  }
}
void f() {
  // convert decimal x to n bits binary
  auto increase = [](vi& v) {
    int n = v.size(), k = 0;
    for (int i = 0; i < n; i++) {
      if (v[i] == 1) {
        v[i] = 0;
        k++;
      }
      else {
        v[i] = 1;
        break;
      }
    }
    return k;
  };
  // 计数次数，初值
  int n; 
  while (cin >> n) {
    vi v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    reverse(all(v));
    int t; cin >> t;
    while (t--) {
      int k = increase(v);
      cout <<  (k == v.size() ? 0 : 2) << ' '; 
    }
    cout << '\n';
  }
}
int main() {
#ifdef local
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // a();
  // d();
  // e();
  f();
  return 0;
}