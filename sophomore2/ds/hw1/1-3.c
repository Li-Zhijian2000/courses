#include <stdio.h>
#include <string.h>

#define maxn 1000

struct BigInt {
    int num[maxn];
    int len;
};

// return a < b
int less(struct BigInt a, struct BigInt b) {
    if (a.len != b.len) return a.len < b.len;

    int i = 0;
    while (i < a.len) {
        if (a.num[i] != b.num[i]) return a.num[i] < b.num[i];
        i++;
    }
    return 0;
}

void rm0(struct BigInt *a) {
    int len = a->len;
    while (len > 1 && a->num[len - 1] == 0) len--;
    a->len = len;
}
void minus(struct BigInt a, struct BigInt b) {
    if (less(a, b)) {
        putchar('-');
        minus(b, a);
        return;
    }
    struct BigInt res;
    memset(&res, 0, sizeof(res));
    int len = a.len > b.len ? a.len : b.len;
    res.len = len;
    int i;
    for (i = 0; i < len; i++) {
        res.num[i] += a.num[i] - b.num[i];
        if (res.num[i] < 0) {
            res.num[i] += 10;
            res.num[i + 1]--;
        }
    }
    
    rm0(&res);
    for (i = res.len - 1; i >= 0; i--) 
        printf("%d", res.num[i]);
    putchar('\n');
}

void read(struct BigInt *a) {
    char s[maxn];
    gets(s);
    
    int i, len = strlen(s);
    for (i = 0; i < len; i++) a->num[i] = s[len - i - 1] - '0';
    a->len = len;
    rm0(a);
}
int main() {
    struct BigInt a, b;

    read(&a);
    read(&b);

    minus(a, b);
    return 0;
}