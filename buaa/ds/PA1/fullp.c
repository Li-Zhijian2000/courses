#include <stdio.h>

int array[12];

void print(int);
void fullp(int);
void swap(int, int);
void reverse(int, int);
int main()
{
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        array[i] = i + 1;
    }
    print(n);
    fullp(n);
    return 0;
}

void fullp(int n)
{
    while (1) {
        int i, j;
        for (i = n - 2; i >= 0; --i) {
            if (array[i] < array[i+1])
                break;
        }
        if (i == -1)
            break;
        for (j = i + 1; array[j] > array[i] && j < n; ++j)
            ;
        --j;
        swap(i, j);
        reverse(i + 1, n - 1);
        print(n);
    }
}

void swap(int i, int j)
{
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void reverse(int i, int j)
{
    while(i < j) {
        swap(i++, j--);
    }
}
void print(int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d ", array[i]);
    putchar('\n');
}
