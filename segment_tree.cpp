//无修改的区间第K小
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100005;
int n,m;
int b[maxn],sortb[maxn],rt[maxn];
int cur=0,cnt=1;
struct node{int ch[2],value;}nd[maxn<<6];
void pushup(int rt) {nd[rt].value=nd[nd[rt].ch[0]].value+nd[nd[rt].ch[1]].value;}
int build(int l,int r)
{
	int k=++cur;
	if(l==r)
	{
		nd[k]=nd[0];
		return k;
	}
	int mid=(l+r)>>1;
	nd[k].ch[0]=build(l,mid);
	nd[k].ch[1]=build(mid+1,r);
	pushup(k);
	return k;
}
int update(int o,int l,int r,int p,int add)
{
	int k=++cur;
	nd[k]=nd[o];
	if(l==r) 
	{
		nd[k].value+=add;
		return k;
	}
	int mid=(l+r)>>1;
	if(p<=mid) nd[k].ch[0]=update(nd[o].ch[0],l,mid,p,add);
	else nd[k].ch[1]=update(nd[o].ch[1],mid+1,r,p,add);
	pushup(k);
	return k;
}
int query(int l,int r,int rt1,int rt2,int k)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	int res=nd[nd[rt2].ch[0]].value-nd[nd[rt1].ch[0]].value;
	if(res>=k) return query(l,mid,nd[rt1].ch[0],nd[rt2].ch[0],k);
	else return query(mid+1,r,nd[rt1].ch[1],nd[rt2].ch[1],k-res);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		sortb[i]=b[i];
	}
	sort(sortb+1,sortb+n+1);
	cnt=unique(sortb+1,sortb+1+n)-sortb-1;
	rt[0]=build(1,cnt);
	for(int i=1;i<=n;i++)
	{
		int p=lower_bound(sortb+1,sortb+cnt+1,b[i])-sortb;
		rt[i]=update(rt[i-1],1,cnt,p,1);
	}
	for(int i=1;i<=m;i++)
	{
		int x1,x2,k;
		scanf("%d%d%d",&x1,&x2,&k);
		int idx=query(1,cnt,rt[x1-1],rt[x2],k);
		printf("%d\n",sortb[idx]);
	}
	return 0;
}
