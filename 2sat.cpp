//建图
//缩点
//判可行
//记录矛盾
//反向建图 
//拓扑
//构造方案 
#include<cstdio>
#include<stack>
using namespace std;
const int M=2000010;
const int N=2010;
struct edge{int to,next;}e1[M],e2[M];
int tot,idx1[N],idx2[N];
int low[N],dfn[N];
int belong[N];
int bcnt=0;
bool ins[N];
stack<int>S;
int Time,ans;
void add1(int from,int to){
    e1[tot].to=to;e1[tot].next=idx1[from];idx1[from]=tot++;
}
void add2(int from,int to){
    e2[tot].to=to;e2[tot].next=idx2[from];idx2[from]=tot++;
}
void tarjan(int x){
    dfn[x]=low[x]=++Time;
    S.push(x);ins[x]=1;
    for(int t=idx1[x];t;t=e1[t].next){
        edge e=e1[t];
        if(!dfn[e.to]){
            tarjan(e.to);
            low[x]=min(low[x],low[e.to]);
        }
        else if(ins[e.to])
            low[x]=min(low[x],dfn[e.to]);
    }
    int now;
    if(dfn[x]==low[x]){
        bcnt++;
        do{
            now=S.top();
            S.pop();
            ins[now]=0;
            belong[now]=bcnt;
        }while(now!=x);
        ans++;
    }
}
int a[1005],b[1005],c[1005];
int chudu[2005];
int n;
int fan[2005];
int shunxu[2005];
void topsort(int x)
{
    chudu[x]=-1;
    shunxu[tot++]=x;
    for(int i=idx2[x];i;i=e2[i].next)
    {
        chudu[e2[i].to]--;
        if(chudu[e2[i].to]==0) topsort(e2[i].to);
    }
}
int col[2005];
void dfs(int x)
{
    col[x]=2;
    for(int i=idx2[x];i;i=e2[i].next)
    {
        if(col[e2[i].to]==0) dfs(e2[i].to);
    }
}
void print(int x)
{
    int shi=x/60;
    int fen=x%60;
    if(shi<10) printf("0%d",shi);
    else printf("%d",shi);
    printf(":");
    if(fen<10) printf("0%d",fen);
    else printf("%d",fen);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int dd1,dd2;
        scanf("%d:%d",&dd1,&dd2);
        a[i]=dd1*60+dd2;
        scanf("%d:%d",&dd1,&dd2);
        b[i]=dd1*60+dd2;
        scanf("%d",&c[i]);
    }
    tot=1;
    //建图 
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            if(a[i]+c[i]<=a[j]||a[i]>=a[j]+c[j]) ;
            else {add1(i,j+n);add1(j,i+n);}
            if(a[i]+c[i]<=b[j]-c[j]||a[i]>=b[j]) ;
            else {add1(i,j);add1(j+n,i+n);}
            if(b[i]<=a[j]||a[j]+c[j]<=b[i]-c[i]) ;
            else {add1(i+n,j+n);add1(j,i);}
            if(b[i]<=b[j]-c[j]||b[j]<=b[i]-c[i]) ;
            else {add1(i+n,j);add1(j+n,i);}
        }
    }
    //缩点
    for(int i=1;i<=2*n;i++)
    {
        if(dfn[i]==0) tarjan(i);
    }
    //判可行
    for(int i=1;i<=n;i++)
    {
        if(belong[i]==belong[i+n])
        {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    //矛盾块
    for(int i=1;i<=n;i++)
    {
        fan[belong[i]]=belong[i+n];
        fan[belong[i+n]]=belong[i];
    }
	//反向 
    tot=1;
    for(int i=1;i<=2*n;i++)
    {
        for(int j=idx1[i];j;j=e1[j].next)
        {
            int k=e1[j].to;
            if(belong[i]!=belong[k])
            {
                add2(belong[k],belong[i]);
                chudu[belong[i]]++;
            }
        }
    }
    //拓扑  
    tot=0;
    for(int i=1;i<=bcnt;i++)
    {
        if(chudu[i]==0) topsort(i);
    }
    //构造方案 
    for(int i=0;i<bcnt;i++)
    {
        if(col[shunxu[i]]==0)
        {
            col[shunxu[i]]=1;
            dfs(fan[shunxu[i]]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        int s,t;
        if(col[belong[i]]==1)
        {
            s=a[i];
            t=a[i]+c[i];
        }
        else
        {
            s=b[i]-c[i];
            t=b[i];
        }
        print(s);
        printf(" ");
        print(t);
        printf("\n");
    }
    return 0;
}
