#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1e5+5;

struct node
{
	long long x;
	long long y;
	long long l;
}ma[maxn],a[maxn];

int cmp(node& a, node& b)
{
	if(a.x!=b.x)
		return a.x>b.x;
	else
		return a.y>b.y;
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n,m,i,j,num,flag,mi,sign[maxn];
	long long ans;
	while(cin >> n >> m)
	{
		num = 0;
		ans = 0;
		memset(sign,0,sizeof(sign));
		for(i = 0; i < n; i++)
			cin >> ma[i].x >> ma[i].y;
		for(i = 0; i < m; i++)
		{
			cin >> a[i].x >> a[i].y;
			a[i].l = 1000*a[i].x+10*a[i].y;			
		}
		sort(ma,ma+n,cmp);
		sort(a,a+m,cmp);
		for(i=0; i < n; i++)
		{
			j = 0;
			flag = -1;
			mi = 999999999;
			while(ma[j].x>=a[i].x&&j<n)
			{
				if(ma[j].y>=a[i].y&&sign[j]==0&&ma[j].y<=mi)
				{
					mi = ma[j].y;
					flag = j;
				}
				j++;
			}
			if(flag>=0)
			{
				sign[flag] = 1;
				num++;
				ans+=a[i].l;
			}
		}
		cout << num << ' ' << ans << '\n';
	}
	return 0;
}