int phi(int x)
{
	int ans = x;
	for(int i = 2; i*i <= x; i++)
	{
		if(x % i == 0)
		{
			ans = ans / i * (i-1);
			while(x % i == 0) x /= i;
		}
	}
	if(x > 1) ans = ans / x * (x-1);
	return ans;
}
//线性筛
int phi[200005];
int prime[200005];
int is[200005];
int tot=0;
inline void euler(int n)
{
	phi[1] = 1;
	for(int i=2; i<=n; ++i)
	{
		if(!is[i])
		{
			prime[++tot] = i;
			phi[i] = i-1;
		}
		for(int j = 1; j <= tot && (long long)prime[j]*i <= n; ++j)
		{
			is[i*prime[j]] = true;
			if(i%prime[j] == 0)
			{
				phi[i*prime[j]] = phi[i]*prime[j];
				break;
			}
			else phi[i*prime[j]] = phi[i]*phi[prime[j]];
		}
	}
}
