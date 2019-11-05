// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int offset = 1e6;
const int maxn = 2 * offset + 5;
vector<int> a;
int b[maxn];

void readvec(vector<int>& a, int n) {
    vector<int> vi;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        vi.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        for (int d: vi)
            a.push_back(d + x + offset);
    }
    
}
void readarray(int* a, int n) {
    vector<int> vi;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        vi.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        for (int d: vi)
            a[d + x + offset]++;
    }    
}
int main() {
#ifdef local
    freopen("f.txt", "r", stdin);
#endif

    int n;
    while (~scanf("%d", &n)) {
        a.clear();
        memset(b, 0, sizeof(b));
        readvec(a, n);
        readarray(b, n);
        long res = 0;
        for (int d: a) {
            res += b[offset*2 - d];
        }
        printf("%ld\n", res);        
    }
    return 0;
}
