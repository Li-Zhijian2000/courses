#include "defs.h"
#include "Trie.h"
#include "print.h"

static struct Node node[NODENUM];
static int nodeNum = 1;

inline int initial()
{
    return nodeNum++;
}

//return index
void insertDic(Trie r, char key[])
{
    int len = strlen(key), i, *p;
    for (i = 0; i < len; i++) {
        p = &node[r].next[a2i(key[i])];
        if (!(*p))
            *p = nodeNum++;
        
        r = *p;
    }
    node[r].data = 1;
}

int insertMiss(Trie r, char key[])
{
    int len = strlen(key), i, *p;
    for (i = 0; i < len; i++) {
        p = &node[r].next[a2i(key[i])];
        if (!(*p))
            *p = nodeNum++;
        
        r = *p;
    }
    p = &node[r].data;
    if (!(*p))
        *p = newPrintNode();
    return *p;
}
//return member variable data if succedd to search
int search(Trie r, char key[])
{
    int len = strlen(key), i;
    for (i = 0; i < len; i++) {
        r = node[r].next[a2i(key[i])];
        if (!r)
            break;
    }

    return node[r].data;
}

void triePreorder(Trie r, char str[], int level)
{
    if (node[r].data) {
        str[level] = '\0';
        setPrintNodeWordAndOrder(node[r].data, str);
    }
    int i;
    for (i = 0; i < ALPHASIZE; i++) {
        if (node[r].next[i]) {
            str[level] = i2a(i);
            triePreorder(node[r].next[i], str, level + 1);
        }
    }
}

