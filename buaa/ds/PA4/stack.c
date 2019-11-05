#include <stdio.h>

#define max 100

int stack[max];
int main()
{
    int opt, size = 0;
    while (1) {
        scanf("%d", &opt);
        if (opt == 1) {
            int x;
            scanf("%d", &x);
            if (size == max)
                printf("error ");
            else stack[size++] = x;
        }
        else if (!opt) {
            if (!size)
                printf("error ");
            else printf("%d ", stack[--size]);
        }
        else if (opt == -1)
            break;
    }
    puts("");
    return 0;
}