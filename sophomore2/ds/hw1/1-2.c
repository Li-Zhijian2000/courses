#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define maxn 2000
char str[maxn], res[maxn];

int main() {
    gets(str);
    int i, len = strlen(str), size = 0;
    for (i = 0; i < len; i++) {
        if (str[i] == '-') {
            char lastc = str[i - 1], nextc = str[i + 1];
            if (isupper(nextc) && isupper(lastc) ||
                islower(nextc) && islower(lastc) ||
                isdigit(nextc) && isdigit(lastc)) {
                if (lastc < nextc) {
                    char c;
                    for (c = lastc + 1; c != nextc; ++c) {
                        res[size++] = c;
                    }
                }
            } else
                res[size++] = str[i];
        } else
            res[size++] = str[i];
    }
    puts(res);
    return 0;
}
