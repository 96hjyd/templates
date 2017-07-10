/*
	计算从1-n范围内的SG值
	Array(存储可以走的步数,Array[0]表示可以有多少种走法)
	Array[]需要从小到大排序
	1.可选步数为1-m的连续整数,直接取模即可,SG(x)=x%(m+1);
	2.可选步数为任意步,SG(x)=x;
	3.可选步数为一系列不连续的数,用GetSG(计算)
 */
int	SG[MAX],hash[MAX];
void init(int Array[],int n)
{
	memset(SG,0,sizeof(SG));
	for(int i=0;i<=n;i++)
	{
		memset(hash,0,sizeof(hash));
		for(int j=1;j<=Array[0];j++)
		{
			if(i<Array[j])
				break;
			hash[SG[i-Array[j]]]=1;
		}
		for(int j=0;j<=n;j++)
		{
			if(hash[j]==0)
			{
				SG[i]=j;
				break;
			}
		}
	}
}
//计算从1-n范围内的SG值
int	s[101],sg[10001];//初始sg为-1;s存储步数,s[0]为走法总数，s[1]到s[s[0]]为可走步数
int	getsg(int m)
{
	int vis[105]; //由于要记忆化搜索，vis要放函数内
	if(sg[m]!=-1) return sg[m];
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=s[0];i++)
	{
		if(m-s[i]<0) break;
		sg[m-s[i]]=getsg(m-s[i]);
		vis[sg[m-s[i]]]=1;
	}
	for(int i=0;;i++)
		if(vis[i]==0)
			return i;
}

