#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define maxn 1500000 + 5
// #define LOCAL
typedef struct {
    int x, y;
}Point;

Point point[maxn], stack[maxn];

int read_decimal();
int read_binary();

int toLeft(Point a, Point b, Point c)
{ //juege point c if in the left of directive ab
    long long flag =  (long long)a.x * b.y + (long long)b.x * c.y + (long long)c.x * a.y - 
                      (long long)a.y * b.x - (long long)b.y * c.x - (long long)c.y * a.x; 
    return flag > 0 ? 1 : 
           flag < 0 ? -1 : 0;
}
int comp(const void *lhs, const void *rhs)
{
    Point *a = (Point*)lhs, *b = (Point*)rhs;
    // return (a->x != b->x) ? (a->x - b->x) : (a->y - b->y);
    return (a->y != b->y) ? (a->y - b->y) : (a->x - b->x);
}

void printStack(int n)
{
    for (int i = 0; i < n; i++)
        printf("%d %d\n", stack[i].x, stack[i].y);
}

int main()
{
    int n, size = 0;
    #ifdef LOCAL
    n = read_decimal();
    #else
    n = read_binary();
    #endif

    qsort(point, n, sizeof(point[0]), comp);

    for (int i = 0; i < n; i++) {
        while (size > 1 && toLeft(stack[size - 2], stack[size - 1], point[i]) <= 0) {
            size--;
        }
        stack[size++] = point[i];
    }
    
    int k = size;
    for (int i = n - 2; i >= 0; i--) {
        while (size > k && toLeft(stack[size - 2], stack[size - 1], point[i]) <= 0) {
            size--;
        }
        stack[size++] = point[i];
    }
    if (n > 1) {
        size--;
    }
    printStack(size);
    return 0;
}
int read_decimal()
{
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d%d", &point[i].x, &point[i].y);
    }
    return n;
}
int read_binary()
{
    int n, i;
    fread(&n, sizeof(int), 1, stdin);
    for (i = 0; i < n; i++) {
        fread(&point[i].x, sizeof(int), 1, stdin);
        fread(&point[i].y, sizeof(int), 1, stdin);
    }
    return n;
}