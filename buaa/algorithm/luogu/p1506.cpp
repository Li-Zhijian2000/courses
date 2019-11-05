// #define local
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 505;

int x, y;
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
bool visited[maxn][maxn];

void dfs(int curx, int cury)
{
    if (curx < 0 || curx >= x || cury < 0 || cury >= y) return;
    visited[curx][cury] = true;

    for (int i = 0; i < 4; i++) {
        int newx = curx + dx[i], newy = cury + dy[i];
        if (!visited[newx][newy]) dfs(newx, newy);
    }
}
int main()
{
#ifdef local
    freopen("p1506.txt", "r", stdin);
#endif

    cin >> x >> y;

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            char c;
            scanf(" %c", &c);
            if (c == '0') visited[i][j] = false;
            else visited[i][j] = true;
        }
    }
    
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (i == 0 || i == x-1 || j == 0 || j == y-1)
                if (!visited[i][j]) dfs(i, j);
        }
    }

    long res = 0;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            if (!visited[i][j]) res++;
    cout << res << endl;
    return 0;
}
