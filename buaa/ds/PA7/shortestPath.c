#include <stdio.h>
#include <stdlib.h>                          
#include <string.h>
#include <assert.h>
#define MAXINT 0x7f7f7f7f
#define maxv 300
#define maxe 1000

int verMatrix[maxv][maxv];
int priority[maxv], parent[maxv], isvisit[maxv], subwayLine[maxv], transit[maxv];
int v;

char *stationCode[maxv];

void primPrioUpdater(int pa, int ch)
{
    if (!isvisit[ch])
        if (priority[ch] > priority[pa] + 1) {
            priority[ch] = priority[pa] + 1;
            parent[ch] = pa;
        }
}
void pfs(int ver, int terminal, void prioUpdater(int, int))
{   
    memset(priority, 0x7f, sizeof(priority));

    priority[ver] = 0;
    isvisit[ver] = 1;
    parent[ver] = 0;

    int i, j, k, shortest;
    for (i = 1; i < v; i++) {
        for (j = 0; j < v; j++)
            if (verMatrix[ver][j])
                prioUpdater(ver, j);

        for (shortest = MAXINT, j = 0; j < v; j++)
            if (!isvisit[j])
                if (shortest > priority[j]) {
                    shortest = priority[j];
                    ver = j;
                }

        isvisit[ver] = 1;
        if (ver == terminal)
            break;
    }
}

int insert(char *s)
{
    int i;
    for (i = 0; i < v; i++)
        if (!strcmp(s, stationCode[i]))
            break;
    
    if (i == v) {
        char *p = malloc(strlen(s) + 1);
        strcpy(p, s);
        stationCode[v++] = p;
        return v - 1;
    }
    return i;
}
int search(char *s)
{
    int i;
    for (i = 0; i < v; i++)
        if (!strcmp(s, stationCode[i]))
            break;

    assert(i != v);
    return i;
}
void print(int ver, int origin, int line, int count)
{ 
    if (ver == origin) {
        printf("%s-%d(%d)-", stationCode[ver], line, count);
        return;
    }
    if (transit[ver] && verMatrix[ver][parent[ver]] != line) {
        print(parent[ver], origin, verMatrix[ver][parent[ver]], 1);
        printf("%s-%d(%d)-", stationCode[ver], line, count);
    }
    else
        print(parent[ver], origin, line, count + 1);
}
int main()
{   
    FILE *in = fopen("bgstations.txt", "r");
    int lineNum, subway, stationNum, flag, precStation, i, j;
    char stationName[20];
    fscanf(in, "%d", &lineNum);
    for (i = 0; i < lineNum; i++) {
        fscanf(in, "%d%d", &subway, &stationNum);
        for (j = 0, precStation = -1; j < stationNum; j++) {
            fscanf(in, "%s%d", stationName, &flag);
            int verCode = insert(stationName);
            subwayLine[verCode] = subway;
            transit[verCode] = flag;
            if (precStation > 0) {
                verMatrix[precStation][verCode] = verMatrix[verCode][precStation] = 
                (!flag ? subway : subwayLine[verCode]);
            }
            precStation = verCode;
        }
    }

    char origin[20], terminal[20];
    scanf("%s%s", origin, terminal);
    int originCode = search(origin), terminalCode = search(terminal);
    pfs(originCode, terminalCode, primPrioUpdater);

    print(terminalCode, originCode, verMatrix[terminalCode][parent[terminalCode]], 0);
    puts(terminal);
    return 0;
}