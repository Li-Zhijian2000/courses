#include <stdio.h>
#define maxn 1000000 + 5

int interviewee[maxn], next[maxn],stack[maxn];

int main()
{
    int n, m, pos = 0, i;
    scanf("%d%d", &n, &m);
    scanf("%d", interviewee);

    for (int i = 1; i < n; i++) {
        int x, forward = m % i;
        scanf("%d", &x);
        while (forward--)
            pos = next[pos];
        interviewee[i] = x;
        next[i] = next[pos];
        next[pos] = i;
    }
    pos = next[pos];
    pos = next[pos];
    for (i = 0; i < n; i++) {
        stack[i] = interviewee[pos];
        pos = next[pos];
    }
    for (i = n - 1; i >= 0; i--)
        printf("%d ", stack[i]);
    puts("");
    return 0;
}