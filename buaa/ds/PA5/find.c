#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 10000

struct Node {
    char *name;
    int height;
    int parent;
    int lChild;
    int rChild;
};

struct Node node[maxn];
int nodeSize = 1;
int root;

void read();
int find(char *);

int main()
{
    read();

    char a[50], b[50];
    scanf("%s%s", a, b);

    int aposi = find(a), bposi = find(b);

    if (node[aposi].height == node[bposi].height) {
        int i;
        for (i = 0; aposi != bposi; i++) {
            aposi = node[aposi].parent;
            bposi = node[bposi].parent;
        }
        printf("%s %s %d\n", node[aposi].name, a, i);
        printf("%s %s %d\n", node[aposi].name, b, i);
    }
    else {
        int x = node[aposi].height - node[bposi].height;
        x > 0 ? printf("%s %s %d\n", a, b, x) : printf("%s %s %d\n", b, a, -x);
    }
}

int find(char *key)
{
    int posi = -1, i;
    if (!root) {
        posi = root = nodeSize++;
        char *p = malloc(strlen(key) + 1);
        strcpy(p, key);
        node[root].name = p;
    }
        
    else {
        for (i = root; i < nodeSize; i++) {
            if (!strcmp(key, node[i].name)) {
                posi = i;
                break;
            }
        }
    }
    return posi;
}

void insert(int posi, char *lc, char *rc)
{
    if (lc) {
        struct Node lNode = {lc, node[posi].height + 1, posi, 0, 0};
        node[posi].lChild = nodeSize;
        node[nodeSize++] = lNode;
    }
    if (rc) {
        struct Node rNode = {rc, node[posi].height + 1, posi, 0, 0};
        node[posi].rChild = nodeSize;
        node[nodeSize++] = rNode;
    }
}
void read()
{
    FILE *in = fopen("in.txt", "r");
    int n;
    fscanf(in, "%d", &n);

    char parent[50], lChild[50], rChild[50];
    int posi;

    while (n--) {
        fscanf(in, "%s%s%s", parent, lChild, rChild);
        char *lc = NULL, *rc = NULL;
        if (strcmp(lChild, "NULL")) {
            lc = malloc(strlen(lChild) + 1);
            strcpy(lc, lChild);
        }
        if (strcmp(rChild, "NULL")) {
            rc = malloc(strlen(rChild) + 1);
            strcpy(rc, rChild);
        }

        posi = find(parent);
        insert(posi, lc, rc);
    }
}