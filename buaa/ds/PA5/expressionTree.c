#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define maxn 205

int level[128], num[maxn], numSize, optSize;
char opt[maxn];

struct OptData {
    int optData;
    int isData;
};

struct Node {
    struct OptData value;
    int lChild;
    int rChild;
};

struct Node node[maxn];
int nodeSize = 1;

int nodeStack[maxn];
int stackSize;

void levelInit();
void calc(char);
void printAns();

int main()
{
    levelInit();
    opt[optSize++] = '\0';

    char line[1000];
    gets(line);

    int len = strlen(line), number, i = 0;
    while (i < len) {
        number = 0;
        while (isdigit(line[i])) {
            number = number * 10 + line[i] - '0';
            i++;
        }
        if (isdigit(line[i - 1])) {
            num[numSize++] = number;
            node[nodeSize] = (struct Node){(struct OptData){number, 1}};
            nodeStack[stackSize++] = nodeSize++;
        }

        switch(line[i]) {
            case '(':
                opt[optSize++] = line[i];
                break;
            case ')':
                while (opt[--optSize] != '(')
                    calc(opt[optSize]);
                break;
            case '+': case '-': case '*': case '/': case '=': 
                while (level[opt[optSize - 1]] >= level[line[i]])
                    calc(opt[--optSize]);
                if (line[i] == '=') {
                    printAns();
                    return 0;
                }
                else opt[optSize++] = line[i];
                break;
            default: break;
        }
        i++;
    }
}

void levelInit()
{
    level['\0'] = -1;
    level['+'] = level['-'] = 1;
    level['*'] = level['/'] = 2;
}
void calc(char ch)
{
    // putchar(ch);
    int b = num[--numSize], a = num[--numSize];
    int rc = nodeStack[--stackSize], lc = nodeStack[--stackSize];
    node[nodeSize] = (struct Node){(struct OptData){ch, 0}, lc, rc};
    nodeStack[stackSize++] = nodeSize++;
    if (ch == '*') num[numSize++] = a * b;
    if (ch == '/') num[numSize++] = a / b;
    if (ch == '+') num[numSize++] = a + b;
    if (ch == '-') num[numSize++] = a - b;
    // printf("%d\n", num[numSize-1]);
}
void inOrder(int posi)
{
    if (!posi)
        return;
    inOrder(node[posi].lChild);
    inOrder(node[posi].rChild);
    char *buf = (node[posi].value.isData) ? "%d " : "%c ";
    printf(buf, node[posi].value.optData);
}
void printNode(int posi)
{
    char *buf = (node[posi].value.isData) ? "%d " : "%c ";
    printf(buf, node[posi].value.optData);
}
void printAns()
{
    // inOrder(nodeStack[stackSize - 1]);
    // puts("");
    int posi = nodeStack[stackSize - 1], i;
    int tmp[3] = {posi, node[posi].lChild, node[posi].rChild};
    for (i = 0; i < 3 && tmp[i]; i++)
        printNode(tmp[i]);
    printf("\n%d\n", num[0]);
}