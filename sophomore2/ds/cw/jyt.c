#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
    char word[50];
    int count1;
    int count2;
    int flag;
};
struct node dic[900000];
struct node2 {
    char zimu;
    int begin;
    int geshu;
};
struct node3 {
    char word[50];
    int count;
};
struct node3 article1[700000], article2[700000];
struct node2 suoyin1[26], suoyin2[26];
int top = 0;
char stopword[200000][50], dictionary[1000000][50];
int search1(char *chazhao);
int search2(char *chazhao);
int search(char *chazhao, struct node2 *suoyin, char target[][50]) {
    int i = chazhao[0] - 'a';
    if (suoyin[i].geshu == 0) return -1;

    int low = suoyin[i].begin, high = suoyin[i].begin + suoyin[i].geshu;
    while (low < high) {
        int mid = low + high >> 1;
        int res = strcmp(chazhao, target[mid]);
        if (!res) return mid;

        if (res < 0)
            high = mid;
        else
            low = mid + 1;
    }
    return -1;
}
int main() {
    FILE *in1, *in2, *in3, *in4, *out;
    in1 = fopen("dictionary.txt", "r");
    in2 = fopen("stopwords.txt", "r");
    in3 = fopen("article1.txt", "r");
    in4 = fopen("article2.txt", "r");
    out = fopen("result.txt", "w");

    int i;

    while (fscanf(in2, "%s", stopword[top]) != EOF) {
        top++;
    }
    top--;
    for (i = 0; i < 26; i++) {
        suoyin1[i].zimu = i + 'a';
        suoyin1[i].geshu = 0;
    }
    for (i = 0; i <= top; i++) {
        suoyin1[stopword[i][0] - 'a'].geshu++;
    }
    int zonghe = 0;
    for (i = 0; i < 26; i++) {
        suoyin1[i].begin = zonghe;
        zonghe += suoyin1[i].geshu;
    }
    top = 0;
    int temp2;
    while (fscanf(in1, "%s", dictionary[top]) != EOF) {
        strcpy(dic[top].word, dictionary[top]);
        dic[top].count1 = dic[top].count2 = dic[top].flag = 0;
        top++;
    }
    top--;
    // dictionary����������
    for (i = 0; i < 26; i++) {
        suoyin2[i].zimu = i + 'a';
        suoyin2[i].geshu = 0;
    }
    for (i = 0; i <= top; i++) {
        suoyin2[dictionary[i][0] - 'a'].geshu++;
    }
    zonghe = 0;
    for (i = 0; i < 26; i++) {
        suoyin2[i].begin = zonghe;
        zonghe += suoyin2[i].geshu;
    }
    //����article1
    i = 0;
    char c;
    char word[50];
    int temp;
    int j;
    while (1) {
        c = fgetc(in3);
        if (c == EOF) break;

        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
            word[i] = c;
            i++;
        } else if (c >= 'a' && c <= 'z') {
            // i++;
            word[i] = c;
            i++;
        } else if (c < 'a' || c > 'z') {
            if (i != 0) {
                word[i] = '\0';
                temp = search(word, suoyin2, dictionary);
                if (search(word, suoyin1, stopword) == -1 && temp != -1) {
                    dic[temp].count1++;
                }
                memset(word, 0, sizeof(word));
                i = 0;
            }
        }
    }
    //����article2
    i = 0;
    while (1) {
        c = fgetc(in4);
        if (c == EOF) break;

        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
            word[i] = c;
            i++;
        } else if (c >= 'a' && c <= 'z') {
            // i++;
            word[i] = c;
            i++;
        } else if (c < 'a' || c > 'z') {
            if (i != 0) {
                word[i] = '\0';
                temp = search(word, suoyin2, dictionary);
                temp2 = search(word, suoyin1, stopword);
                if (temp2 == -1 && temp != -1) {
                    dic[temp].count2++;
                }
                memset(word, 0, sizeof(word));
                i = 0;
            }
        }
    }
    int n;
    int count1n, count1m, count2n, count2m;
    count1n = count1m = count2n = count2m = 0;
    scanf("%d", &n);
    struct node3 p;
    int top1, top2;
    top1 = top2 = 0;
    for (i = 0; i <= top; i++) {
        if (dic[i].count1 > 0) {
            strcpy(article1[top1].word, dic[i].word);
            article1[top1].count = dic[i].count1;
            top1++;
        }
        if (dic[i].count2 > 0) {
            strcpy(article2[top2].word, dic[i].word);
            article2[top2].count = dic[i].count2;
            top2++;
        }
    }
    for (i = 0; i < top1; i++) {
        for (j = 0; j < top1 - i - 1; j++) {
            if (article1[j].count < article1[j + 1].count) {
                p = article1[j];
                article1[j] = article1[j + 1];
                article1[j + 1] = p;
            }
        }
    }
    for (i = 0; i < top2; i++) {
        for (j = 0; j < top2 - i - 1; j++) {
            if (article2[j].count < article2[j + 1].count) {
                p = article2[j];
                article2[j] = article2[j + 1];
                article2[j + 1] = p;
            }
        }
    }
    for (j = 0; j < n && j < top2; j++) {
        count2n += article2[j].count;
    }
    for (i = 0; i < n && i < top1; i++) {
        count1n += article1[i].count;
        for (j = 0; j < n && j < top2; j++) {
            // count2n+=article2[j].count;
            if (strcmp(article1[i].word, article2[j].word) == 0) {
                count1m += article1[i].count;
                count2m += article2[j].count;
            }
        }
    }
    double pro1 = 1.0 * count1m / count1n, pro2 = 1.0 * count2m / count2n;
    double sim;
    if (pro1 > pro2) {
        sim = (double)(count2m * count1n) / (count2n * count1m);
        printf("%.5lf\n", sim);
        fprintf(out, "%.5lf\n", sim);
    } else {
        sim = (double)(count1m * count2n) / (count1n * count2m);
        printf("%.5lf\n", sim);
        fprintf(out, "%.5lf\n", sim);
    }
    fprintf(out, "\n");
    for (i = 0; i < n && i < top1; i++) {
        fprintf(out, "%s %d\n", article1[i].word, article1[i].count);
    }
    fprintf(out, "\n");
    for (i = 0; i < n && i < top2; i++) {
        fprintf(out, "%s %d\n", article2[i].word, article2[i].count);
    }
}

int search1(char *chazhao) {  //��stopword���Ƿ���ڸõ���
    int i;
    int low, mid, high;
    int flag;
    if (suoyin1[chazhao[0] - 'a'].geshu == 0) return -1;
    low = suoyin1[chazhao[0] - 'a'].begin;
    high = low + suoyin1[chazhao[0] - 'a'].geshu;
    // mid=(low+high)/2;
    flag = 0;
    // num=0;
    while (low <= high) {
        mid = (low + high) / 2;
        // num++;
        if (strcmp(chazhao, stopword[mid]) == 0) {
            flag = 1;
            // num++;
            break;
        } else if (strcmp(chazhao, stopword[mid]) > 0) {
            low = mid + 1;
        } else if (strcmp(chazhao, stopword[mid]) < 0) {
            high = mid - 1;
        }
    }
    if (flag == 1) {
        return mid;
    } else
        return -1;
}
int search2(char *chazhao) {  //��stopword���Ƿ���ڸõ���
    int i;
    int low, mid, high;
    int flag;
    if (suoyin2[chazhao[0] - 'a'].geshu == 0) {
        return -1;
    } else {
        low = suoyin2[chazhao[0] - 'a'].begin;
        high = low + suoyin2[chazhao[0] - 'a'].geshu;
        // mid=(low+high)/2;
        flag = 0;
        // num=0;
        while (low <= high) {
            mid = (low + high) / 2;
            // num++;
            if (strcmp(chazhao, dictionary[mid]) == 0) {
                flag = 1;
                // num++;
                break;
            } else if (strcmp(chazhao, dictionary[mid]) > 0) {
                low = mid + 1;
            } else if (strcmp(chazhao, dictionary[mid]) < 0) {
                high = mid - 1;
            }
        }
        if (flag == 1) {
            return mid;
        } else {
            return -1;
        }
    }
}
