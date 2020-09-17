#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 300

struct Student {
    int stuNum;
    char *name;
    int seatNum;
};
struct Student student[maxn];

int studentSize;

int isSet[maxn];

int comp(const void *lhs, const void *rhs)
{
    struct Student *a = (struct Student *)lhs, *b = (struct Student *)rhs;
    return (a->seatNum != b->seatNum) ? (a->seatNum - b->seatNum) : (a->stuNum - b->stuNum);
}
int compStuNum(const void *lhs, const void *rhs)
{
    return ((struct Student *)lhs)->stuNum - ((struct Student *)rhs)->stuNum;
}

int main()
{
    int n, i;
    scanf("%d", &n);
    
    FILE *in = fopen("in.txt", "r"), *out = fopen("out.txt", "w");
    char name[25];
    int stuNum, seatNum;
    for (i = 0; i < n; i++) {
        fscanf(in, "%d%s%d", &stuNum, name, &seatNum);
        char *p = malloc(strlen(name) + 1);
        strcpy(p, name);
        student[i] = (struct Student){stuNum, p, seatNum};
    }
    qsort(student, n, sizeof(student[0]), comp);

    int j = 1, size = n;
    i = 0;
    while (i < n) {
        if(isSet[student[i].seatNum])
            i++;
        else if (j == student[i].seatNum) {
            isSet[j] = 1;
            i++;
            j++;
        }
        else if (j < student[i].seatNum) {
            student[--size].seatNum = j;
            isSet[j] = 1;
            j++;
        } 
        
    }
    printf("%d\n", j);
    qsort(student, n, sizeof(student[0]), comp);
    for (i = 0; i < n; i++)
        printf("%d %s %d\n", student[i].stuNum, student[i].name, student[i].seatNum);
    for (i = 1; i < n; i++) {
        if (student[i - 1].seatNum == student[i].seatNum)
            student[i].seatNum = j++;
    }
    qsort(student, n, sizeof(student[0]), compStuNum);
    for (i = 0; i < n; i++)
        fprintf(out, "%d %s %d\n", student[i].stuNum, student[i].name, student[i].seatNum);
    return 0;
}
