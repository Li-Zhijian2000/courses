#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 10;

int n, m;
int orix, oriy, desx, desy;
long res;
int map[maxn][maxn];
bool visited[maxn][maxn];
int blood[maxn][maxn];

void dfs(int x, int y, int blood, int level)
{
    if (x < 0 || x >= n || y < 0 || y >= m) return;
    if (!blood) return;
    if (blood < visited[x][y]) return;
}
int main()
{
#ifdef local
    freopen("p2802.txt", "r", stdin);
#endif

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            map[i][j] = x;
            if (x == 1) {
                orix = i;
                oriy = j;
            }
            if (x == 2) {
                desx = i;
                desy = j;
            }
        }
    
    dfs(orix, oriy, 6, 0);
    return 0;
}
