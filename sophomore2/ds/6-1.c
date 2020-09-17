#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char word[3500][26];
typedef struct node {
    char word[26];
    struct node *link;

} LNode, *List;
void shunxu(char key[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(key, word[i]) == 0) {
            printf("1 %d", i + 1);
            break;
        } else if (strcmp(key, word[i]) < 0) {
            printf("0 %d", i + 1);
            break;
        }
    }
}
void zheban(char key[], int n) {
    int i, low = 0, mid, high = n - 1;
    for (i = 1; low <= high; i++) {
        mid = (high + low) / 2;
        if (strcmp(key, word[mid]) == 0) {
            printf("1 %d", i);
            break;
        }
        if (strcmp(key, word[mid]) > 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (low > high) printf("0 %d", i - 1);
}
void suoyin(char key[], int n) {
    int i, j, k, low = 0, high = n - 1, mid;
    for (i = 0; i < n; i++) {
        if (word[i][0] == key[0]) {
            low = i;
            for (j = i; j < n; j++) {
                if (word[j][0] != key[0]) {
                    high = j - 1;
                    break;
                }
            }
            break;
        }
    }
    if (low == 0 && high == n - 1) {
        printf("0 0\n");
        return;
    }
    for (k = 1; low <= high; k++) {
        mid = (high + low) / 2;
        // printf("%s %s %s\n", word[low], word[mid], word[high]);
        if (strcmp(key, word[mid]) == 0) {
            printf("1 %d", k);
            break;
        }
        if (strcmp(key, word[mid]) > 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (low > high) printf("0 %d", k - 1);
}
#define NHASH 3001
#define MULT 37
unsigned int hash(char *str) {
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++) h = MULT * h + *p;
    return h % NHASH;
}
void insert(List list, char temp[]) {
    List p, r;
    r = list;
    while (r->link != NULL) {
        r = r->link;
    }
    p = (List)malloc(sizeof(LNode));
    strcpy(p->word, temp);
    p->link = NULL;
    r->link = p;
}
int main() {
    FILE *In;
    In = fopen("dictionary3000.txt", "r");
    int i, n = 0, method, times = 0, t;
    char temp[30], key[30];
    int value;
    List list = NULL, p;
    List hlist[3500];
    for (i = 0; i < 3500; i++) {
        list = (List)malloc(sizeof(LNode));
        list->link = NULL;
        hlist[i] = list;
    }
    while (!feof(In)) {
        fscanf(In, "%s", temp);
        strcpy(word[n], temp);
        value = hash(temp); /*��������Ĺ�ϣֵ*/
        if (hlist[value]->link == NULL) {
            p = hlist[value];
            strcpy(p->word, temp);
            p->link = NULL;
        } else if (hlist[value]->link != NULL)
            insert(hlist[value], temp);
        n++;
    }
    scanf("%s%d", key, &method);
    if (method == 1)
        shunxu(key, n);
    else if (method == 2)
        zheban(key, n);
    else if (method == 3)
        suoyin(key, n);
    else if (method == 4) {
        value = hash(key);
        p = hlist[value];
        times++;
        while (strcmp(p->word, key) > 0 && p->link != NULL) {
            p = p->link;
            times++;
        }
        if (strcmp(p->word, key) == 0) {
            printf("1 %d\n", times);
        } else {
            printf("0 %d\n", times + 1);
        }
    }
    fclose(In);
    return 0;
}
