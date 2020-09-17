#include <stdio.h>
#include <stdlib.h>

int stack[100];
int size;

int main() {
    int op;    
    while (~scanf("%d", &op)) {
        if (op == -1) break;

        if (op == 1) {
            int x;
            scanf("%d", &x);

            if (size == 100) {
                printf("error ");
                continue;
            }
            stack[size++] = x;
        }
        if (op == 0) {
            if (!size) {
                printf("error ");
                continue;
            }
            printf("%d ", stack[--size]);
        }
    }
    putchar('\n');
    return 0;
}