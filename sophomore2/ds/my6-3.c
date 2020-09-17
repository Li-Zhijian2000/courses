#include <stdio.h>
#include <stdlib.h>
#define maxn 110

int num[maxn], count;

void selectSort(int);
void bubbleSort(int);
void heapSort(int);
void mSort(int, int);
void quickSort(int, int);
int main() {
    int n, opt, i;
    scanf("%d%d", &n, &opt);
    for (i = 0; i < n; i++) scanf("%d", num + i);

    switch (opt) {
        case 1:
            selectSort(n);
            break;
        case 2:
            bubbleSort(n);
            break;
        case 3:
            heapSort(n);
            break;
        case 4:
            mSort(0, n - 1);
            break;
        case 5:
            quickSort(0, n - 1);
            break;
        default:
            break;
    }
    for (i = 0; i < n; i++) printf("%d ", num[i]);
    putchar('\n');
    printf("%d\n", count);
    return 0;
}
static void swap(int i, int j) {
    int tmp = num[i];
    num[i] = num[j];
    num[j] = tmp;
}
void selectSort(int n) {
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (++count && num[j] < num[min]) min = j;
        }
        if (min != i) swap(min, i);
    }
}
void bubbleSort(int n) {
    int i, j, flag = 1;
    int temp;
    for (i = n - 1; i > 0 && flag == 1; i--) {
        flag = 0;
        for (j = 0; j < i; j++)
            if (++count && num[j] > num[j + 1]) {
                temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp; /* 交换两个元素的位置 */
                flag = 1;          /* 标志flag置1 */
            }
    }
}
void percolateDown(int i, int n) {
    int j, temp;
    temp = num[i];
    j = 2 * i + 1;
    while (j < n) {
        if (j < n - 1 && num[j] < num[j + 1]) j++;
        if (++count && temp >= num[j]) break;
        num[(j - 1) / 2] = num[j];
        j = 2 * j + 1;
    }
    num[(j - 1) / 2] = temp;
}
void heapSort(int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--) percolateDown(i, n);
    for (i = n - 1; i >= 1; i--) {
        swap(0, i);
        percolateDown(0, i);
    }
}
void merge(int left, int leftend, int rightend) {
    int *tmp = malloc(rightend - left + 1);
    int i = left, j = leftend + 1, q = 0;
    while (i <= leftend && j <= rightend) {
        if (++count && num[i] <= num[j])
            tmp[q++] = num[i++];
        else
            tmp[q++] = num[j++];
    }
    while (i <= leftend) tmp[q++] = num[i++];
    while (j <= rightend) tmp[q++] = num[j++];
    for (i = left; i <= rightend; i++) num[i] = tmp[i - left];
}
void mSort(int left, int right) {
    int center;
    if (left < right) {
        center = (left + right) / 2;
        mSort(left, center);
        mSort(center + 1, right);
        merge(left, center, right);
    }
}
void quickSort(int left, int right) {
    int i, last;
    if (left < right) {
        last = left;
        for (i = left + 1; i <= right; i++)
            if (++count && num[i] < num[left]) swap(++last, i);
        swap(left, last);
        quickSort(left, last - 1);
        quickSort(last + 1, right);
    }
}
