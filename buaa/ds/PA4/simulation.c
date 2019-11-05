#include <stdio.h>

typedef struct {
    int index;
    int time;
}customer;

customer queue[2000];

int main()
{
    int m, front = 0, back = 0, n = 3, i;
    scanf("%d", &m);
    do {
        int cum = 0;
        if (m-- > 0)
            scanf("%d", &cum);
        for (i = 0; i < cum; i++, back++)
            queue[back].index = back + 1;
        n = 3;
        while (back - front >= 7 * n && n <= 4)
            n++;
        while (n-- && front < back) {
            printf("%d : %d\n", queue[front].index, queue[front].time);
            front++;
        }
            
        for (i = front; i < back; i++)
            queue[i].time++;
    } while (front < back || m > 0);
    return 0;
}
