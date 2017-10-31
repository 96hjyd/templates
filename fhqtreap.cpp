#include <cstdio>
#include <cstdlib>
#define N 100005
using namespace std;
int ch[N][2],val[N],pri[N],siz[N],sz=0;
void update(int x)
{
	siz[x]=1+siz[ch[x][0]]+siz[ch[x][1]];
}
int new_node(int v)
{
	siz[++sz]=1;
	val[sz]=v; //值
	pri[sz]=rand(); //优先级
	return sz;
}
int merge(int x,int y)
{
	if (!x || !y) return x+y;
	if (pri[x]<pri[y])
	{
		ch[x][1]=merge(ch[x][1],y);
		update(x);
		return x;
	}
	else
	{
		ch[y][0]=merge(x,ch[y][0]);
		update(y);
		return y;
	}
}
void split1(int now,int k,int &x,int &y) //按照权值分配
{
	if (!now) x=y=0;
	else
	{
		if (val[now]<=k)
			x=now,split1(ch[now][1],k,ch[now][1],y);
		else
			y=now,split1(ch[now][0],k,x,ch[now][0]);
		update(now);
	}
}
void split2(int now,int k,int &x,int &y) //按前k个分配
{
	if (!now) x=y=0;
	else
	{
		if (k<=siz[ch[now][0]])
			y=now,split2(ch[now][0],k,x,ch[now][0]);
		else
			x=now,split2(ch[now][1],k-siz[ch[now][0]]-1,ch[now][1],y);
		update(now);
	}
}
int kth(int now,int k) //第k大
{
	while(1)
	{
		if (k<=siz[ch[now][0]])
			now=ch[now][0];
		else if (k==siz[ch[now][0]]+1)
			return now;
		else
			k-=siz[ch[now][0]]+1,now=ch[now][1];
	}
}
int main()
{
    srand(unsigned((long long)new char));
    return 0;
}
