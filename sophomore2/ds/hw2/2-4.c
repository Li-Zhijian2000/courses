#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 120

struct person {
    char name[25];
    char phone[25];
    int idx;
} persons[MAXN];

int cmp(const void *a, const void *b) {
    struct person *p1 = (struct person *)a, *p2 = (struct person *)b;
    return strcmp(p1->name, p2->name) ? strcmp(p1->name, p2->name)
                                      : p1->idx - p2->idx;
}
int main() {
    int n;
    scanf("%d", &n);

    int i;
    for (i = 0; i < n; i++) {
        scanf("%s%s", persons[i].name, persons[i].phone);
        persons[i].idx = i;
    }
    qsort(persons, n, sizeof(struct person), cmp);

    int cnt = 1;
    for (i = 0; i < n; i++) {
        if (i == n - 1 || strcmp(persons[i].name, persons[i + 1].name)) {
            int j;
            for (j = 0; j < cnt; j++) {
                int k = i - cnt + 1 + j;
                printf("%s", persons[k].name);
                if (j != 0) printf("_%d", j);
                printf(" %s\n", persons[k].phone);
            }
            cnt = 1;
        } else if (!strcmp(persons[i].phone, persons[i + 1].phone))
            continue;
        else
            cnt++;
    }
}
