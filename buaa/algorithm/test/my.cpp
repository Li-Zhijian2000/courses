#include <iostream>
#include <cstring>

using namespace std;
typedef pair<int,int> filter;
int t,n,k;
long long count;
filter fil[11];

void search(char* ,int);

int main()
{
	int i,j,seat1,num1,seat2,num2;
	char ao[51];
	cin >> t;
	while(t--)
	{
		cin >> n >> k;
		count = 0;
		if(n == 2)
		{
			count = 2;
		}
		else if(k == 0)
		{
			count = (n-1)*(n-1)+1;
		}
		else
		{
			for(i = 0; i < k; i++)
			{
				cin >> fil[i].first >> fil[i].second;
			}
			for(i = 0; i < n; i++)
			{
				ao[i] = i+65;
			}
			ao[n] = 0;
			search(ao,k-1);
			for(num1 = 1; num1 <= n; num1++)
			{
				for(seat1 = 0; seat1 < n; seat1++)
				{
					if(num1==seat1+1||num1==seat1+2)
						continue;
					ao[seat1] = num1+65;
					num2=1; 
					seat2=0;
					while(seat2 < n)
					{
						if(num2==num1)
						{
							num2++;
							continue;
						}
						if(seat2==seat1)
						{
							seat2++;
							continue;
						}
						ao[seat2] = num2+65;
						seat2++;
						num2++;
					}
					search(ao,k-1);
				}
			}
		}
	cout << count << '\n';
	}
	cout << endl;
	return 0;
} 

void search(char* xo,int i)
{
	char temp[51],Temp;
	if(xo[fil[i].first-1]>xo[fil[i].second-1])
		return;
	else
	{
		strcpy(temp,xo);
		Temp = temp[fil[i].first-1];
		temp[fil[i].first-1] = temp[fil[i].second-1];
		temp[fil[i].second-1] = Temp;
		if(i==0)
		{
			count+=2;
		}
		else
		{	
			search(temp,i-1);
			search(xo,i-1);
		} 
	}
}
