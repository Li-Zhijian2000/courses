#include <stdio.h>
#include <stdlib.h>
int a[120];
int count = 0;
void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int selectsort(int a[], int n) {
    int i, mark, j;
    for (i = 0; i < n; i++) {
        mark = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[mark]) {
                mark = j;
            }
            count++;
        }
        if (mark != i) {
            swap(&a[i], &a[mark]);
        }
    }
    return count;
}
int bubblesort(int a[], int n) {
    int i, j, flag = 1;  // flag=1��Ԫ�ؽ���
    for (i = n - 1; i > 0 && flag == 1; i--) {
        flag = 0;
        for (j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                flag = 1;
            }
            count++;
        }
    }
    return count;
}
void adjust(int a[], int i, int n) {
    int j, temp;
    j = 2 * i + 1;
    temp = a[i];
    while (j < n) {
        if (j < n - 1 && a[j] < a[j + 1]) j++;
        int h = temp - a[j];
        count++;
        if (h >= 0) {
            break;
        }
        a[(j - 1) / 2] = a[j];
        j = 2 * j + 1;
    }
    a[(j - 1) / 2] = temp;
}
void heapsort(int a[], int n) {
    int i = 0;
    for (i = n / 2; i >= 0; i--) adjust(a, i, n);
    for (i = n - 1; i >= 0; i--) {
        swap(&a[0], &a[i]);
        adjust(a, 0, i);
    }
}
void quickSort(int a[], int left, int right) {
    int i, last;
    if (left < right) {
        last = left;
        for (i = left + 1; i <= right; i++) {
            if (a[i] < a[left]) {
                last++;
                swap(&a[last], &a[i]);
            }
            count++;
        }
        swap(&a[left], &a[last]);
        quickSort(a, left, last - 1);
        quickSort(a, last + 1, right);
    }
}
int main() {
    int n, op;
    int f;
    scanf("%d%d", &n, &op);
    int i;
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    if (op == 1) {
        f = selectsort(a, n);
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n%d", f);
    }
    if (op == 2) {
        f = bubblesort(a, n);
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n%d", f);
    }
    if (op == 3) {
        heapsort(a, n);
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n%d", count);
    }
    if (op == 5) {
        quickSort(a, 0, n - 1);
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n%d", count);
    }
    return 0;
}