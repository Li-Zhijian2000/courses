#include<bits/stdc++.h>
using namespace std;
int n,m,k,r,i,j,x[11],point[11],t[11],s,f[51];
int main() 
{   cin>>n>>m>>k>>r;
    for(i=1;i<=n;i++)
        cin>>x[i];
    for(i=1;i<=m;i++)
        cin>>t[i];
    for(i=1;i<=m;i++)
        cin>>point[i];//输入部分
    sort(x+1,x+n+1);//排序，为下面做用时少的题目预处理
    for(i=1;i<=k;i++) 
        f[i]=66666666;//要求为最小值，先赋值为用时无限大
    for(i=1;i<=m;i++)
        for(j=k;j>=point[i];j--)
            f[j]=min(f[j],f[j-point[i]]+t[i]);
    //01背包，对于这道题做或不做作抉择
    for (int i = 0; i <= k; i++) {
        cout << f[i] << " ";
    }
    cout << endl;
    r-=f[k];//真正刷题的时间为原先时间减去做作业最短用时
    i=0;
    while(r>=x[++i]&&i<=n){
        r-=x[i];
        s++;
    }//从用时短的题开始循环，直到没时间或所有题都做完了
    cout<<s;//输出
    return 0;
}
// // #define local
// #include <iostream>
// #include <algorithm>
// #include <cstring>
// using namespace std;

// const long max_cost = 20005;
// const long maxn = 15;
// long dp[max_cost], ques_cost[maxn], hw_cost[maxn], weight[maxn];

// int main()
// {
// #ifdef local
//     freopen("p1926.txt", "r", stdin);
// #endif

//     long n, m, k, r, total_w = 0, total_c = 0;
//     cin >> n >> m >> k >> r;
//     for (int i = 1; i <= n; i++) {
//         cin >> ques_cost[i];
//     }
//     for (int i = 1; i <= m ;i++) {
//         cin >> weight[i];
//         total_w += weight[i];
//     }
//     for (int i = 1; i <= m; i++) {
//         cin >> hw_cost[i];
//         total_c += hw_cost[i];
//     }
//     for (int i = 0; i <= total_c; i++) {
//         dp[i] = total_w;
//     }

//     for (int i = 1; i <= m; i++) {
//         for (long c = k; c <= total_c - hw_cost[i]; c++) {
//             dp[c] = min(dp[c], dp[c + hw_cost[i]] - weight[i]);
//         }
//     }

//     // 应用贪心，先做用时少的题目
//     r -= dp[k];
//     memset(dp, 0, sizeof(dp));
//     for (int i = 1; i <= n; i++) {
//         for (long c = r; c >= ques_cost[i]; c--) {
//             dp[c] = max(dp[c], dp[c - ques_cost[i]] + 1);
//         }
//     }
//     cout << dp[r] << endl;
//     return 0;
// }