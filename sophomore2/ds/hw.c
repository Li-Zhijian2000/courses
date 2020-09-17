#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_Char_Number 28
#define Max_Word_Len 60
#define isAlpha(c) ((97 <= c && c <= 122) || (65 <= c && c <= 90))
#define isUpper(c) (65 <= c && c <= 90)

struct Word {
    char word[70];
    int time;
    char both;
};
struct Word dictionary[1000000];
struct Word stopwords[1000000];
typedef struct Word *wordPtr;
int cnt1 = 0, cnt2 = 0;
int total1, total2;
struct Word top1[1000000];

struct Trie_Node {
    struct Word *link;
    struct Trie_Node *next_[Max_Char_Number];
};
// struct Trie_Node nodes[5500000];
int total = 0;
struct Trie_Node root1 = {NULL, {NULL}};
struct Trie_Node root2 = {NULL, {NULL}};

FILE *dic, *stop, *art1, *art2;
int n;

void initDic(FILE *fp);
void initStop(FILE *fp);
void insert(struct Trie_Node *, char *, struct Word *);
wordPtr search(struct Trie_Node *, char *);
void cal(FILE *);
void copy(struct Word *);
int cmp(const void *, const void *);
int main() {
    scanf("%d", &n);
    dic = fopen("dictionary.txt", "r");
    initDic(dic);
    stop = fopen("stopwords.txt", "r");
    initStop(stop);

    art1 = fopen("article1.txt", "r");
    art2 = fopen("article2.txt", "r");

    FILE *res = fopen("results.txt", "w");
    int i = 0;

    cal(art1);  //	printf("done1\n");
    copy(top1);
    qsort(top1, cnt1 + 1, sizeof(top1[0]), cmp);

    cal(art2);
    qsort(dictionary, cnt1 + 1, sizeof(dictionary[0]), cmp);
    wordPtr ptr = NULL;
    int sumBoth1 = 0, sum1 = 0, sumBoth2 = 0, sum2 = 0;
    double pro1 = 0, pro2 = 0, sim = 0;
    struct Trie_Node temp = {NULL, {NULL}};

    for (i = cnt1; i >= cnt1 - n + 1; --i) {
        if (dictionary[i].time != 0) {
            insert(&temp, dictionary[i].word, &dictionary[i]);
            ++total2;
        } else
            break;
    }
    int n1 = n < total1 ? n : total1;
    int n2 = n < total2 ? n : total2;
    for (i = cnt1; i >= cnt1 - n1 + 1; --i) {
        ptr = search(&temp, top1[i].word);
        if (ptr != NULL) {
            ptr->both = 1;
            top1[i].both = 1;
            sumBoth1 += top1[i].time;
        }
        sum1 += top1[i].time;
    }
    //	printf("done2\n");
    for (i = cnt1; i >= cnt1 - n2 + 1; --i) {
        if (dictionary[i].both == 1) {
            sumBoth2 += dictionary[i].time;
        }
        sum2 += dictionary[i].time;
    }
    pro1 = sumBoth1 * 1.0 / sum1;
    pro2 = sumBoth2 * 1.0 / sum2;
    sim = (pro1 < pro2) ? (pro1 / pro2) : (pro2 / pro1);
    fprintf(res, "%.5f\n\n", sim);
    for (i = cnt1; i >= cnt1 - n1 + 1; --i)
        fprintf(res, "%s %d\n", top1[i].word, top1[i].time);
    fprintf(res, "\n");
    for (i = cnt1; i >= cnt1 - n2 + 1; --i)
        fprintf(res, "%s %d\n", dictionary[i].word, dictionary[i].time);
    printf("%.5f\n", sim);
    return 0;
}
int cmp(const void *a, const void *b) {
    if (((wordPtr)a)->time != ((wordPtr)b)->time)
        return ((wordPtr)a)->time - ((wordPtr)b)->time;
    else
        return strcmp(((wordPtr)b)->word, ((wordPtr)a)->word);
}
void copy(struct Word top[]) {
    int i = 0;
    for (; i <= cnt1; ++i) {
        top[i] = dictionary[i];
        if (dictionary[i].time != 0) {
            ++total1;
            dictionary[i].time = 0;
        }
    }
}
void cal(FILE *fp) {
    int i = 0, flag = 0;
    char c = 0;
    char word[70] = {'\0'};
    wordPtr p = NULL;
    wordPtr q = NULL;
    while ((c = fgetc(fp)) != EOF) {
        if (!isAlpha(c)) {
            do {
                c = fgetc(fp);
                if (c == EOF) {
                    flag = 1;
                    break;
                }
            } while (!isAlpha(c));
            word[i++] = '\0';
            p = search(&root1, word);
            q = search(&root2, word);
            if (p != NULL && q == NULL) {
                ++(p->time);
                //	printf("%s\n",word);
            }
            i = 0;
        }
        if (flag == 1) break;
        if (isUpper(c))
            word[i++] = c + 32;
        else
            word[i++] = c;
    }
    if (i != 0) {
        word[i++] = '\0';
        p = search(&root1, word);
        q = search(&root2, word);
        if (p != NULL && q == NULL) {
            ++(p->time);
        }
    }
}
wordPtr search(struct Trie_Node *root, char *word) {
    int loop;
    struct Trie_Node *cur;
    cur = root;
    for (loop = 0;; ++loop) {
        if (word[loop] == '\0') return cur->link;
        if (cur->next_[word[loop] - 97] == NULL) return NULL;
        cur = cur->next_[word[loop] - 97];
    }
}
void insert(struct Trie_Node *root, char *word, struct Word *ptr) {
    int loop;
    struct Trie_Node *cur, *newnode;
    if (word[0] == '\0') return;
    cur = root;
    for (loop = 0;; ++loop) {
        if (word[loop] == '\0') break;
        if (cur->next_[word[loop] - 97] == NULL) {
            newnode = (struct Trie_Node *)malloc(sizeof(struct Trie_Node));
            memset(newnode, 0, sizeof(struct Trie_Node));
            cur->next_[word[loop] - 97] = newnode;
            //++total;
        }
        cur = cur->next_[word[loop] - 97];
    }
    cur->link = ptr;
    return;
}
void initStop(FILE *fp) {
    int i = 0, flag = 0;
    char c = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (!isAlpha(c)) {
            do {
                c = fgetc(fp);
                if (c == EOF) {
                    flag = 1;
                    break;
                }
            } while (!isAlpha(c));
            dictionary[cnt2].word[i] = '\0';
            insert(&root2, stopwords[cnt2].word, &stopwords[cnt2]);
            i = 0;
            ++cnt2;
        }
        if (flag == 1) break;
        stopwords[cnt2].word[i++] = c;
    }
    if (i != 0) {
        stopwords[cnt2].word[i] = '\0';
        insert(&root2, stopwords[cnt2].word, &stopwords[cnt2]);
    }
}
void initDic(FILE *fp) {
    int i = 0, flag = 0;
    char c = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (!isAlpha(c)) {
            do {
                c = fgetc(fp);
                if (c == EOF) {
                    flag = 1;
                    break;
                }
            } while (!isAlpha(c));
            dictionary[cnt1].word[i] = '\0';
            insert(&root1, dictionary[cnt1].word, &dictionary[cnt1]);
            // printf("%s\n",dictionary[cnt1].word);
            //			if(cnt1%2500==0)
            //				printf("%d\n",cnt1);
            i = 0;
            ++cnt1;
        }
        if (flag == 1) break;
        dictionary[cnt1].word[i++] = c;
    }
    if (i != 0) {
        dictionary[cnt1].word[i] = '\0';
        insert(&root1, dictionary[cnt1].word, &dictionary[cnt1]);
    }
}
