#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define maxn 105
char opt[maxn], line[1024];
int stack[maxn];

// 先计算乘除，再计算加减，达到实现优先级的目的
int main() {
    fgets(line, 1024, stdin);
    int i, lens = strlen(line), num, optcnt = 0, size = 1, lastopt = '+', res;
    for (i = 0, num = 0; i < lens; i++) {
        char c = line[i];
        if (isspace(c)) {
            continue;
        }
        if (isdigit(c)) {
            num = num * 10 + c - '0';
            continue;
        }
        if (lastopt == '*' || lastopt == '/') {
            int lastnum = stack[--size];
            stack[size++] = lastopt == '*' ? lastnum * num : lastnum / num;
        } else {
            opt[optcnt++] = lastopt;
            stack[size++] = num;
        }
        lastopt = c;
        num = 0;
    }
    for (i = 1, res = stack[0]; i < size; ++i) {
        res = opt[i - 1] == '+' ? res + stack[i] : res - stack[i];
    }
    printf("%d\n", res);
    return 0;
}
