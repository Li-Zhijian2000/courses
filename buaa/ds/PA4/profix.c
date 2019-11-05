#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define maxn 200

int level[128], nums[maxn], numsize, optsize;
char opt[maxn];

void calc(char ch)
{
    
    int b = nums[--numsize], a = nums[--numsize];
    if (ch == '*') nums[numsize++] = a * b;
    if (ch == '/') nums[numsize++] = a / b;
    if (ch == '%') nums[numsize++] = a % b;
    if (ch == '+') nums[numsize++] = a + b;
    if (ch == '-') nums[numsize++] = a - b;
}
int main()
{
    level['\0'] = -1;
    level['+'] = level['-'] = 1;
    level['*'] = level['/'] = level['%'] = 2;
    opt[optsize++] = '\0';
    char buf[1024];
    gets(buf);

    int len = strlen(buf), num = 0, i;
    for (i = 0; i < len; i++) {
        while (isdigit(buf[i])) {
            num = num * 10 + buf[i] - '0';
            i++;
            // printf("%d\n", num);
        }
        if (isdigit(buf[i - 1]))
            nums[numsize++] = num;
        num = 0;

        if (isspace(buf[i]))
            continue;

        switch (buf[i]) {
            case '(': opt[optsize++] = buf[i]; break;
            case ')': while (opt[--optsize] != '(') calc(opt[optsize]); break;
            default: while (level[opt[optsize - 1]] >= level[buf[i]]) calc(opt[--optsize]);
                     if (buf[i] == '=') {
                        printf("%d\n", nums[0]);
                        return 0;
                     }
                     else opt[optsize++] = buf[i];
                     break;
        }
    }

    #if 0
    while (scanf("%d", &num) {
        printf("%d %c\n", num, ch);
        if ( {
            num += num * 10 + ch - '0';
            continue;
        }
            
        if (isspace(ch)) {
            nums[cnt++] = 0;
            num = 0;
            continue;
        }
        
        if (ch == '(')
            stack[size++] = ch;
        else if (ch == ')') {
            while ((ch = stack[--size]) != '(')
                res += opt(ch,cnt);
                cnt -= 2;
        }
        else if (ch == '=') {
            printf("%d\n", res);
            break;
        }
        else {
            while (level[stack[size - 1]] >= level[ch]) {
                res += opt(stack[--size], cnt);
                cnt -= 2;
            }
            stack[size++] = ch;
        }
        nums[cnt++] = num;
        num = 0;
    }
    return 0;
    #endif
}