#include<stdio.h>
#include<stdlib.h>
#define MAX 110
int pointnum,edgenum,deletepoint;
int Dvisited[MAX]={0},Bvisited[MAX]={0};
typedef struct edge{
	int bianjiedian;//��Ŷ�Ӧ�߽������ 
	struct edge *next;
}Elink;
typedef struct ver{
	int dingdian;
	Elink *link;
}Vlink;
Vlink G[MAX];
Elink *insertEdge(Elink *head,int avex);
void createGraph(Vlink graph[],int n);
void travelDFS(Vlink G[],int n);
void DFS(Vlink G[],int v);
int main()
{
	Elink *p;
	int i;
	scanf("%d%d",&pointnum,&edgenum);
	for(i=0;i<pointnum;i++)
	{
		G[i].dingdian=i;
		G[i].link=NULL;
	}
	createGraph(G,edgenum);
	scanf("%d",&deletepoint);
	
	//travelDFS(G,pointnum);
	printf("\n");
	for(i=0;i<pointnum;i++)
	{
		printf("%d",G[i].dingdian);
		for(p=G[i].link;p->next!=NULL;p=p->next)
			printf("%d",p->bianjiedian);
		printf("\n");
	}
	//travelBFS(G,pointnum);
	
	return 0;
}
Elink *insertEdge(Elink *head,int avex)
{
	Elink *e,*p;
	e=(Elink *)malloc(sizeof(Elink));
	e->bianjiedian=avex;
	e->next=NULL;
	if(head==NULL)
	{
		head=e;
		return head;
	}
	for(p=head;p->next!=NULL;p=p->next)
		p->next=e;
	return head;
}
void createGraph(Vlink graph[],int n)
{
	int i,v1,v2;
	for(i=0;i<n;i++)
	{
		scanf("%d %d",&v1,&v2);
		graph[v1].link=insertEdge(graph[v1].link,v2);
		graph[v2].link=insertEdge(graph[v2].link,v1);
	}
}
void travelDFS(Vlink G[],int n)
{
	int i;
	for(i=0;i<n;i++)
		Dvisited[i]=0;
	for(i=0;i<n;i++)
		if(Dvisited[i]==0)
			DFS(G,i);
}
void DFS(Vlink G[],int v)
{
	Elink *p;
	Dvisited[v]=1;
	printf("%d ",G[v].dingdian);
	for(p=G[v].link;p!=NULL;p=p->next)
		if(Dvisited[p->bianjiedian]==0)
			DFS(G,p->bianjiedian);
}
