#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 1e5+5;
const int maxm = 2 * maxn;
struct Point{
    int num,comein,sum;
}p[5001];
queue<int>ready;
long long total;
struct Side{int next,to;}s[maxm];
int fr[maxn],tails,n,m,p1,p2,nowuse;
void add(int from,int to){
    s[++tails].to=to;
    s[tails].next=fr[from];
    fr[from]=tails;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d %d",&p1,&p2);
        add(p1,p2);p[p2].comein++;
    }
    for(int i=1;i<=n;i++){
        if(!p[i].comein)p[i].sum=1,ready.push(i);
        p[i].num=i;
    }
    while(!ready.empty()){
        nowuse=ready.front();
        ready.pop();
        int lzh=fr[p[nowuse].num];
        if(!lzh)
            total=(total+p[nowuse].sum);
        for(;lzh;lzh=s[lzh].next){
            p[s[lzh].to].sum=(p[s[lzh].to].sum+p[nowuse].sum);
            if(!(--p[s[lzh].to].comein))
                ready.push(s[lzh].to);
        }
    }
    cout<<total<<'\n';
    return 0;
}