#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAX 200
char word[25], aim[25];  // word����ļ������ĵ��ʣ�aim�������Ҫ���ҵĵ���
char chart[5000][25];
int result;
int search1(FILE *fp);
int search2(FILE *fp);
int main() {
    FILE *fp;
    int num, count;
    fp = fopen("dictionary3000.txt", "r");
    while (scanf("%s", aim) != EOF) {
        scanf("%d", &num);
        if (num == 1) {
            count = search1(fp);
            printf("%d %d\n", result, count);
        }
        if (num == 2) {
            count = search2(fp);
            printf("%d %d\n", result, count);
        }
    }
}
int search1(FILE *fp) {
    int count = 0;
    while (fgets(word, 25, fp) != NULL) {
        word[strlen(word) - 1] = '\0';
        if (strcmp(word, aim) < 0) count++;
        if (strcmp(word, aim) == 0) {
            count++;
            result = 1;
            return count;
        }
        if (strcmp(word, aim) > 0) {
            count++;
            result = 0;
            return count;
        }
    }
}
int search2(FILE *fp) {
    int i = 0, low = 0, high, mid, count = 0;
    while (fgets(chart[i], 25, fp) != NULL) {
        // chart[i][strlen(chart[i]) - 1] = '\0';
        i++;
    }
    // printf("%d\n", i);
    high = i - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (strcmp(chart[mid], aim) == 0) {
            result = 1;
            count++;
            return count;
        }
        if (strcmp(chart[mid], aim) < 0) {
            count++;
            low = mid + 1;
        } else {
            count++;
            high = mid - 1;
        }
    }
    result = 0;
    return count;
}
