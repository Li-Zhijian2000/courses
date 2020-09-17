#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXN 420000
#define MAXM 1200000
#define ARTICLESIZE 8000000
// 6200000 - 30000000
char article[ARTICLESIZE];
typedef struct Trie {
    int cnt;  //�õ������ֵ��е�λ�ã�0��ʾ�õ��ʲ����ֵ���
    int children[26];
} Trie;
Trie trie[MAXM];
int trie_size;
struct node {
    char *word;
    int cnt;
};
struct node count1[MAXN];
struct node count2[MAXN];
char *dict[MAXN];
int n_dict;
int isStop[MAXN];
int make_dictionary(char *dict[]);

int bisearch(struct node count[], char *s, int len);
void count(char *filename, struct node cnt[]);
int cmp1(const void *a, const void *b);
int cmp2(const void *a, const void *b);

void Order_static(struct node count[], int l, int r, int n);

int searchTrie(char *keyword) {
    int now = 0;
    while (*keyword != '\0') {
        if (trie[now].children[*keyword - 'a'] == 0) return -1;
        now = trie[now].children[*keyword - 'a'];
        keyword++;
    }
    return trie[now].cnt;
}
int main() {
    int n;
    scanf("%d", &n);

    char tmp[100];
    int top = 0;
    FILE *file = fopen("dictionary.txt", "r");

    while (fscanf(file, "%s", tmp) != EOF) {
        int n = strlen(tmp);
        count1[top].word = (char *)malloc(sizeof(char) * (n + 1));
        strcpy(count1[top].word, tmp);
        top++;
    }

    file = fopen("stopwords.txt", "r");
    memset(isStop, 0, sizeof(int) * top);

    while (fscanf(file, "%s", tmp) != EOF) {
        int t = bisearch(count1, tmp, top);
        if (t == -1)
            continue;
        else
            isStop[t] = 1;
    }
    fclose(file);
    int ret = 0;
    for (int i = 0; i < top; i++) {
        if (isStop[i])
            free(count1[i].word);
        else
            dict[ret++] = count1[i].word;
    }
    n_dict = ret;
    int len = ret;

    for (int i = 0; i < len; i++) {
        count1[i].word = dict[i];
        count2[i].word = dict[i];
    }
    memset(trie, 0, sizeof(trie));
    for (int i = 0; i < MAXM; i++) trie[i].cnt = -1;
    trie_size = 1;
    for (int i = 0; i < n_dict; i++) {
        char *word = dict[i];
        int index = i;
        int now = 0;
        while (*word != '\0') {
            if (trie[now].children[*word - 'a'] == 0)  // û�и���ĸ��Ӧ�ķ�֧
            {
                trie[now].children[*word - 'a'] = trie_size++;
            }
            now = trie[now].children[*word - 'a'];
            word++;
        }
        trie[now].cnt = index;
    }

    count("article1.txt", count1);
    count("article2.txt", count2);

    if (n < len) {
        Order_static(count1, 0, len - 1, n - 1);
        Order_static(count2, 0, len - 1, n - 1);
    } else
        n = len;

    qsort(count2, n, sizeof(struct node), cmp1);

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    for (int i = 0; i < n; i++) {
        y1 += count1[i].cnt;
        y2 += count2[i].cnt;
    }
    for (int i = 0; i < n; i++) {
        int t = bisearch(count2, count1[i].word, n);
        if (t == -1) continue;
        x1 += count1[i].cnt;
        x2 += count2[t].cnt;
    }
    // printf("x1 = %d, x2 = %d, y1 = %d, y2 = %d\n",x1,x2,y1,y2);
    double pro1 = (double)x1 / y1;
    double pro2 = (double)x2 / y2;
    double pro_max = pro1 > pro2 ? pro1 : pro2;
    double pro_min = pro1 < pro2 ? pro1 : pro2;
    double sim = pro_min / pro_max;
    printf("%.5f\n", sim);

    qsort(count2, n, sizeof(struct node), cmp2);
    qsort(count1, n, sizeof(struct node), cmp2);

    file = fopen("results.txt", "w");
    fprintf(file, "%.5f\n\n", sim);
    for (int i = 0; i < n; i++)
        fprintf(file, "%s %d\n", count1[i].word, count1[i].cnt);
    fprintf(file, "\n");
    for (int i = 0; i < n; i++)
        fprintf(file, "%s %d\n", count2[i].word, count2[i].cnt);
    return 0;
}


int bisearch(struct node count[], char *s, int len) {
    int l = 0, r = len - 1;
    int mid;

    while (l <= r) {
        mid = (l + r) >> 1;
        int t = strcmp(count[mid].word, s);
        if (t == 0)
            return mid;
        else if (t < 0)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}
int cmp2(const void *_a, const void *_b) {
    struct node *a = (struct node *)_a;
    struct node *b = (struct node *)_b;
    if (a->cnt == b->cnt) return strcmp(a->word, b->word);
    return b->cnt - a->cnt;
}
int cmp1(const void *_a, const void *_b) {
    struct node *a = (struct node *)_a;
    struct node *b = (struct node *)_b;
    return strcmp(a->word, b->word);
}

void count(char *filename, struct node cnt[]) {
    FILE *f = fopen(filename, "r");
    int size = fread(article, sizeof(char), ARTICLESIZE, f);
    fclose(f);

    article[size] = '\0';
    char *st = article;
    char *ed = st;

    while (1) {
        while (*st != '\0' && !isalpha(*st)) st++;
        if (*st == '\0') break;
        ed = st;
        while (*ed != '\0' && isalpha(*ed)) {
            *ed = tolower(*ed);
            ed++;
        }
        if (*ed == '\0') {
            int t = searchTrie(st);
            if (t != -1) cnt[t].cnt++;
            break;
        } else {
            *ed = '\0';
            int t = searchTrie(st);
            if (t != -1) cnt[t].cnt++;
            st = ed + 1;
        }
    }
}

void Order_static(struct node count[], int l, int r, int n) {
    if (l >= r) return;
    int mid = rand() % (r + 1 - l) + l, i = l, j = r;
    struct node x = count[mid];
    while (i < j) {
        while (cmp2(&count[i], &x) < 0 && i < j) i++;
        while (cmp2(&count[j], &x) > 0 && i < j) j--;
        if (i >= j) break;
        struct node hold = count[i];
        count[i] = count[j];
        count[j] = hold;
    }
    count[j] = x;
    if (j == n)
        return;
    else if (j < n)
        Order_static(count, j + 1, r, n);
    else
        Order_static(count, l, j - 1, n);
}
