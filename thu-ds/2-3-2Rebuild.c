#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 1100000 + 5

typedef struct 
{
    int data;
    int lChild;
    int rChild;
}Node;
Node node[maxn];
int nodeSize = 1;
int root;

int preOrder[maxn], postOrder[maxn];

int rebuild(int alo, int ahi, int blo, int bhi)
{
    if (alo >= ahi) {
        return 0;
    }
    if (alo + 1 == ahi) {
        node[nodeSize].data = preOrder[alo];
        return nodeSize++;
    }
    int r;
    for (int i = blo; i < bhi; i++) {
        if (preOrder[alo + 1] == postOrder[i]) {
            r = i;
            break;
        }
    }
    // printf("%d %d %d %d %d\n", r, alo, ahi, blo,bhi);

    int lc = rebuild(alo + 1, r + alo - blo + 2, blo, r + 1), rc = rebuild(r + alo - blo + 2, ahi, r + 1, bhi - 1);
    node[nodeSize] = (Node){preOrder[alo], lc, rc};       
    return nodeSize++;
}
void inOrder(int posi)
{
    if (!posi) {
        return;
    }
    inOrder(node[posi].lChild);
    printf("%d ", node[posi].data);
    inOrder(node[posi].rChild);
}
int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", preOrder + i);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", postOrder + i);
    }

    root = rebuild(0, n, 0, n);
    inOrder(root);
    putchar('\n');
    return 0;
}