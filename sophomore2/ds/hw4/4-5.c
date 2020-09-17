#include <stdio.h>

struct Costomer {
    int index;
    int time;
} queue[1005];

int main() {
    int m, i, n = 3, front = 0, back = 0;
    scanf("%d", &m);
    do {
        int cum = 0;
        if (m > 0) scanf("%d", &cum);
        for (i = 0; i < cum; i++, back++) queue[back].index = back + 1;

        if (m-- > 0)1
            while (back - front >= 7 * n && n <= 4) n++;

        for (i = 0; i < n && front < back; i++, front++) {
            printf("%d : %d\n", queue[front].index, queue[front].time);
        }

        if (back - front < 7 * n && n >= 4) n--;
        for (i = front; i < back; i++) queue[i].time++;
    } while (front < back || m > 0);

    return 0;
}