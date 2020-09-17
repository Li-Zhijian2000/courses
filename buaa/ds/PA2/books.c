#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int isremove;
    char name[55];
    char author[25];
    char publisher[35];
    char date[15];
}book;

FILE *in, *out;
book books[505];

int find(book *a, char *str)
{
    return strstr(a -> name, str) || strstr(a -> author, str) || strstr(a -> publisher, str) || strstr(a -> date, str);
}
int Comp(const void *lhs, const void *rhs)
{
    book *a = (book*)lhs, *b = (book*)rhs;
    return strcmp(a -> name, b -> name);
}
void print(book *a, FILE *out)
{
    fprintf(out, "%-50s%-20s%-30s%-10s\n", a -> name, a -> author, a -> publisher, a -> date);
}
void irq(int opt, int cnt)
{
    int i, j, k;
    char findstr[55];
    book output[505];
    scanf("%s", findstr);
    for (i = 0, j = 0; i < cnt; i++) {
        if (!books[i].isremove && find(books + i, findstr)) {
            if (opt) {
                books[i].isremove = 1;
            }
                
            else {
                output[j++]= books[i];
            }
        }
    }
    if (!opt && j) {
        qsort(output, j, sizeof(output[0]), Comp);
        for (k = 0; k < j; k++) {
            print(output + k, stdout);
        }
    }
}
int main()
{
    in = fopen("books.txt", "r"), out = fopen("ordered.txt", "w");
    char input[120];
    book inputbook;
    inputbook.isremove = 0;
    int bookcnt = 0, opt, i;
    while (~fscanf(in, "%s%s%s%s", inputbook.name, inputbook.author, inputbook.publisher, inputbook.date)) {
        books[bookcnt++] = inputbook;
    }
    while (~scanf("%d", &opt)) {
        if (!opt)
            break;
        if (opt == 1) {
            scanf("%s%s%s%s", inputbook.name, inputbook.author, inputbook.publisher, inputbook.date);
            books[bookcnt++] = inputbook;
        }
        else if(opt == 2) {
            irq(0, bookcnt);//find
        }
        else if (opt == 3) {
            irq(1, bookcnt);//remove
        }
    }
    qsort(books, bookcnt, sizeof(books[0]), Comp);
    for (i = 0; i < bookcnt; i++) {
        if (!books[i].isremove)
            print(books + i, stdout);
    }
    return 0;
}
