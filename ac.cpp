int sz;
int ch[1000000][26],last[1000000],f[1000000],val[1000000];
void init()
{
	sz=0;
	memset(ch,0,sizeof(ch));
	memset(last,0,sizeof(last));
	memset(f,0,sizeof(f));
	memset(val,0,sizeof(val));
}
void insert(char* t,int p)
{
	int len=strlen(t);
	int x=0;
	for(int i=0; i<len; i++)
	{
		int y=t[i]-'a';
		if(!ch[x][y]) ch[x][y]=++sz;
		x=ch[x][y];
	}
	val[x]=p;
}
void getfail()
{
	f[0]=0;
	queue<int> q;
	for(int i=0; i<26; i++)
	{
		if(ch[0][i])
		{
			q.push(ch[0][i]);
		}
	}
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=0; i<26; i++)
		{
			int y=ch[x][i];
			if(!ch[x][i])
			{
				ch[x][i]=ch[f[x]][i];
				continue;
			}
			q.push(y);
			f[y]=ch[f[x]][i];
			last[y]=val[f[y]]?f[y]:last[f[y]];
		}
	}
}
void print(int x)
{
	while(x)
	{
		// pass
		x=last[x];
	}
}
void find(char *s)
{
	int x=0;
	int len=strlen(s);
	for(int i=0; i<len; i++)
	{
		int y=s[i]-'a';
		x=ch[x][y];
		if(val[x]) print(x);
		else if(last[x]) print(last[x]);
	}
}
