#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define maxChar 140
#define maxn 14000
struct CharInfo {
    int count;
    char *code;
};
struct CharInfo charInfo[maxChar];

struct HuffNode {
    char ch;
    int weight;
    int lChild;
    int rChild;
};
struct HuffNode huffNode[maxn * 2];
int huffNodeSize = 1;

int huffForest[maxn], nextForest[maxn];
int huffForestSize = 1;
int headNode = 0;

char book[100000];
char encode[100000 * 8];
int len;

int comp(const void *a, const void *b)
{
    int lhs = *(int *)a, rhs = *(int *)b;
    return (huffNode[lhs].weight != huffNode[rhs].weight) ? (huffNode[lhs].weight - huffNode[rhs].weight) :
                                                            (huffNode[lhs].ch - huffNode[rhs].ch);
}

void preOrder(int, int, char *);
void insert(int);
int getMin();

int main()
{
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    char ch;
    charInfo[0] = (struct CharInfo){1, NULL};
    while ((ch = fgetc(in)) != EOF) 
        if (ch != '\n') {
            book[len++] = ch;
            charInfo[ch].count++;
        }
    assert(len);
    int i;
    for (i = 0; i < maxChar; i++)
        if (charInfo[i].count) {
            huffForest[huffForestSize++] = huffNodeSize;
            huffNode[huffNodeSize++] = (struct HuffNode){i, charInfo[i].count}; 
        }
                   
    qsort(huffForest, huffForestSize, sizeof(huffForest[0]), comp);
    for (i = 0; i < huffForestSize - 1; i++)
        nextForest[i] = i + 1;
    
    int total = huffForestSize - 2;
    for (i = 0; i < total; i++) {
        int a = getMin(), b = getMin();
        huffNode[huffNodeSize] = (struct HuffNode){-1, huffNode[huffForest[a]].weight + huffNode[huffForest[b]].weight, huffForest[a], huffForest[b]};
        insert(huffNodeSize);
        huffNodeSize++;
    }

    char code[100];
    preOrder(huffNodeSize - 1, 0, code);
    
    for (i = 0; i <= len; i++) {
        if (charInfo[book[i]].code)
            strcat(encode, charInfo[book[i]].code);
    }
    len = strlen(encode);
    if (len % 8) {
        int x = 8 - len + len / 8 * 8;
        for (i = 0; i < x; i++)
            encode[i + len] = '0';
        len += x;
    }
    int j, num;
    assert(len >= 0);
    for (i = 0; i < len; i += 8) {
        j = num = 0;
        while (j < 8) {
            num = (num << 1) + encode[i + j] - '0';
            j++;
        }
        printf("%x", num);
        fprintf(out, "%x", num);
    }
    puts("");
    return 0;
}

int getMin()
{
    int a = nextForest[headNode];
    nextForest[headNode] = nextForest[nextForest[headNode]];
    return a;
}
void insert(int key)
{
    int posi = headNode;
    while (nextForest[posi] && huffNode[huffForest[nextForest[posi]]].weight <= huffNode[key].weight)
        posi = nextForest[posi];
    huffForest[huffForestSize] = key;
    nextForest[huffForestSize] = nextForest[posi];
    nextForest[posi] = huffForestSize++;
}
void preOrder(int posi, int level, char code[])
{   
    if (huffNode[posi].ch >= 0) {
        code[level] = '\0';
        // printf("%c %s\n", huffNode[posi].ch, code);
        char *p = malloc(level + 1);
        strcpy(p, code);
        charInfo[huffNode[posi].ch].code = p;
        return;
    }
    if (huffNode[posi].lChild) {
        code[level] = '0';
        preOrder(huffNode[posi].lChild, level + 1, code);
    }
    if (huffNode[posi].rChild) {
        code[level] = '1';
        preOrder(huffNode[posi].rChild, level + 1, code);
    }
}         
