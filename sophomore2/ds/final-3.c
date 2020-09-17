#include <stdio.h>

#define maxn 305
typedef struct {
    int parent;
    int childs[8];
    int type;
    int poindex; // preorder index
} Node;

Node nodes[maxn];
int queue[maxn], depth[maxn], vis[maxn], pa[maxn];

int idx = 1;
void preorder(int x) {
    nodes[x].poindex = idx++;

    int i;
    for (i = 0; i < 8; i++) {
        int nx = nodes[x].childs[i];
        if (nx) preorder(nx);
    }
}
int main() {
    FILE *in = fopen("in.txt", "r");
    int n, x;
    scanf("%d%d", &n, &x);
    x++;

    int i;
    for (i = 0; i < n; i++) {
        int x, pa, type, port;
        fscanf(in, "%d%d%d%d", &x, &pa, &type, &port);
        x++, pa++; // 根为1
        if (!pa) {
            nodes[x].parent = pa;
        } else {
            nodes[pa].childs[port] = x;
            nodes[x].parent = pa;
            nodes[x].type = type;
        }
    }

    preorder(1);

    // bfs
    int front = 0, back = 0, aim = 0;
    queue[back++] = x;
    while (front < back) {
        int u = queue[front++];
        if (vis[u]) continue;
        vis[u] = 1;
        // printf(": %d %d %d %d\n", u, depth[u], nodes[u].type, aim);
        if (aim && depth[u] > depth[aim]) break;
        if (nodes[u].type == 2) aim = u;

        int v = nodes[u].parent;
        if (v && !vis[v]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            queue[back++] = v;
        }
        for (i = 0; i < 8; i++) {
            v = nodes[u].childs[i];
            if (v && !vis[v]) {
                pa[v] = u;
                depth[v] = depth[u] + 1;
                queue[back++] = v;                    
            }
        }
        
    }

    for (i = 1; i <= n; i++) {
        if (nodes[i].type == 2 && depth[i] == depth[aim] && nodes[i].poindex < nodes[aim].poindex)
            aim = i;
    }
    printf("%d ", aim - 1);
    int stack[maxn];
    int size = 0;
    aim = pa[aim];
    while (aim != x) {
        stack[size++] = aim;
        aim = pa[aim];
    }
    while (size > 0) {
        printf("%d ", stack[--size] - 1);
    }
    printf("\n");
    return 0;
}