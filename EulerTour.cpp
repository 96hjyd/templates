//uoj117
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5,maxm=4e5+5;
int dd1,dd2,opt,n,m,top,ans[maxm],in[maxn],out[maxn],idx[maxn];
bool vis[maxm];
struct edge
{
	int to,next,id;
} e[maxm];
void add(int a,int b,int id)
{
	e[++top].to=b;
	e[top].next=idx[a];
	e[top].id=id;
	idx[a]=top;
	out[a]++;
	in[b]++;
}
void dfs(int x)
{
	for(int i=idx[x]; i; i=idx[x])
	{
		for(; i&&vis[abs(e[i].id)]; i=e[i].next);
		idx[x]=e[i].next;
		if(i)
		{
			vis[abs(e[i].id)]=1;
			dfs(e[i].to);
			ans[++top]=e[i].id;
		}
	}
}
int main()
{
	scanf("%d%d%d",&opt,&n,&m);
	for(int i=1; i<=m; i++)
	{
		if(scanf("%d%d",&dd1,&dd2),add(dd1,dd2,i),opt==1) add(dd2,dd1,-i);
	}
	for(int i=1; i<=n; i++)
	{
		if((opt==1&&in[i]%2)||(opt==2&&in[i]^out[i])) return printf("NO\n")*0;
	}
	top=0,dfs(e[1].to);
	if(top!=m) return printf("NO\n")*0;
	for(printf("YES\n"); top; printf("%d ",ans[top--])) ;
	return 0;
}
