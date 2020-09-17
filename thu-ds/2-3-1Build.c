#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 400005

typedef struct 
{
    int data;
    int lChild;
    int rChild;
}Node;
Node node[maxn];
int nodeSize = 1;
int root;

void preOrder(int posi)
{
    if (!posi) {
        return;
    }
    printf("%d ", node[posi].data);
    preOrder(node[posi].lChild);
    preOrder(node[posi].rChild);
}
void postOrder(int posi)
{
    if (!posi) {
        return;
    }
    
    postOrder(node[posi].lChild);
    postOrder(node[posi].rChild);
    printf("%d ", node[posi].data);
}
int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);

        if (!root) {
            root = nodeSize;
            node[nodeSize++].data = key;
        }
        else {
            int posi = root;
            while (1) {
                if (key < node[posi].data) {
                    if (node[posi].lChild) {
                        posi = node[posi].lChild;
                    }
                    else {
                        node[posi].lChild = nodeSize;
                        node[nodeSize++].data = key;
                        break;
                    }
                }
                else {
                    if (node[posi].rChild) {
                        posi = node[posi].rChild;
                    }
                    else {
                        node[posi].rChild = nodeSize;
                        node[nodeSize++].data = key;
                        break;
                    }
                }
            }
        }
    }

    preOrder(root);
    putchar('\n');
    postOrder(root);
    putchar('\n');
    return 0;
}
