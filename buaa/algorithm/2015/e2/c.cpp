// #define local
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct Stu {
    int id;
    int gender;
    int score;

    Stu(int s, int g, int sc): id(s), gender(g), score(sc) {}
    bool operator< (const Stu& rhs) const {
        return score != rhs.score ? score < rhs.score :
               gender != rhs.gender ? gender > rhs.gender :
               id > rhs.id;
    }
};
int main() {
#ifdef local
    freopen("c.txt", "r", stdin);
#endif

    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        vector<Stu> stus;
        priority_queue<Stu> pq;
        for (int i = 0; i < n; i++) {
            int s, g, sc;
            scanf("%d%d%d", &s, &g, &sc);
            stus.push_back(Stu(s, g, sc));
        }
        while (m--) {
            char op[10];
            scanf("%s", op);
            if (!strcmp(op, "Add")) {
                int x;
                scanf("%d", &x);
                pq.push(stus[x-1]);
            }
            else if (!strcmp(op, "Delete") && !pq.empty())
                 pq.pop();
            else {
                Stu top = pq.top();
                printf("%d %d %d\n", top.id, top.gender, top.score);
            }
        }
    }
    return 0;
}
