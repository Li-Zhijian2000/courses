#include <iostream>
#include <cstdio>
#include<cmath>
#include <cstring>
#include<stdlib.h>
#include<algorithm>
using namespace std;
struct thing{
	long long c1;
	long long c2;
}; 
bool cmp(const thing &a, const thing &b)
{
	if(a.c1 != b.c1)
		return a.c1 > b.c1;
	else
		return a.c2 > b.c2;
}
thing a[100050], b[100050];
int sign[100050], n, m;
int main()
{
	int i, j, t, mi, flag;
	long long ans;
	while(scanf("%d%d",&n,&m) != EOF)
	{
		ans = 0;
		t = 0;
		memset(sign, 0, sizeof(sign));
		for(i = 0; i < n; i++)
			scanf("%lld %lld", &a[i].c1, &a[i].c2);
		for(i = 0; i < m; i++)
			scanf("%lld %lld", &b[i].c1, &b[i].c2);
		sort(a, a + n, cmp);
		sort(b, b + m, cmp);
		for(i = 0; i < m; i++)
		{
			j = 0;
			flag = -1;
			mi = 999999999;
			while(a[j].c1 >= b[i].c1 && j <= n - 1)
			{
				if(a[j].c2 < mi && sign[j] == 0 && a[j].c2 >= b[i].c2)
				{
					mi = a[j].c2;
					flag = j;
				}
				j++;
			}
			if(flag >= 0 && flag <= n - 1 && a[flag].c1 >= b[i].c1 && a[flag].c2 >= b[i].c2 && sign[flag] == 0)
			{
				sign[flag] = 1;
				t++;
				ans += (1000 * b[i].c1 + 10 * b[i].c2);
			}
		}
		printf("%d %lld\n", t, ans);
	}
}