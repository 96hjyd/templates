int lowbit(int x)
{
	return x&(-x);
}
void modify(int	x,int add)//一维
{		
	while(x<=MAXN)		
	{						
		a[x]+=add;				
		x+=lowbit(x);
	}
}
int get_sum(int	x)
{		
	int	ret=0;
	while(x!=0)		
	{							
		ret+=a[x];			
		x-=lowbit(x);			
	}		
	return	ret;
}
void modify(int	x,int y,int data)//二维
{
	for(int	i=x;i<=MAXN;i+=lowbit(i))
		for(int	j=y;j<=MAXN;j+=lowbit(j))
			a[i][j]+=data;
}
int get_sum(int x,int y)
{
	int res=0;
	for(int	i=x;i>0;i-=lowbit(i))
		for(int	j=y;j>0;j-=lowbit(j))
			res+=a[i][j];
	return res;
}
