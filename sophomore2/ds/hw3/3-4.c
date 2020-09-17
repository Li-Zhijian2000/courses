#include <stdio.h>
#include <string.h>
#define maxn 130
#define min 32
#define max 127
char key[maxn], list[maxn], next[maxn], prev[maxn];

int main() {
    FILE *in = fopen("in.txt", "r"), *out = fopen("in_crpyt.txt", "w");
    char line[maxn];
    gets(line);
    int lens = strlen(line), i, cnt;
    for (i = 0, cnt = 0; i < lens; i++) {
        if (!key[line[i]]) {
            list[cnt++] = line[i];
            key[line[i]] = 1;
        }
    }
    for (i = min; i < max; i++)
        if (!key[i]) list[cnt++] = i;

    for (i = 0; i < cnt; i++) {
        next[i] = (i + 1) % cnt;
        prev[i] = (i - 1 + cnt) % cnt;
    }
    int j, first, cur, step;
    for (i = 1, first = list[0], cur = 0; i < cnt; i++) {
        step = list[cur];
        next[prev[cur]] = next[cur];
        prev[next[cur]] = prev[cur];
        cur = prev[cur];
        for (j = 0; j < step % (cnt - i); j++) cur = next[cur];
        key[step] = list[cur];
    }
    key[list[cur]] = first;

    char ch;
    while ((ch = fgetc(in)) != EOF) {
        if (ch >= min && ch < max)
            fputc(key[ch], out);
        else
            fputc(ch, out);
    }

    return 0;
}