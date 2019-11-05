#define local
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 1e6 + 5;
struct Film {
    long long l;
    long long v;
};
Film films[maxn];

// 大顶堆(greater)
struct cmp_by_l {
    bool operator() (const Film& a, const Film& b)
    {
        return a.l > b.l;
    }
};

// 心情从大到小
bool cmp(const Film& a, const Film& b)
{
    return (a.v != b.v)? (a.v > b.v) : (a.l > b.l);
}

int main()
{
#ifdef local
    freopen("b.txt", "r", stdin);
#endif

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> films[i].l >> films[i].v;
    }
    sort(films, films + n, cmp);

    long long suml = 0, res = 0;
    priority_queue<Film, vector<Film>, cmp_by_l> pq;
    if (k > n) k = n;
    for (int i = 0; i < k; i++) {
        suml += films[i].l;
        pq.push(films[i]);
        res = max(res, suml * films[i].v);
    }
    
    for (int i = k; i < n; i++) {
        long long minv = films[i].v;
        Film f = pq.top();
        if (f.l < films[i].l) {
            pq.pop();
            pq.push(films[i]);

            suml += films[i].l - f.l;
            res = max(res, minv * suml);
        }
    }
    cout << res << endl;
    return 0;
}