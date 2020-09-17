#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 300

struct Student {
    int stuNum; // 学号
    char *name; // 姓名
    int seatNum; // 座位号
};

struct Student students[maxn]; 

int comp(const void *lhs, const void *rhs) {
    struct Student *a = (struct Student *)lhs, *b = (struct Student *)rhs;
    return (a->seatNum != b->seatNum) ? (a->seatNum - b->seatNum)
                                      : (a->stuNum - b->stuNum);
}

int comp_by_StuNum(const void *lhs, const void *rhs) {
    return ((struct Student *)lhs)->stuNum - ((struct Student *)rhs)->stuNum;
}

int main() {
    int n; scanf("%d", &n);
    FILE *in = fopen("in.txt", "r"), *out = fopen("out.txt", "w");

    char name[25];
    int stuNum, seatNum, i;
    for (i = 0; i < n; i++) {
        fscanf(in, "%d%s%d", &stuNum, name, &seatNum);
        char *p = malloc(strlen(name) + 1);
        strcpy(p, name);
        students[i] = (struct Student){ stuNum, p, seatNum };
    }

    // 按座位号排序，生成表T2
    qsort(students, n, sizeof(students[0]), comp);

    // 检查漏排
    int size = n, cur_seat = 1; // 从1号开始检查
    /**
     * TODO
     */

    // 按座位号重新排序
    qsort(students, n, sizeof(students[0]), comp);

    // 去重
    for (i = 1; i < n; i++) {
        if (students[i - 1].seatNum == students[i].seatNum)
            students[i].seatNum = cur_seat++;
    }

    // 按学号排序并输出
    qsort(students, n, sizeof(students[0]), comp_by_StuNum);
    for (i = 0; i < n; i++)
        fprintf(out, "%d %s %d\n", 
                students[i].stuNum, students[i].name, students[i].seatNum);

    return 0;
}
