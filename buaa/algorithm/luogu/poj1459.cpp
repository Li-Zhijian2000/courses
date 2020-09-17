#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=100+9;
struct Edge
{
    int from,to,cap,flow;
};
vector<Edge>edges;
vector<int>G[N];
int d[N]; //从起点到i点的距离
int cur[N]; //当前弧下标
bool vis[N];
int s,t;
bool bfs()
{
    memset(vis,0,sizeof(vis));
    queue<int>q;
    q.push(s);
    d[s]=0;
    vis[s]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=0;i<G[x].size();i++){
            Edge& e=edges[G[x][i]];
            if(!vis[e.to]&&e.cap>e.flow){
                vis[e.to]=1;
                d[e.to]=d[x]+1;
                q.push(e.to);
            }
        }
    }
    return vis[t];
}
int dfs(int x,int a)
{
    if(x==t||a==0)return a;
    int flow=0,f;
    for(int& i=cur[x];i<G[x].size();i++){
        Edge& e=edges[G[x][i]];
        if(d[x]+1==d[e.to]&&(f=dfs(e.to,min(a,e.cap-e.flow)))>0){
            e.flow+=f;
            edges[G[x][i]^1].flow-=f;
            flow+=f;
            a-=f;
            if(a==0)break;
        }
    }
    return flow;
}
int Maxflow()
{
    int flow=0;
    while(bfs()){
        memset(cur,0,sizeof(cur));
        flow+=dfs(s,INF);
    }
    return flow;
}
void addedge(int from,int to,int cap)
{
    edges.push_back((Edge){from,to,cap,0});
    edges.push_back((Edge){to,from,0,0});
    int m=edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
}

int main()
{
    int n,np,nc,m;
	while (~scanf("%d%d%d%d",&n,&np,&nc,&m)){
        s=0,t=n+1;
		int a, b, c;
		for (int i = 0; i <= n+1; i++)
			G[i].clear();
		edges.clear();
		for (int i = 0; i < m; i++) {
                        scanf(" (%d,%d)%d",&a,&b,&c); 
			//cin >> t >> a >> t >> b >> t >> c;
			addedge(a + 1, b + 1, c);
		}
		for (int i = 0; i < np; i++) {
			//cin >> t >> a >> t >> b;
                        scanf(" (%d)%d",&a,&b);
			addedge(s, a + 1, b);
		}
		for (int i = 0; i < nc; i++) {
			//cin >> t >> a >> t >> b;
			 scanf(" (%d)%d",&a,&b);
			addedge(a + 1, t, b);
		}
		printf("%d\n", Maxflow());
	}
	return 0;
}