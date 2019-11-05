#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
long long flit[11][2], n, k;
long long num = 0;
void find(char *x, long long i)
{
	if(x[flit[i][0] - 1] > x[flit[i][1] - 1])
		return;
	char y[51], temp;
	strcpy(y, x);
	temp = y[flit[i][0] - 1];
	y[flit[i][0] - 1] = y[flit[i][1] - 1];
	y[flit[i][1] - 1] = temp;
	if(i + 1 == k)
		num += 2;
	else
	{
		find(x, i + 1);
		find(y, i + 1);
	}
}
int main()
{
	long long i, a, b, c, d, j, t;
	char x[51];
	
	cin >> t;
	while(t--)
	{
		cin >> n >> k;
		for(j = k - 1; j >= 0; j--)
			cin >> flit[j][0] >> flit[j][1];
		if(n == 2)
			num = 2;
		else
			if(k == 0)
				num = (n - 1) * (n - 1) + 1;
			else
			{
				for(i = 1; i <= n; i++)
					x[i - 1] = i + 65;
				x[n] = '\0';
				find(x, 0);
				for(a = 1; a <= n; a++)
					for(b = 0; b < n; b++)
					{
						if(b == a - 1 || b == a - 2)
							continue;
						x[b] = a + 65;
						for(c = 0, d = 1; c < n; )
						{
							if(c == b)
							{
								c++;
								continue;
							}
							if(d == a)
							{
								d++;
								continue;
							}
							x[c++] = d + 65;
							d++;
						}
						find(x, 0);
					}
		}
		cout << num << endl;
		num = 0;
	}
	
	return 0;
}


