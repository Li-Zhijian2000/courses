#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {

    int ap = *(int *)a, ab = *(int *)b;

    return ap - ab;
}

void print(int v[], int n) {
    for (int i = 0; i < n; i++) 
        printf("%d ", v[i]);
    putchar('\n');
}

int main() {
    int n = 5;
    int v[5] = { 5, 3, 2, 1, 4 };

    print(v, n);
    qsort(v, n, sizeof(int), cmp);
    print(v, n);
}