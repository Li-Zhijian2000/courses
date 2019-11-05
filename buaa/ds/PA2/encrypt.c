#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main()
{
    char str[50], key[27];
    int check[26] = {0};
    gets(str);
    FILE *in = fopen("encrypt.txt", "r"), *out = fopen("output.txt", "w");
    int lens = strlen(str), i, j;
    for (i = 0, j = 0; i < lens; i++) {
        if (!check[str[i] - 'a']) {
            key[j++] = str[i];
            check[str[i] - 'a'] = 1;
        }
    }
    for (i = 25; i >= 0; i--) {
        if (!check[i])
            key[j++] = i + 'a';
    }
    key[j] = '\0';
    char c;
    while ((c = fgetc(in)) != EOF) {
        if (isalpha(c))
            c = key[c - 'a'];
        fputc(c, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}

