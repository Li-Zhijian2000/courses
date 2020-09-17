#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) ((a)>(b) ? (a);(b))

char a[10000000];

int main() {
    gets(a);
    int n = strlen(a);

    int i;
    char ch;
    for (i = 0; i < n; i++) {
        if (a[i] == '-') {
            if (isdigit(a[i - 1]) && isdigit(a[i + 1]) && a[i - 1] < a[i + 1]) {
                for (ch = a[i - 1] + 1; ch < a[i + 1]; ch++) printf("%c", ch);
            } else if (islower(a[i - 1]) && islower(a[i + 1]) &&
                       a[i - 1] < a[i + 1]) {
                for (ch = a[i - 1] + 1; ch < a[i + 1]; ch++) printf("%c", ch);
            } else if (isupper(a[i - 1]) && isupper(a[i + 1]) &&
                       a[i - 1] < a[i + 1]) {
                for (ch = a[i - 1] + 1; ch < a[i + 1]; ch++) printf("%c", ch);
            } else
                printf("%c", a[i]);
        } else
            printf("%c", a[i]);
    }
    printf("\n");

    return 0;
}
