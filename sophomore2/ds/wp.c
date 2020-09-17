#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct book {
    char name[50];
    char pub[30];
    char author[20];
    char number[10];
};

int main() {
    FILE *in, *out;
    int j, m;
    char s[50];
    in = fopen("books.txt", "r");
    out = fopen("ordered.txt", "w");

    struct book a[600], temp, flag;
    int i = 0, n;
    while (~fscanf(in, "%s%s%s%s", a[i].name, a[i].author, a[i].pub,
                  &a[i].number) != NULL) {
        i++;
    }
    n = i;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            if (strcmp(a[j].name, a[j + 1].name) > 0) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    while (1) {
        scanf("%d", &m);
        if (m == 0)
            break;
        else {
            if (m == 1) {
                n++;
                scanf("%s%s%s%s", flag.name, flag.author, flag.pub,
                      flag.number);
                for (i = 0; i < n; i++) {
                    if (strcmp(flag.name, a[i].name) < 0) {
                        temp = a[i];
                        a[i] = flag;
                        a[i + 1] = a[i];
                        for (j = i + 1; j < n; j++) {
                            a[j + 1] = a[j];
                        }
                    }
                }
            } else {
                if (m == 2) {
                    scanf("%s", s);
                    for (i = 0; i < n; i++) {
                        if (strstr(a[i].name, s) != NULL) {
                            printf("-50%s-20%s-30%s-10%s", a[i].name,
                                   a[i].author, a[i].name, a[i].number);
                        }
                    }
                } else if (m == 3) {
                    scanf("%s", s);
                    for (i = 0; i < n; i++) {
                        if (strstr(a[i].name, s) != NULL) {
                            for (j = i; j < n; j++) {
                                a[j] = a[j + 1];
                            }
                            n--;
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < n; i++) {
        fprintf(out, "-50%s-20%s-30%s-10%s\n", a[i].name, a[i].author, a[i].pub,
                a[i].number);
    }
}