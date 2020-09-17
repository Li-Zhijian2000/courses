#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxn 1000

struct Node {
    char *word;
    int count;
    int lChild;
    int rChild;
};

struct Node node[maxn];
int nodeSize = 1;
int root;

void read();
void inOrder(int);

int main()
{
    read();

    int i, posi = root;
    for (i = 0; i < 3 && posi; i++) {
        printf("%s ", node[posi].word);
        posi = node[posi].rChild;
    }
    puts("");

    inOrder(root);
    return 0;
}

static void insert(char *p)
{
    int posi;
    if (!root) {
        root = nodeSize++;
        node[root] = (struct Node){p, 1, 0, 0};
    }
    else {
        posi = root;
        while (1) {
            if (strcmp(p, node[posi].word) < 0) {
                if (node[posi].lChild)
                    posi = node[posi].lChild;
                else {
                    node[posi].lChild = nodeSize;
                    node[nodeSize++] = (struct Node){p, 1, 0, 0};
                    break;
                }
            }
            else if (strcmp(p, node[posi].word) > 0) {
                if (node[posi].rChild)
                    posi = node[posi].rChild;
                else {
                    node[posi].rChild = nodeSize;
                    node[nodeSize++] = (struct Node){p, 1, 0, 0};
                    break;
                }
            }
            else {
                node[posi].count++;
                break;
            }
        }
    }
}
void read()
{
    FILE *in = fopen("article.txt", "r");
    int j;
    char word[50], ch;

    while ((ch = getc(in)) != EOF) {
        j = 0;
        while (isalpha(ch)) {
            word[j++] = tolower(ch);
            ch = getc(in);
        }
        if (j) {
            char *p = malloc(j + 1);
            word[j] = '\0';
            strcpy(p, word);
            insert(p);
        }
    }
}

void inOrder(int posi)
{
    if (!posi)
        return;
    inOrder(node[posi].lChild);
    printf("%s %d\n", node[posi].word, node[posi].count);
    inOrder(node[posi].rChild);
}