#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define n 1000

int main() {
    FILE *in = fopen("filein.txt", "r"), *out = fopen("fileout.txt", "w");

    char t1[n], t2[n];
    scanf("%s%s", t1, t2);

    char s1[n], s2[n];
    while (1) {
        memset(s1, 0, sizeof(s1));
        memset(s2, 0, sizeof(s2));
        if (!fgets(s1, n, in)) break;

        char lower_s1[n];
        int i, len = strlen(s1);

        // 将输入串转换成小写
        for (i = 0; i < len; i++) lower_s1[i] = tolower(s1[i]);
        lower_s1[len] = '\0';

        char *p_s1 = s1, *p_lower_s1 = lower_s1,
             *p_s2 = s2;  // 因为数组指针不可变，所以将其赋值给指针

        char *p;
        // 找到重复的字串
        while (p = strstr(p_lower_s1, t1)) {
            // 将字串前的非重复部分复制
            strncpy(p_s2, p_s1, p - p_lower_s1);
            p_s2 += p - p_lower_s1;

            // 替换重复的部分
            strcpy(p_s2, t2);
            p_s2 += strlen(t2);

            // 以下调整变量，以便下一次循环
            p_lower_s1 = p + strlen(t1);

            p_s1 = s1 + (p_lower_s1 - lower_s1);
        }
        strcpy(p_s2, p_s1);
        fputs(s2, out);
    }

    return 0;
}