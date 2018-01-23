//bzoj1010
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long sum[50005]; //前缀和
int q[50005]; //队列
long long dp[50005];
int head=0,tail=0;
int n,m;
long long f(int i,int j) //转移函数
{
	return dp[j]+(i+sum[i]-j-sum[j]-m-1)*(i+sum[i]-j-sum[j]-m-1);
}
long long up(int i,int j) //分子 
{
	return dp[i]+(i+sum[i])*(i+sum[i])-dp[j]-(j+sum[j])*(j+sum[j]);
}
long long down(int i,int j) //分母 
{
	return 2*(i+sum[i]-sum[j]-j);
}
int main()
{
	scanf("%d%d",&n,&m);
	head=tail=0;
	q[tail++]=0;
	memset(dp,0,sizeof(dp));
	memset(sum,0,sizeof(sum));
	for(int i=1; i<=n; i++) scanf("%lld",&sum[i]);
	for(int i=1; i<=n; i++) sum[i]+=sum[i-1];
	for(int i=1; i<=n; i++)
	{
		while(head+1<tail&&up(q[head+1],q[head])<=(i+sum[i]-m)*down(q[head+1],q[head]))
			head++;
		dp[i]=f(i,q[head]);
		while(head+1<tail&&up(i,q[tail-1])*down(q[tail-1],q[tail-2])<=up(q[tail-1],q[tail-2])*down(i,q[tail-1]))
			tail--;
		q[tail++]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
