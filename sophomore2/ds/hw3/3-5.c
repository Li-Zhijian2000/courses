#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 1000

struct Word {
    char s[50];
} words[maxn];

char line[50 * maxn];

int comp(const void *lhs, const void *rhs) {
    return strcmp(((struct Word *)lhs)->s, ((struct Word *)rhs)->s);
}
int main() {
    FILE *in = fopen("article.txt", "r");
    char ch;
    int i = 0;
    while ((ch = fgetc(in)) != EOF) {
        if (isalpha(ch))
            line[i++] = tolower(ch);
        else
            line[i++] = ' ';
    }

    int offset, cnt = 0, num;
    char word[100], *data = line;
    while (~sscanf(data, "%s%n", word, &offset)) {
        data += offset;
        strcpy(words[cnt++].s, word);
    }

    qsort(words, cnt, sizeof(words[0]), comp);
    for (i = 0, num = 1; i < cnt; i++) {
        if (i != cnt - 1 && !strcmp(words[i].s, words[i + 1].s))
            num++;
        else {
            printf("%s %d\n", words[i].s, num);
            num = 1;
        }
    }
    return 0;
}
