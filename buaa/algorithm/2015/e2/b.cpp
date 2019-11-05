// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int readmin(int n) {
    int minn = 0x7f7f7f7f;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        minn = min(minn, x);
    }
    return minn;
}
int main() {
#ifdef local
    freopen("b.txt", "r", stdin);
#endif

    int n;
    while (~scanf("%d", &n)) {
        int mina = readmin(n);
        int minb = readmin(n);
        printf("%d\n", mina + minb);
    }
    return 0;
}
