#include<cmath>
using namespace std;
int a[200005];
int f1[200005][20]; //最小值数组
int f2[200005][20]; //最大值数组
int n,m;
void rmq_init()
{
	for(int i=1;i<=n;i++)
	{
		f1[i][0]=a[i];
		f2[i][0]=a[i];
	}
	int k=floor(log((double)n)/log(2.0));
	for(int j=1;j<=k;j++)
	{
		for(int i=n;i>=1;i--)
		{
			if(1+(1<<(j-1))<=n)
			{
				f1[i][j]=min(f1[i][j-1],f1[i+(1<<(j-1))][j-1]);
				f2[i][j]=max(f2[i][j-1],f2[i+(1<<(j-1))][j-1]);
			}
		}
	}
}
int rmq(int i,int j) //查询最大值与最小值之差
{
	int k=floor(log(j-i+1)/log(2.0));
	int minnum=min(f1[i][k],f1[j-(1<<k)+1][k]);
	int maxnum=max(f2[i][k],f2[j-(1<<k)+1][k]);
	return maxnum-minnum;
}
