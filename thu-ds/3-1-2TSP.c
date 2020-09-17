#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxe 1000000 + 5
#define maxv 100000 + 5

typedef struct
{
    int from;
    int to;
    int weight;
}Edge;

Edge edge[maxe];
int first[maxe], next[maxe];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    memset(first, -1, sizeof(first));
    for (int e = 0; e < m; e++) {
        int u, v ,w;
        scanf("%d%d%d", &u, &v, &w);
        edge[e] = (Edge){u, v, w};
        next[e] = first[u];
        first[u] = e;
    }
    return 0;
}
