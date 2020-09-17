#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 100
struct Edit {
    int opt;
    int pos;
    int n;
    char *str;
} stack[maxn];

char buf[550];
int size;

int main() {
    int n;
    gets(buf);
    scanf("%d", &n);
    
    while (n--) {
        readPush();
    }

    while (readManuPush())
        continue;

    puts(buf);
    return 0;
}
void readPush() {
    int op, pos, n;
    char str[500];
    char *p;
    scanf("%d%d%s", &op, &pos, str);
    switch (op) {
        case 1:
            stack[size++] = (struct Edit){2, pos, strlen(str), 0};
            break;
        case 2:
            p = malloc(strlen(str) + 1);
            strcpy(p, str);
            stack[size++] = (struct Edit){1, pos, 0, p};
            break;
        default:
            break;
    }
}
int readManuPush() {
    int op, pos, n;
    char str[500];
    scanf("%d", &op);
    switch (op) {
        case 1:
            scanf("%d%s", &pos, str);
            stack[size++] = (struct Edit){2, pos, strlen(str), 0};
            insert(pos, str);
            break;
        case 2:
            scanf("%d%d", &pos, &n);
            char *p = malloc(n + 1);
            memcpy(p, buf + pos, n);
            p[n] = '\0';
            stack[size++] = (struct Edit){1, pos, 0, p};
            delete (pos, n);
            break;
        case 3:
            if (!size) break;
            switch (stack[--size].opt) {
                case 1:
                    insert(stack[size].pos, stack[size].str);
                    break;
                case 2:
                    delete (stack[size].pos, stack[size].n);
                    break;
                default:
                    break;  // don't free stack.str memory
            }
            break;
        case -1:
        default:
            return 0;
    }
    return 1;
}

void insert(int pos, char *str) {
    int len = strlen(str);
    char end[550];
    strcpy(end, buf + pos);
    strcpy(buf + pos, str);
    strcpy(buf + pos + len, end);
}
void delete (int pos, int n) {
    int i;
    char *p = buf + pos;
    if (p + n > buf + strlen(buf)) n = strlen(buf) - pos;
    while (*p = *(p + n)) p++;
}
