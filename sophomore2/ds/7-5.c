#include <stdio.h>
#include <string.h>

typedef struct station {
    char name[100];
    int change;
} sta;

typedef struct edge {
    int weight;
    int eno;
} edg;

sta All[500];
edg Alle[500][500];
int dis[500];
char label[500];
int spath[500];
int path[500];
int N;
FILE *in;

int find(char string[]) {
    int n1;
    for (n1 = 0; n1 < 500 && *(All[n1].name) != '\0'; n1++) {
        if (strcmp(string, All[n1].name) == 0) return n1;
    }
    return -1;
}

int smallest(int a[]) {
    int n1, n2 = 0, min = 10000000;
    for (n1 = 0; n1 < N; n1++) {
        if (label[n1] != 1) continue;
        if (dis[n1] < min) {
            n2 = n1;
            min = dis[n1];
        }
    }
    return n2;
}

void read() {
    in = fopen("bgstations.txt", "r");
    int linenum;
    fscanf(in, "%d", &linenum);
    int n1, n2, n3, n4;
    int Eno, Num;
    char string[100];
    int Change;
    for (n1 = 0; n1 < linenum; n1++) {
        fscanf(in, "%d%d", &Eno, &Num);
        for (n2 = 0; n2 < Num; n2++) {
            fscanf(in, "%s%d", string, &Change);
            if (Change == 0 || find(string) == -1) {
                n4 = N;
                strcpy(All[N].name, string);
                All[N++].change = Change;
            } else {
                n4 = find(string);
            }
            if (n2 == 0) {
                n3 = n4;
                continue;
            }
            Alle[n3][n4].eno = Eno;
            Alle[n4][n3].eno = Eno;
            Alle[n3][n4].weight = 1;
            Alle[n4][n3].weight = 1;
            // printf("%d: %d:%s-%d:%s\n",Eno,n3,All[n3].name,n4,All[n4].name);
            n3 = n4;
        }
    }
    fclose(in);
}

int main() {
    int n1, n2;
    for (n1 = 0; n1 < 500; n1++) {
        dis[n1] = 10000000;
        label[n1] = 1;
        for (n2 = 0; n2 < 500; n2++) {
            Alle[n1][n2].weight = 10000000;
            Alle[n1][n2].eno = 0;
        }
    }
    read();
    char start[100];
    char des[100];
    scanf("%s%s", start, des);
    int Sta = find(start);
    int Des = find(des);
    for (n1 = 0; n1 < 500; n1++) spath[n1] = Sta;
    dis[Sta] = 0;

    // Dijkstra�㷨
    int p = Sta;
    for (n1 = 0; n1 < N - 1; n1++) {
        for (n2 = 0; n2 < N; n2++)  // pΪĿǰվ�㣬��ѭ�����ڼ����վ�㸽��վ���롣
        {
            if (label[n2] != 1) continue;
            if (dis[n2] > dis[p] + Alle[p][n2].weight) {
                dis[n2] = dis[p] + Alle[p][n2].weight;
                // printf("%s %d\n", All[n2].name, dis[n2]);
                if (!strcmp(All[n2].name, "复兴门") || dis[n2] == 1)
                    printf("%s %d\n", All[n2].name, dis[n2]);
                    
                spath[n2] = p;
                // printf("%s-%s-%d:%d\n",All[n2].name,All[p].name,Alle[p][n2].eno,dis[n2]);
            }
        }
        label[p] = 2;
        p = smallest(dis);
        // printf("%d:%s\n",p,All[p].name);
    }

    for (n1 = Des, n2 = 0; n1 != Sta;) {
        path[n2++] = n1;
        // printf("%s-",All[n1].name);
        n1 = spath[n1];
    }
    path[n2] = Sta;
    printf("n2: %d\n", n2);
    int time = 0;
    p = Sta;
    printf("%s", All[p].name);
    while (--n2) {
        if (Alle[p][path[n2]].eno == Alle[path[n2]][path[n2 - 1]].eno) {
            time++;
        } else {
            time++;
            printf("-%d(%d)-%s", Alle[p][path[n2]].eno, time,
                   All[path[n2]].name);
            time = 0;
        }
        p = path[n2];
    }
    printf("-%d(%d)-%s\n", Alle[p][path[n2]].eno, time + 1, All[path[n2]].name);
    return 0;
}
