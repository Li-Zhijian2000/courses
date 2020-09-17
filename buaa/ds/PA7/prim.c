#include <stdio.h>
#include <stdlib.h>                          
#include <string.h>
#define MAXINT 0x7f7f7f7f
#define maxv 300
#define maxe 1000

int verMatrix[maxv][maxv];
int weight[maxe];
int priority[maxv], parent[maxv], isvisit[maxv];
int tree[maxv], treeSize;
int v, e, totalWeight;

void primPrioUpdater(int pa, int ch)
{
    if (!isvisit[ch])
        if (priority[ch] > weight[verMatrix[pa][ch]]) {
            priority[ch] = weight[verMatrix[pa][ch]];
            parent[ch] = pa;
        }
}
void pfs(int ver, void prioUpdater(int, int))
{   
    priority[ver] = 0;
    isvisit[ver] = 1;
    parent[ver] = 0;

    int i, j, k, shortest;
    for (i = 1; i < v; i++) {
        for (j = 0; j < v; j++)
            if (verMatrix[ver][j])
                prioUpdater(ver, j);

        for (shortest = MAXINT, j = 0; j < v; j++)
            if (!isvisit[j])
                if (shortest > priority[j]) {
                    shortest = priority[j];
                    ver = j;
                }

        isvisit[ver] = 1;
        totalWeight += weight[tree[treeSize++] = verMatrix[parent[ver]][ver]];
    }
}
int cmp(const void *a, const void *b){return *(int *)a - *(int *)b;}
int main()
{   
    scanf("%d%d", &v, &e);
    int i, e0, v1, v2, w;
    for (i = 0; i < e; i++) {
        scanf("%d%d%d%d", &e0, &v1, &v2, &w);
        verMatrix[v1][v2] = verMatrix[v2][v1] = e0;
        weight[e0] = w;
    }

    memset(priority, 0x7f, sizeof(priority));
    pfs(0, primPrioUpdater);

    qsort(tree, treeSize, sizeof(tree[0]), cmp);
    printf("%d\n", totalWeight);
    for (i = 0; i < treeSize; i++)
        printf("%d ", tree[i]);
    putchar('\n');
    return 0;
}