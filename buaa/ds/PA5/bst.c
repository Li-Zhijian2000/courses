#include <stdio.h>
#define maxn 205

struct Node {
    int value;
    int lChild;
    int rChild;
    int height;
};

struct Node node[maxn];
int nodeSize = 1;
int root;

void inOrder(int);

int main()
{
    int n, key, posi;
    scanf("%d", &n);

    while (n--) {
        scanf("%d", &key);
        if (!root) {
            root = nodeSize++;
            node[root] = (struct Node){key, 0, 0, 1};
        }
        else {
            posi = root;
            while (1) {
                if (key < node[posi].value) {
                    if (node[posi].lChild)
                        posi = node[posi].lChild;
                    else {
                        node[posi].lChild = nodeSize;
                        node[nodeSize++] = (struct Node){key, 0, 0, node[posi].height + 1};
                        break;
                    };
                }
                else {
                    if (node[posi].rChild)
                        posi = node[posi].rChild;
                    else {
                        node[posi].rChild = nodeSize;
                        node[nodeSize++] = (struct Node){key, 0, 0, node[posi].height + 1};
                        break;
                    }
                }
            }
        }
    }

    inOrder(root);
    return 0;
}

void inOrder(int posi)
{
    if (!posi)
        return;
    inOrder(node[posi].lChild);
    if (!node[posi].lChild && !node[posi].rChild)
        printf("%d %d\n", node[posi].value, node[posi].height);
    inOrder(node[posi].rChild);
}