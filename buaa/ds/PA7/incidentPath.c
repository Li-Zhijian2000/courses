#include <stdio.h>
#include <string.h>
#define maxv 1200
#define maxe 3000
struct Edge {
    int isEdge;
    int nextVer;
};
struct Edge matrix[maxv][maxe];
int v, e;
int path[maxe], visited[maxv];

void dfs(int ver, int level)
{   
    int i;
    if (ver == v - 1) {
        for (i = 0; i < level; i++)
            printf("%d ", path[i]);
        putchar('\n');
        return;
    }
    visited[ver] = 1;
    for (i = 1; i <= e; i++) {
        if (matrix[ver][i].isEdge && !visited[matrix[ver][i].nextVer]) {
            path[level] = i;
            dfs(matrix[ver][i].nextVer, level + 1);
        }
    }
    visited[ver] = 0;
}

int main()
{
    scanf("%d%d", &v, &e);

    int i, e0, v1, v2;
    for (i = 0; i < e; i++) {
        scanf("%d%d%d", &e0, &v1, &v2);
        matrix[v1][e0] = (struct Edge){1, v2};
        matrix[v2][e0] = (struct Edge){1, v1};
    }
    
    dfs(0, 0);
    
    return 0;
}