#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int cnt;
    long long num[14];
    char name[25];
}phone;
phone phones[105];

int Comp(const void *lhs, const void *rhs)
{
    phone *a = (phone*)lhs, *b = (phone*)rhs;
    return strcmp(a -> name, b -> name) > 0;
}
int main()
{
    int n, phonecnt = 0, i, j, k;
    scanf("%d", &n);
    while (n--) {
        char inputstr[25];
        long long inputnum;
        scanf("%s%lld", inputstr, &inputnum);
        for (i = 0; i < phonecnt; i++) {
            if (!strcmp(inputstr, phones[i].name)) {
                for (j = 0; j < phones[i].cnt; j++) {
                    if (inputnum == phones[i].num[j])
                        break;
                }
                if (j == phones[i].cnt) {
                    phones[i].num[phones[i].cnt++] = inputnum;
                }
                break;
            }
        }
        if (i == phonecnt) {
            strcpy(phones[i].name, inputstr);
            phones[i].num[phones[i].cnt++] = inputnum;
            phonecnt++;
        }
        // printf("%d %s %lld\n", phonecnt, inputstr, inputnum);
    }
    qsort(phones, phonecnt, sizeof(phone), Comp);
    for (i = 0; i < phonecnt; i++) {
        for (j = 0; j < phones[i].cnt; j++) {
            printf("%s", phones[i].name);
            if (j)
                printf("_%d", j);
            printf(" %lld\n", phones[i].num[j]);
        }
    }
    return 0;
}
