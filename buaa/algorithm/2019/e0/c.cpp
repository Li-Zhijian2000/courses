// #define local
#include <cstdio>
#include <iostream>
#include <stack>
using namespace std;

const int maxn = 5 * 1e4 + 5;
const int inf = maxn;
int num[maxn];
int low_left[maxn], low_right[maxn];
int high_left[maxn], high_right[maxn];

void calc(int n)
{
    num[0] = num[n+1] = 0;  
    stack<int> s;
    for (int i = 0; i <= n + 1; i++) {
        while (!s.empty() && num[i] <= num[s.top()])
            s.pop();
        if (s.empty()) low_left[i] = -1;
        else low_left[i] = abs(s.top() - i);
        s.push(i);
    }

    while (!s.empty())
        s.pop();    
    for (int i = n + 1; i >= 0; i--) {
        while (!s.empty() && num[i] < num[s.top()])
            s.pop();
        if (s.empty()) low_right[i] = -1;
        else low_right[i] = abs(s.top() - i);
        s.push(i);
    }

    num[0] = num[n+1] = inf;
    while (!s.empty())
        s.pop();
    for (int i = 0; i <= n + 1; i++) {
        while (!s.empty() && num[i] >= num[s.top()])
            s.pop();
        if (s.empty()) high_left[i] = -1;
        else high_left[i] = abs(s.top() - i);
        s.push(i);
    }

    while (!s.empty())
        s.pop();    
    for (int i = n + 1; i >= 0; i--) {
        while (!s.empty() && num[i] > num[s.top()])
            s.pop();
        if (s.empty()) high_right[i] = -1;
        else high_right[i] = abs(s.top() - i);
        s.push(i);
    }
}
void print(int*a, int n)
{
    for (int i = 0; i <= n; i++)
        cout << a[i] << " ";
    cout << endl;
}
int main()
{
#ifdef local
    freopen("c.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> num[i];
    calc(n);
    long long total = 0;
    for (int i = 1; i <= n; i++) {
        long long inc = high_right[i] * high_left[i] - 1;
        long long dec = low_right[i] * low_left[i] - 1;
        total += num[i] * (inc - dec);
    }
    cout << total << endl;
    // print(low_left, n + 1);
    // print(low_right, n + 1);
    // cout << endl;
    // print(high_left, n + 1);
    // print(high_right, n + 1);
    return 0;
}