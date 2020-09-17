#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 23;
char str[maxn][40];
int visited[maxn];
int len[maxn];

int n;
long res, total;

void dfs(int cur)
{
    res = max(total, res);

    for (int i = 0; i < n; i++) {
        if (visited[i] < 2) {
            int ok = 1;
            for (int j = 1; j < len[cur]; j++) {
                for (int k = 0; k < len[i]; k++) {
                    if (str[cur][j+k] != str[i][k]) break;
                }
            }
        }
    }
}
int main()
{
#ifdef local
    freopen("p1019.txt", "r", stdin);
#endif

    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%s", str[i]);
        len[i] = strlen(str[i]);
    }

    char initial;
    cin >> initial;
    for (int i = 0; i < n; i++) {
        if (str[i][0] == initial) {
            visited[i]++;
            total += len[i];
            dfs(i);
            total -= len[i];
            visited[i]--;
        }
    }
    cout << res << endl;
    return 0;
}
