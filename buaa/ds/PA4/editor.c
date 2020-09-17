#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 100
struct edit {
    int opt;
    int pos;
    int n;
    char *str;
}stack[maxn];

char buf[550];
int size;

void readPush();
int readManuPush();
void insert(int, char *);
void delete(int, int);

int main()
{   
    #if 0
    strcpy(buf, "test data");
    delete(6, 8);
    delete(0, 1);
    insert(0, "begin");
    insert(strlen(buf), "end");
    #endif
    int n;
    gets(buf);
    scanf("%d", &n);
    while (n--) {
        readPush();
    }

    while (readManuPush());

    puts(buf);
    return 0;
}
void readPush()
{
    int op, pos, n;
    char str[500];
    char *p;
    scanf("%d%d%s", &op, &pos, str);
    switch (op) {
        case 1: stack[size++] = (struct edit){2, pos, strlen(str), 0}; break;
        case 2: p = malloc(strlen(str) + 1); strcpy(p, str); stack[size++] = (struct edit){1, pos, 0, p}; break;
        default: break;
    }
}
int readManuPush()
{
    int op, pos, n;
    char str[500];
    scanf("%d", &op);
    switch (op) {
        case 1: scanf("%d%s", &pos, str);
                stack[size++] = (struct edit){2, pos, strlen(str), 0};
                insert(pos, str);
                break;
        case 2: scanf("%d%d", &pos, &n);
                char *p = malloc(n + 1);
                memcpy(p, buf + pos, n);
                p[n] = '\0';
                stack[size++] = (struct edit){1, pos, 0, p};
                delete(pos, n);
                break;
        case 3: if (!size) break;
                switch (stack[--size].opt) {
                    case 1: insert(stack[size].pos, stack[size].str); break;
                    case 2: delete(stack[size].pos, stack[size].n); break;
                    default : break;//don't free stack.str memory
                }
                break;
        case -1: default: return 0;
    }
    return 1;
}

void insert(int pos, char *str)
{
    // puts(buf);
    int len = strlen(str);
    char end[550];
    strcpy(end, buf + pos);
    strcpy(buf + pos, str);
    strcpy(buf + pos + len, end);
    // puts(buf);
}
void delete(int pos, int n)
{
    // puts(buf);
    int i;
    char *p = buf + pos;
    if (p + n > buf + strlen(buf))
        n = strlen(buf) - pos;
    while (*p = *(p + n))
        p++;
    // puts(buf);
}