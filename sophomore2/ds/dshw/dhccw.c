#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define inf 3000000
#define mode 1000000007
#define p 10000019
struct index {
    char word[200];
    int times;
    int dele;
    int vis;
};
struct index dic1[inf], dic2[inf], stop[inf];
char s[1040], s1[1040];
int n;

int hash(char s[]) {
    long long sum = 0;
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        sum = ((sum * 27) + tolower(s[i])) % inf;
    }
    return sum;
}
int cmp(const void *a, const void *b) {
    struct index *c = (struct index *)a;
    struct index *d = (struct index *)b;
    if (c->times > d->times)
        return -1;
    else if (c->times < d->times)
        return 1;
    else
        return strcmp(c->word, d->word);
}
void check1(char s[]) {
    int i = 1, temp, now;
    now = hash(s);
    // if(now == 6513)	printf("---------%s\n",s);
    if (stop[now].vis == 1) {
        temp = now;
        while (strcmp(stop[temp].word, s) != 0 && stop[temp].vis == 1) {
            temp = now + i * i;
            i++;

            if (temp >= inf) temp %= inf;
        }

        if (strcmp(stop[temp].word, s) == 0 && stop[temp].vis == 1) return;
    }

    if (dic1[now].vis == 1) {
        temp = now;
        i = 1;
        while (strcmp(dic1[temp].word, s) != 0 && dic1[temp].vis == 1) {
            temp = now + i * i;
            i++;

            if (temp >= inf) temp %= inf;
        }
    }
    if (dic1[temp].vis == 1 && strcmp(dic1[temp].word, s) == 0)
        dic1[temp].times++;
}
void check2(char s[]) {
    int i = 1, temp, now;
    now = hash(s);

    if (stop[now].vis == 1) {
        temp = now;
        while (strcmp(stop[temp].word, s) != 0 && stop[temp].vis == 1) {
            temp = now + i * i;
            i++;

            if (temp >= inf) temp %= inf;
        }

        if (strcmp(stop[temp].word, s) == 0 && stop[temp].vis == 1) return;
    }

    if (dic2[now].vis == 1) {
        temp = now;
        i = 1;
        while (strcmp(dic1[temp].word, s) != 0 && dic2[temp].vis == 1) {
            temp = now + i * i;
            i++;

            if (temp >= inf) temp %= inf;
        }
    }
    // if(temp == 289480)	printf("%s____	%d\n",s,cnt++);
    if (dic2[temp].vis == 1 && strcmp(dic1[temp].word, s) == 0)
        dic2[temp].times++;
}
int main() {
    FILE *article1, *article2, *out, *dicc, *stopp;
    int i, j, temp, now;
    double freq0 = 0, freq00 = 0, freq1 = 0, freq2 = 0, len;
    double pro1, pro2;

    scanf("%d", &n);
    dicc = fopen("dictionary.txt", "r");
    stopp = fopen("stopwords.txt", "r");
    article1 = fopen("article1.txt", "r");
    article2 = fopen("article2.txt", "r");
    out = fopen("results.txt", "w");

    while (fscanf(dicc, "%s", s) != EOF) {
        temp = now = hash(s);
        i = 1;
        while (dic1[temp].vis == 1) {
            temp = now + i * i;
            i++;
            if (temp >= inf) temp %= inf;
        }
        for (i = 0; s[i] != '\0'; i++)
            dic1[temp].word[i] = dic2[temp].word[i] = tolower(s[i]);
        dic1[temp].vis = dic2[temp].vis = 1;
        dic2[temp].word[i] = dic1[temp].word[i] = '\0';
        memset(s, 0, sizeof(s));
    }
    while (fscanf(stopp, "%s", s) != EOF) {
        temp = now = hash(s);
        i = 1;

        while (stop[temp].vis == 1) {
            temp = now + i * i;
            i++;

            if (temp >= inf) temp %= inf;
        }
        for (i = 0; s[i] != '\0'; i++) stop[temp].word[i] = tolower(s[i]);
        stop[temp].word[i] = '\0';
        stop[temp].vis = 1;

        memset(s, 0, sizeof(s));
    }
    while (fscanf(article1, "%s", s) != EOF) {
        i = 0;
        do {
            for (j = 0; isalpha(s[i]); i++, j++) s1[j] = tolower(s[i]);
            s1[j] = '\0';
            check1(s1);
            i++;
            memset(s1, 0, sizeof(s1));
        } while (s[i]);
        memset(s, 0, sizeof(s));
    }
    while (fscanf(article2, "%s", s) != EOF) {
        i = 0;
        do {
            for (j = 0; isalpha(s[i]); i++, j++) s1[j] = tolower(s[i]);
            s1[j] = '\0';
            check2(s1);
            i++;
            memset(s1, 0, sizeof(s1));
        } while (s[i]);
        memset(s, 0, sizeof(s));
    }

    qsort(dic1, inf, sizeof(dic1[0]), cmp);
    qsort(dic2, inf, sizeof(dic2[0]), cmp);

    for (i = 0; dic1[i].times && i < n; i++) {
        freq1 += dic1[i].times;

        for (j = 0; dic2[j].times && j < n; j++) {
            if (dic2[j].dele || strcmp(dic1[i].word, dic2[j].word) != 0)
                continue;

            dic2[j].dele = 1;
            freq0 += dic1[i].times;
            freq00 += dic2[j].times;

            break;
        }
    }
    for (j = 0; dic2[j].times && j < n; j++) freq2 += dic2[j].times;

    pro1 = freq0 / freq1;
    pro2 = freq00 / freq2;
    printf("%.5f", min(pro1, pro2) / max(pro1, pro2));
    fprintf(out, "%.5f\n\n", min(pro1, pro2) / max(pro1, pro2));
    for (i = 0; i < n && dic1[i].times; i++)
        fprintf(out, "%s %d\n", dic1[i].word, dic1[i].times);
    fputs("\n", out);
    for (i = 0; i < n && dic2[i].times; i++)
        fprintf(out, "%s %d\n", dic2[i].word, dic2[i].times);
    return 0;
}