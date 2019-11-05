#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 1000

int edge[maxn][maxn];
int visited[maxn];
int v, e;

void dfs(int ver)
{
    int i;
    visited[ver] = 1;
    printf("%d ", ver);
    for (i = 0; i < v; i++)
        if (!visited[i] && edge[ver][i])
            dfs(i);
}
/*
void dfs(int ver)
{
    memset(visited, 0, sizeof(visited));
    int stack[maxn], size = 0;
    stack[size++] = ver;
    visited[ver] = 1;

    while (size > 0) {
        int cur = stack[--size], i;
        printf("%d ", cur);
        for (i = v - 1; i > 0; i--)
            if (!visited[i] && edge[cur][i]) {
                visited[i] = 1;
                stack[size++] = i;
            }
    }
    putchar('\n');
}
*/
void bfs(int ver)
{
    memset(visited, 0, sizeof(visited));

    int queue[maxn], front = 0, back = 0;
    queue[back++] = ver;
    visited[ver] = 1;

    while (front < back) {
        int cur = queue[front++], i;
        printf("%d ", cur);
        for (i = 0; i < v; i++)
            if (!visited[i] && edge[cur][i]) {
                visited[i] = 1;
                queue[back++] = i;
            }
    }
    putchar('\n');
}
int main()
{
    scanf("%d%d", &v, &e);

    int i, e1, e2;
    for (i = 0; i < e; i++) {
        scanf("%d%d", &e1, &e2);
        edge[e1][e2] = edge[e2][e1] = 1;
    }

    memset(visited, 0, sizeof(visited));
    dfs(0);
    putchar('\n');
    bfs(0);

    int del;
    scanf("%d", &del);
    for (i = 0; i < v; i++) 
        edge[del][i] = edge[i][del] = 0;
    
    memset(visited, 0, sizeof(visited));
    visited[0] = 1;
    dfs(0);
    putchar('\n');
    bfs(0);
    return 0;
}