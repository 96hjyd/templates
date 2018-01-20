#define MAXN 100005
struct Node
{
	int l,r,d,k,fa;
} node[MAXN];
int cnt;
void init()
{
	memset(node,0,sizeof(node));
	cnt=0;
	node[0].d=-1;
}
int find(int x)
{
	while(node[x].fa) x=node[x].fa;
	return x;
}
int merge(int x,int y)
{
	if (x==0||y==0) return x+y;
	if (node[x].k>node[y].k||(node[x].k==node[y].k&&x>y)) swap(x,y);//小根堆
	node[x].r=merge(node[x].r,y);
	node[node[x].r].fa=x;
	if (node[node[x].r].d>node[node[x].l].d)
		swap(node[x].l,node[x].r);
	node[x].d=node[node[x].r].d+1;
	return x;
}
int pop(int x)
{
	int ret=node[x].k;
	node[x].k=-1;
	node[node[x].l].fa=node[node[x].r].fa=0;
	merge(node[x].l,node[x].r);
	node[x].fa=node[x].l=node[x].r=0;
	return ret;
}
int mk(int d)
{
	cnt++;
	node[cnt].k=d;
	return cnt;
}
int ins(int r,int x)
{
	int t=mk(x);
	return merge(r,t);
}
int build(int n)
{
	queue<int> q;
	for (int i=1; i<=n;i++)
		q.push(i);
	while(q.size()>1)
	{
		int x=q.front();
		q.pop();
		int y=q.front();
		q.pop();
		int z=merge(x,y);
		q.push(z);
	}
	return q.front();
}
void del(int x)
{
	int q=node[x].fa;
	int p=merge(node[x].l,node[x].r);
	node[p].fa=q;
	if (q&&node[q].l==x) node[q].l=p;
	if (q&&node[q].r==x) node[q].r=p;
	while (q)
	{
		if (node[node[q].l].d<node[node[q].r].d)
			swap(node[q].l,node[q].r);
		if (node[node[q].r].d+1==node[q].d)
			return;
		node[q].d=node[node[q].r].d+1;
		p=q;
		q=node[q].fa;
	}
}
