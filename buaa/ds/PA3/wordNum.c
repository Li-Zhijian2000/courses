#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxn 1000
char *words[maxn], line[maxn * maxn];

int comp(const void *lhs, const void *rhs)
{
    return strcmp(*(char **)lhs, *(char **)rhs);
}
int main()
{
    FILE *in = fopen("article.txt", "r");
    char ch;
    int i = 0;
    while ((ch = fgetc(in)) != EOF) {
        if (isalpha(ch))
            line[i++] = tolower(ch);
        else line[i++] = ' ';
    }
    
    int offset, cnt = 0, num;
    char word[100], *data = line;
    while (~sscanf(data, "%s%n", word, &offset)) {
        data += offset;
        words[cnt] = malloc(sizeof(word) + 1);
        strcpy(words[cnt++], word);
    }
    qsort(words, cnt, sizeof(words[0]), comp);
    words[cnt] = "end of words";
    for (i = 0, num = 1; i < cnt; i++) {
        if (!strcmp(words[i], words[i+1]))
            num ++;
        else {
            printf("%s %d\n", words[i], num);
            num = 1;
        }
    }
    return 0;
}