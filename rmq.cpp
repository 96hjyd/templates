int n,f[20][maxn],a[maxn];
void pre()
{
	for(int i=1;i<=n;i++) f[0][i]=a[i];
	int k=floor(log(n)/log(2));
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n-(1<<i)+1;j++)
		{
			f[i][j]=max(f[i-1][j],f[i-1][j+(1<<(i-1))]);
		}
	}
}
int rmq(int x,int y)
{
	int k=floor(log(y-x+1)/log(2));
	return max(f[k][x],f[k][y-(1<<k)+1]);
}
