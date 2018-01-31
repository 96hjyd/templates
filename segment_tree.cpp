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

//有修改区间第k小 
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=50005,maxm=10005;
int n,m,cnt=0,cur=0;
int b[maxn]; 
int sortb[maxn+maxm];
int rt[maxn+maxm];
int p[maxn+maxm]; //树状数组 
int ll[maxn+maxm];
int rr[maxn+maxm];
struct qq
{
	int sign,l,r,k;
} q[maxm];
struct node
{
	int ch[2],value;
} nd[(maxn+maxm)<<5];
int build(int l,int r)
{
	int k=++cur;
	nd[k].value=0;
	if(l==r)
	{
		nd[k]=nd[0];
		return k;
	}
	int mid=(l+r)>>1;
	nd[k].ch[0]=build(l,mid);
	nd[k].ch[1]=build(mid+1,r);
	return k;
}
int insert(int prt,int pos,int add)
{
	int l=1,r=cnt,nrt=++cur,ret=nrt;
	nd[nrt].value=nd[prt].value+add;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			nd[nrt].ch[0]=++cur;
			nd[nrt].ch[1]=nd[prt].ch[1];
			prt=nd[prt].ch[0];
			nrt=nd[nrt].ch[0];
			r=mid;
		}
		else
		{
			nd[nrt].ch[1]=++cur;
			nd[nrt].ch[0]=nd[prt].ch[0];
			prt=nd[prt].ch[1];
			nrt=nd[nrt].ch[1];
			l=mid+1;
		}
		nd[nrt].value=nd[prt].value+add;
	}
	return ret;
}
int lowbit(int x) {return x&(-x);}
void update(int x,int pos,int add)
{
	while(x<=cnt)
	{
		p[x]=insert(p[x],pos,add);
		x+=lowbit(x);
	}
}
int sum(int x,int *use)
{
	int ret=0;
	while(x)
	{
		ret+=nd[nd[use[x]].ch[0]].value;
		x-=lowbit(x);
	}
	return ret;
}
int query(int L,int R,int k)
{
	int l=1,r=cnt,lrt=rt[L-1],rrt=rt[R];
	for(int i=L-1;i;i-=lowbit(i)) ll[i]=p[i];
	for(int i=R;i;i-=lowbit(i)) rr[i]=p[i];
	while(l<r)
	{
		int mid=(l+r)>>1;
		int temp=sum(R,rr)-sum(L-1,ll)+nd[nd[rrt].ch[0]].value-nd[nd[lrt].ch[0]].value;
		if(temp>=k)
		{
			r=mid;
			lrt=nd[lrt].ch[0];
			rrt=nd[rrt].ch[0];
			for(int i=L-1;i;i-=lowbit(i)) ll[i]=nd[ll[i]].ch[0];
			for(int i=R;i;i-=lowbit(i)) rr[i]=nd[rr[i]].ch[0];
		}
		else
		{
			l=mid+1;
			k=k-temp;
			lrt=nd[lrt].ch[1];
			rrt=nd[rrt].ch[1];
			for(int i=L-1;i;i-=lowbit(i)) ll[i]=nd[ll[i]].ch[1];
			for(int i=R;i;i-=lowbit(i)) rr[i]=nd[rr[i]].ch[1];
		}
	}
	return l;
}
int main()
{
	int kase;
	scanf("%d",&kase);
	while(kase--)
	{
		cnt=cur=0;
		memset(rt,0,sizeof(rt));
		memset(p,0,sizeof(p));
		scanf("%d%d",&n,&m);
		for(int i=1; i<=n; i++) scanf("%d",&b[i]);
		for(int i=1; i<=n; i++) sortb[++cnt]=b[i];
		for(int i=1; i<=m; i++)
		{
			char s[2];
			scanf("%s",s);
			if(s[0]=='Q')
			{
				q[i].sign=1;
				scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k);
			}
			if(s[0]=='C')
			{
				q[i].sign=2;
				scanf("%d%d",&q[i].l,&q[i].r);
				sortb[++cnt]=q[i].r;
			}
		}
		sort(sortb+1,sortb+1+cnt);
		cnt=unique(sortb+1,sortb+1+cnt)-sortb-1;
		rt[0]=build(1,cnt);
		for(int i=1; i<=n; i++)
		{
			int pos=lower_bound(sortb+1,sortb+cnt+1,b[i])-sortb;
			rt[i]=insert(rt[i-1],pos,1);
		}
		for(int i=1; i<=cnt; i++)
		{
			p[i]=rt[0];
		}
		for(int i=1; i<=m; i++)
		{
			if(q[i].sign==1)
			{
				printf("%d\n",sortb[query(q[i].l,q[i].r,q[i].k)]);
			}
			else
			{
				int pos=lower_bound(sortb+1,sortb+cnt+1,b[q[i].l])-sortb;
				update(q[i].l,pos,-1);
				pos=lower_bound(sortb+1,sortb+cnt+1,q[i].r)-sortb;
				update(q[i].l,pos,1);
				b[q[i].l]=q[i].r;
			}
		}
	}
	return 0;
}
