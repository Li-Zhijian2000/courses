#include <stdio.h>
#include <string.h>
#define maxn 105
char opt[maxn], input[maxn * 2];
int deque[maxn];

int main()
{
    gets(input);
    int i, lens = strlen(input), num, optcnt = 0, size = 1, lastopt = '+', res;
    for (i = 0, num = 0; i < lens; ++i) {
        char c = input[i];
        if (isspace(c)) {
            continue;
        }
        else if (isdigit(c)) {
            num = num * 10 + c - '0';
        }
        else {
            if (lastopt == '*' || lastopt == '/') {
                int lastnum = deque[--size];
                deque[size++] = lastopt == '*' ? lastnum * num : lastnum / num;
            }
            else {
                opt[optcnt++] = lastopt;
                deque[size++] = num;
            }
            lastopt = c;
            num = 0;
        }
    }
    for (i = 1, res = deque[0]; i < size; ++i) {
        res = opt[i - 1] == '+' ? res + deque[i] : res - deque[i];
    }
    printf("%d\n", res);
    return 0;
}
