#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char name[55];
    char writ[25];
    char publ[35];
    int date;
} book;
book bk[550];
int bn = 0;

int cmp(const void *p1, const void *p2);
void insert(book *p);
void structcpy(book *p1, book *p2);
void dele(int loc);

int main() {
    int i = 0, j = 0;
    char c;
    FILE *fp1 = fopen("books.txt", "r");
    FILE *fp2 = fopen("ordered.txt", "w");

    while (~ fscanf(fp1, "%s%s%s%d", bk[i].name, bk[i].writ, bk[i].publ, &bk[i].date) {
        i++;
    }
    bn = i;                            
    int opt;
    do {
        scanf("%d", &opt);  //�ӿ���̨�������
        if (opt == 1) {
            book add;
            scanf("%s%s%s%d", add.name, add.writ, add.publ, &add.date);
            bk[bn++] = add;
        } else if (opt == 2) {
            char tag[55];
            scanf("%s", tag);
            book output[550];
            int j = 0;
            for (i = 0; i < bn; i++) {
                if (strstr(bk[i].name, tag) != NULL) output[j++] = bk[i];

                qsort(output, j, sizeof(book), cmp);

                for (i = 0; i < j; i++)
                    printf("%-50s%-20s%-30s%-10d\n", bk[i].name, bk[i].writ,
                           bk[i].publ, bk[i].date);
            }
        } else if (opt == 3) {
            char tag[55];
            int sign[55] = {0};
            scanf("%s", tag);
            for (i = 0; i < bn; i++) {
                if (strstr(bk[i].name, tag) != NULL) sign[i] = 1;
            }
            for (j = 0; j < 55; j++) {
                if (sign[j] == 1) dele(j);
            }
        }
    } while (opt != 0);
    for (i = 0; i < bn; i++) {
        fprintf(fp2, "%-50s%-20s%-30s%-10d\n", bk[i].name, bk[i].writ,
                bk[i].publ, bk[i].date);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
int cmp(const void *p1, const void *p2) {
    book *b1 = (book *)p1, *b2 = (book *)p2;
    return strcmp(b1->name, b2->name);
}
void structcpy(book *p1, book *p2) {
    strcpy(p1->name, p2->name);
    strcpy(p1->writ, p2->writ);
    strcpy(p1->publ, p2->publ);
    p1->date = p2->date;
}
void dele(int loc) {
    int i;
    if (loc < bn - 1) {
        for (i = loc; i < bn - 1; i++)  //Ŀ��λ�ÿ�ʼ��ǰ����,ǰ��Ⱥ���
            structcpy(&bk[i], &bk[i + 1]);
    }
    bn--;
}
void insert(book *p) {
    int i, loc = 0;
    if (strcmp(p->name, bk[0].name) <
        0)  //�ҵ�����Ԫ��Ӧ�ڵ�λ��
        loc = 0;
    else if (strcmp(p->name, bk[bn - 1].name) > 0)
        loc = bn;
    else {
        for (i = 0; i < bn - 1; i++) {
            if (strcmp(p->name, bk[i].name) > 0 &&
                strcmp(bk[i + 1].name, p->name) > 0) {
                loc = i + 1;
                break;
            }
        }
    }  //Ȼ���ƶ�����Ԫ�أ��������Ԫ��
    if (loc == bn)
        structcpy(&bk[loc], p);
    else {
        for (i = bn - 1; i >= loc; i--)  //�����һ����ǰ�������ǰ��
            structcpy(&bk[i + 1], &bk[i]);
        structcpy(&bk[loc], p);
    }
    bn++;
}