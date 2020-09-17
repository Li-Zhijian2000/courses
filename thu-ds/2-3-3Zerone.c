#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 30000000 + 5

typedef struct 
{
    int winner;
    int height;
    int lChild;
    int rChild;
}Node;

Node node[maxn];
int nodeSize = 2, root = 1;

//0: none, 1: Adam, 2: Eve
int winner[maxn / 9];

void update(char *str, int posi)
{
    if (*str == '0') {
        if (!node[posi].lChild) {
            node[posi].lChild = nodeSize;
            node[nodeSize++].height = node[posi].height + 1;
        }
        update(str + 1, node[posi].lChild);
    }
    else if (*str == '1') {
        if (!node[posi].rChild) {
            node[posi].rChild = nodeSize;
            node[nodeSize++].height = node[posi].height + 1;
        }
        update(str + 1, node[posi].rChild);
    }
    else if (!*str) {
        if (!node[posi].winner) {
            node[posi].winner = node[posi].height % 2 ? 2 : 1;
        }
        return;
    }

    if (node[posi].height % 2) {
        node[posi].winner = (node[node[posi].lChild].winner == 1 || node[node[posi].rChild].winner == 1) ? 1 : 2;
    }
    else {
        node[posi].winner = (node[node[posi].lChild].winner == 2 || node[node[posi].rChild].winner == 2) ? 2 : 1;
    }
}
void preOrder(int posi)
{
    if (!posi) {
        return;
    }
    printf("%d", node[posi].winner);
    preOrder(node[posi].lChild);
    preOrder(node[posi].rChild);
}
int main()
{
    int n;
    char string[80];
    scanf("%d", &n);
    node[root] = (Node){0, 1};

    for (int i = 0; i < n; i++) {
        scanf("%s", string);
        
        update(string, root);
        winner[i] = node[root].winner;
    }
    
    int count = 0;
    winner[n] = 2;
    for (int i = 0; i < n; i++) {
        if (winner[i] != winner[i+1]) {
            printf("%s %d %d\n", (winner[i] == 1) ? "Adam" : "Eve", i - count + 1, i + 1);
            count = 0;
        }
        else count++;
    }
    preOrder(root);
    putchar('\n');
    return 0;
}