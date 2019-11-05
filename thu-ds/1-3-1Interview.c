#include <stdio.h>
#define maxn 1000 + 5

int interviewee[maxn], pre[maxn];

int main()
{
    int n, m, pos = 0;
    scanf("%d%d", &n, &m);
    scanf("%d", interviewee);

    for (int i = 1; i < n; i++) {
        int x, forward = i - m % i;
        scanf("%d", &x);
        while (forward--)
            pos = pre[pos];
        interviewee[i] = x;
        pre[i] = pre[pos];
        pre[pos] = i;
        pos = i;
    }
    while (n--) {
        printf("%d ", interviewee[pos]);
        pos = pre[pos];
    }
    puts("");
    return 0;
}