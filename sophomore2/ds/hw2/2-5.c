#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 550

struct book {
    int removed;
    char name[55];
    char author[25];
    char publisher[35];
    char date[15];
} books[MAXN];

int find(struct book *a, char *str) {
    return strstr(a->name, str) || 
        strstr(a->author, str) ||
        strstr(a->publisher, str) || 
        strstr(a->date, str);
}

int cmp(const void *lhs, const void *rhs) {
    struct book *a = (struct book *)lhs, *b = (struct book *)rhs;
    return strcmp(a->name, b->name);
}

void print(struct book *a, FILE *out) {
    fprintf(out, "%-50s%-20s%-30s%-10s\n", 
        a->name, a->author, a->publisher, a->date);
}

void search(char *str, int size) {
    struct book output[MAXN];
    int i, j;
    for (i = 0, j = 0; i < size; i++) {
        if (!books[i].removed && find(books + i, str)) output[j++] = books[i];
    }
    qsort(output, j, sizeof(struct book), cmp);
    for (i = 0; i < j; i++) print(output + i, stdout);
}

void delete(char *str, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (!books[i].removed && find(books + i, str)) books[i].removed = 1;
    }
}

int main() {
    FILE *in = fopen("books.txt", "r"), *out = fopen("ordered.txt", "w");
    struct book rb;
    rb.removed = 0;
    int book_size = 0, i;
    while (~fscanf(in, "%s%s%s%s", rb.name, rb.author, rb.publisher, rb.date)) {
        books[book_size++] = rb;
    }

    int opt;
    while (~scanf("%d", &opt)) {
        if (!opt) break;

        switch (opt) {
            case 1: {
                scanf("%s%s%s%s", rb.name, rb.author, rb.publisher, rb.date);
                books[book_size++] = rb;
                break;
            }

            case 2: {
                char str[120];
                scanf("%s", str);
                search(str, book_size);
                break;
            }

            case 3: {
                char str[120];
                scanf("%s", str);
                delete(str, book_size);
            }
        }
    }

    qsort(books, book_size, sizeof(books[0]), cmp);
    for (i = 0; i < book_size; i++) {
        if (!books[i].removed) print(books + i, out);
    }
    return 0;
}