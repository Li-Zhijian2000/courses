#include <stdio.h>
#include <stdlib.h>
#define maxn 1000005

int queue[maxn], front, back;

typedef struct 
{
    int price;
    int count;
}Cnt;
Cnt cnt[maxn];
int cntFront, cntBack;

long long count;

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char opt;
        int pushCnt, price;
        scanf(" %c", &opt);
        switch (opt)
        {
        case 'E':
            scanf("%d", &price);
            pushCnt = 1;
            queue[back++] = price;
            while (cntFront < cntBack && cnt[cntBack - 1].price < price) {
                pushCnt += cnt[--cntBack].count;
            }
            cnt[cntBack++] = (Cnt){price, pushCnt};

            printf("%lld\n", (++count) * cnt[cntFront].price);
            break;
        
        case 'D':
            if (cnt[cntFront].count > 1) {
                cnt[cntFront].count--;
            }
            else {
                cntFront++;
            }
            printf("%lld\n", (--count) * cnt[cntFront].price);
            break;
        default:
            break;
        }
    }
    return 0;
}