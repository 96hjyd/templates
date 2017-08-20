struct edge{
	int to,next,v;
}e[100010];

int head[N<<1],ne=1,q[N<<1],h[N<<1],ans=0,n,S,T;

inline void ins(int u,int v,int f){
	ne++;
	e[ne].to=v;
	e[ne].next=head[u];
	e[ne].v=f;
	head[u]=ne;
}

inline void insert(int u,int v,int f){
	ins(u,v,f);ins(v,u,0);
}

bool bfs(){
	int t=0,w=1;
	memset(h,-1,sizeof(h));
	q[t]=S;h[S]=0;
	while(t<w){
		int now=q[t++];
		for(int i=head[now];i;i=e[i].next){
			int v=e[i].to;
			if(h[v]==-1&&e[i].v){
				h[v]=h[now]+1;
				q[w++]=v;
			}
		}
	}
	if(h[T]!=-1) return 1;
	return 0;
}

int dfs(int x,int f){
	if(x==T) return f;
	int w,used=0;
	for(int i=head[x];i;i=e[i].next){
		int v=e[i].to;
		if(h[v]==h[x]+1){
			w=dfs(v,min(f-used,e[i].v));
			e[i].v-=w;
			e[i^1].v+=w;
			used+=w;
			if(used==f) return f;
		}
	}
	if(!used) h[x]=-1;
	return used;
}

void dinic(){
	while(bfs())
		ans+=dfs(S,inf);
}
