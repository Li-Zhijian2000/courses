#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define maxn 300

struct signal {
    char c;
    int line;
} res[maxn], stack[maxn];

int main()
{
    char buf[1024];
    int i, cnt = 0, line = 0, flag = 0;
    FILE *in = fopen("example.c", "r");
    while (fgets(buf, 1024, in)) {
        int len = strlen(buf);
        line++;
        for (i = 0; i < len; i++) {
            if (flag) {
                while (i < len && (buf[i] != '*' || buf[i + 1] != '/'))
                    i++;
                if (i < len)
                    flag = 0;
            }

            switch (buf[i]) {
                case '(': case '{': case '}': case ')': res[cnt].c = buf[i]; res[cnt++].line = line; break;
                case '\'': do i++; while (buf[i] != '\''); break;
                case '"': do i++; while (buf[i] != '"'); break;
                case '/': i++;
                          if (buf[i] == '/') i = len;
                          else if (buf[i] == '*') flag = 1;
                          else i--;
                          break;
                default: break;
            }
        }
    }
    int size = 0;
    struct signal error = {0, 0};
    for (i = 0; i < cnt; i++) {
        switch (res[i].c) {
            case '(': stack[size++] = res[i]; break;
            case '{': if (stack[size - 1].c"without maching '%c' at line %d", error.c, error.line == '(') {error = stack[size - 1]; i = cnt;} stack[size++] = res[i]; break;
            case ')': if (!size || stack[--size].c != '(') {
                          error = res[i];
                          i = cnt;
                      }
                      break;
            case '}':if (!size || stack[--size].c != '{') {
                          error = res[i];
                          i = cnt;
                      }
                      break;
        }
    }
    if (error.line) printf("without maching '%c' at line %d", error.c, error.line);
    else if (size--) printf("without maching '%c' at line %d", stack[size].c, stack[size].line);
    else 
        for (i = 0; i < cnt; i++)
            putchar(res[i].c);
    puts("");
    return 0;
}
    



