//查找[a,b]上查找第k大/小的元素
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=100005;
struct P_Tree
{
	int n,order[N];
	int valu[20][N],num[20][N];
	void init(int len)
	{
		n=len;
		for(int i=0;i<20;i++)
		{
			valu[i][0]=num[i][0]=0;
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&order[i]);
			valu[0][i]=order[i];
		}
		sort(order+1,order+1+n);
		build(1,n,0);
	}
	void build(int lft,int rht,int ind)
	{
		if(lft==rht) return ;
		int mid=(lft+rht)>>1;
		int same=mid-lft+1,ln=lft,rn=mid+1;
		for(int i=lft;i<=rht;i++)
		{
			if(valu[ind][i]<order[mid]) same--;
		}
		for(int i=lft;i<=rht;i++)
		{
			int flag=0;
			if(valu[ind][i]<order[mid]||(same&&valu[ind][i]==order[mid]))
			{
				flag=1;
				valu[ind+1][ln++]=valu[ind][i];
				if(valu[ind][i]==order[mid]) same--;
			}
			else
			{
				valu[ind+1][rn++]=valu[ind][i];
			}
			num[ind][i]=num[ind][i-1]+flag;
		}
		build(lft,mid,ind+1);
		build(mid+1,rht,ind+1);
	}
	int query(int st,int ed,int k,int lft,int rht,int ind)
	{
		if(lft==rht) return valu[ind][lft];
		int mid=(lft+rht)>>1;
		int lx=num[ind][st-1]-num[ind][lft-1];
		int ly=num[ind][ed]-num[ind][st-1];
		int rx=st-lft-lx;
		int ry=ed-st+1-ly;
		if(ly>=k) return query(lft+lx,lft+lx+ly-1,k,lft,mid,ind+1);
		else
		{
			st=mid+1+rx;
			ed=mid+rx+ry;
			return query(st,ed,k-ly,mid+1,rht,ind+1);
		}
	}
}tree;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	tree.init(n);
	for(int i=0;i<m;i++)
	{
		int a,b,k;
		scanf("%d%d%d",&a,&b,&k);
		printf("%d\n",tree.query(a,b,k,1,n,0));
	}
	return 0;
}
