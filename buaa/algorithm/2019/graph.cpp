#define local
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Edge {
  int from, to, weight;
}
int main() {
#ifdef local
  freopen("graph.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  return 0;
}
