// #define local
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int main()
{
#ifdef local
    freopen("b.txt", "r", stdin);
#endif
    
    int n, k;
    while (~scanf("%d%d", &n, &k)) {
        priority_queue<long, vector<long>, less<long>> pq;

        for (int i = 0; i < n; i++) {
            long x;
            scanf("%ld", &x);
            pq.push(x);
        }

        while (k--) {
            long top = pq.top();
            pq.pop();
            pq.push(top >> 1);
        }
        long res = 0;

        while (!pq.empty()) {
            long top = pq.top();
            pq.pop();
            res += top;
        }
        printf("%ld\n", res);
    }
    return 0;
}
