#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define maxn 1500000 + 5
#define LOCAL
typedef struct {
    int x, y;
}Point;

Point point[maxn], stack[maxn], ltl;

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
    return toLeft(ltl, *a, *b) ? -toLeft(ltl, *a, *b) : abs(a -> x - ltl.x) - abs(b -> x - ltl.x);
}
int read_decimal()
{
    int n, i;
    ltl.x = ltl.y = 0x77777777;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d%d", &point[i].x, &point[i].y);
        if (point[i].y < ltl.y || point[i].y == ltl.y && point[i].x < ltl.x) {
            ltl = point[i];
        }
    }
    return n;
}
int read_binary()
{
    int n, i;
    ltl.x = ltl.y = 0x77777777;
    fread(&n, sizeof(int), 1, stdin);
    for (i = 0; i < n; i++) {
        fread(&point[i].x, sizeof(int), 1, stdin);
        fread(&point[i].y, sizeof(int), 1, stdin);
        if (point[i].y < ltl.y || point[i].y == ltl.y && point[i].x < ltl.x) {
            ltl = point[i];
        }
    }
    return n;
}
void printStack(int n)
{
    for (int i = 0; i < n; i++)
        printf("%d %d\n", stack[i].x, stack[i].y);
}
int main()
{
    int n, i, size = 0;
    #ifdef LOCAL
    n = read_decimal();
    #else
    n = read_binary();
    #endif

    qsort(point, n, sizeof(point[0]), comp);

    i = 1;
    stack[size++] = ltl;
    stack[size++] = point[i++];
    
    while (i < n) {
        int flag = toLeft(stack[size - 2], stack[size - 1], point[i]);
        if (flag > 0)
            stack[size++] = point[i++];
        else if (flag < 0)
            size--;
        else stack[size - 1] = point[i++];
    }
    printStack(size);
    return 0;
}