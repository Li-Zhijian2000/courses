#define local
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
struct HuffNode {
    char ch;
    int weight;
    int lChild;
    int rChild;
    bool operator <(const HuffNode& rhs) { 
      return (this->ch != rhs.ch) ? this->ch > rhs.ch :
             ;
    }
};

int main() {
#ifdef local
  freopen("haffman.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  char c;
  while (cin >> c) {

  }  
  return 0;
}
