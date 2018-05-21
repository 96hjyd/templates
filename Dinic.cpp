#include<bits/stdc++.h>
using namespace std;
const int maxn=10005,maxm=100005,inf=INT_MAX;
int n,m,s,t,idx[maxn],cur[maxn],d[maxn],top=1,ans,q[maxn];
struct edge
{
	int to,next,w;
} e[maxm<<1];
void add(int x,int y,int w)
{
	e[++top].to=y;
	e[top].next=idx[x];
	e[top].w=w;
	idx[x]=top;
}
bool bfs()
{
	for(int i=1; i<=n; i++) cur[i]=idx[i];
	memset(d,0x3f,sizeof(d));
	int head=0,tail=0;
	q[tail++]=s;
	d[s]=0;
	while(head<tail)
	{
		int x=q[head++];
		for(int i=idx[x]; i; i=e[i].next)
		{
			int to=e[i].to;
			if(d[x]+1<d[to]&&e[i].w)
			{
				d[to]=d[x]+1;
				q[tail++]=to;
			}
		}
	}
	return d[t]<=n;
}
int dfs(int x,int lim)
{
	if(lim==0||x==t) return lim;
	int flow=0,f;
	for(int i=cur[x]; i; i=e[i].next)
	{
		cur[x]=i;
		int to=e[i].to;
		if(d[to]==d[x]+1&&(f=dfs(to,min(lim,e[i].w))))
		{
			flow+=f;
			lim-=f;
			e[i].w-=f;
			e[i^1].w+=f;
			if(lim==0) break;
		}
	}
	return flow;
}
void dinic()
{
	while(bfs())
	{
		ans+=dfs(s,inf);
	}
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1; i<=m; i++)
	{
		int from,to,cap;
		scanf("%d%d%d",&from,&to,&cap);
		add(from,to,cap);
		add(to,from,0);
	}
	dinic();
	printf("%d\n",ans);
	return 0;
}
