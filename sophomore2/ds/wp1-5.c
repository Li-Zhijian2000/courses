#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void printArray(int arr[], int len) {
    int i;
    for (i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void perm(int arr[], int p, int q) {
    if (p == q) {
        printArray(arr, q + 1);
    }
    int i;
    for (i = p; i <= q; i++) {
        swap(arr, p, i);
        perm(arr, p + 1, q);
        swap(arr, p, i);
    }
}

int main() {
    int i, n = 10;
    int arr[10];
    for (i = 0; i < n; i++) arr[i] = i + 1;

    int x;
    scanf("%d", &x);
    perm(arr, 0, x - 1);

    return 0;
    /*
    if(i==1) printf("1\n");
    if(i==2){
            int arr[2] = { 1,2};
        perm(arr, 0, 1);
    }
    if(i==3){
            int arr[3] = { 1,2,3};
        perm(arr, 0, 2);
    }
    if(i==4){
            int arr[4] = { 1,2,3,4};
        perm(arr, 0, 3);
    }
    if(i==5){
            int arr[5] = { 1,2,3,4,5};
        perm(arr, 0, 4);
    }
    if(i==6){
            int arr[6] = { 1,2,3,4,5,6};
        perm(arr, 0, 5);
    }
    if(i==7){
            int arr[7] = { 1,2,3,4,5,6,7};
        perm(arr, 0, 6);
    }
    if(i==8){
            int arr[8] = { 1,2,3,4,5,6,7,8};
        perm(arr, 0, 7);
    }
    if(i==9){
            int arr[9] = { 1,2,3,4,5,6,7,8,9};
        perm(arr, 0, 8);
    }
    if(i==10){
            int arr[10] = { 1,2,3,4,5,6,7,8,9,10};
        perm(arr, 0, 9);
    }
    system("pause");
    */
}
