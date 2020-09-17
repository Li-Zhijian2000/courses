#include <stdio.h>
#include <stdlib.h>
#define maxn 2000
char str[maxn], res[maxn];

int main()
{
    gets(str);
    int i, lenstr = strlen(str), lenres = 0;
    for (i = 0; i < lenstr; ++i) {
        if (str[i] == '-') {
                char lastc = str[i - 1], nextc = str[i + 1];
            if (isupper(nextc) && isupper(lastc) || islower(nextc) && islower(lastc) || isdigit(nextc) && isdigit(lastc)) {
                if (lastc < nextc) {
                    char c;
                    for (c = lastc + 1; c != nextc; ++c) {
                        res[lenres++] = c;
                    }
                }
            }
            else res[lenres++] = str[i];
        }
        else res[lenres++] = str[i];
    }
    res[lenres] = 0;
    puts(res);
    return 0;
}


