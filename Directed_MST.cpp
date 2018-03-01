const int inf=1e9;
const int maxm=;
const int maxn=;
struct edge
{
	int id;
	int from,to;
	double w;
}e[maxm];
int pre[maxn],id[maxn],vis[maxn],n,m;
double in[maxn];
/*
double value[maxm];//边的原长
int add[maxm*maxn];
int del[maxm*maxn];
int extra;
int used[maxm*maxn];
int preid[maxn];
*/
double Directed_MST(int root,int V,int E)
{
	double ret=0;
	/*
	extra=E;
	*/
	while(1)
	{
		//1.找最小入边
		for(int i=0;i<V;i++) in[i]=inf;
		for(int i=0;i<E;i++)
		{
			int u=e[i].from;
			int v=e[i].to;
			if(e[i].w<in[v]&&u!=v) 
			{
				pre[v]=u;
				in[v]=e[i].w;
				/*
				preid[v]=e[i].id;
				*/
			}
		}
		for(int i=0;i<V;i++)
		{
			if(i==root) continue;
			if(in[i]==inf) return -1;
		}
		//2.找环
		int cnt=0;
		memset(id,-1,sizeof(id));
		memset(vis,-1,sizeof(vis));
		in[root]=0;
		for(int i=0;i<V;i++)
		{
			ret+=in[i];
			int v=i;
			/*
			if(i!=root) used[preid[i]]++;
			*/
			while(vis[v]!=i&&id[v]==-1&&v!=root)
			{
				vis[v]=i;
				v=pre[v];
			}
			if(v!=root&&id[v]==-1)
			{
				for(int u=pre[v];u!=v;u=pre[u]) id[u]=cnt;
				id[v]=cnt++;
			}
		}
		if(cnt==0) break;
		for(int i=0;i<V;i++)
		{
			if(id[i]==-1) id[i]=cnt++;
		}
		//3.建立新图
		for(int i=0;i<E;i++)
		{
			int u=e[i].from;
			int v=e[i].to;
			e[i].from=id[u];
			e[i].to=id[v];
			if(id[u]!=id[v]) 
			{
				e[i].w-=in[v];
				/*
				add[extra]=e[i].id;
              			del[extra]=preid[v];
                		e[i].id=extra;
                		extra++;
				*/
			}			
		}
		V=cnt;
		root=id[root];
	}
	/*
	for(int i=extra-1;i>=E;i--)
    	{
        	if(used[i])
        	{
            		used[add[i]]++;
            		used[del[i]]--;
        	}
    	}
	*/
	return ret;
}
