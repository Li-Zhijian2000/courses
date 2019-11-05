#define local
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 105;

char a[maxn], b[maxn];
int dp[maxn][maxn];

char res[105];

void print_ans(int i, int j, int level) {
    if (level < 0) {
        printf("%s\n", res);
        return;
    }
    if (!i || !j) return;
    
    if (a[i] == b[j]) {
        res[level] = a[i];
        print_ans(i-1, j-1, level-1);
    }
    else {
        if (dp[i - 1][j] >= dp[i][j - 1]) print_ans(i - 1, j, level);
        if (dp[i][j - 1] >= dp[i - 1][j]) print_ans(i, j - 1, level);
    }
}

int main() {
#ifdef local
    freopen("d.txt", "r", stdin);
#endif

    while (~scanf("%s%s", a, b)) {
        int lena = strlen(a), lenb = strlen(b);
        for (int i = 0; i < lena; i++)
            for (int j = 0; j < lenb; j++)
                if (a[i] == b[j]) 
                    dp[i+1][j+1] = dp[i][j] + 1;
                else dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
        res[dp[lena][lenb]] = 0;
        print_ans(lena, lenb, dp[lena][lenb]-1);
    }
    return 0;
}
