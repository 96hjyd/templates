#include<cstdio>
#include<stack>
using namespace std;
const int M=500010;
const int N=100010;
struct E {int to,nxt;}edge[M];
int tot=1,idx[N];
int low[N],dfn[N];
int belong[N];
int bcnt=0;
bool ins[N];
stack<int>S;
int Time,ans;
int n,m;
void addedge(int from,int to){
    edge[tot].to=to;edge[tot].nxt=idx[from];idx[from]=tot++;
}
void dfs(int x){
    dfn[x]=low[x]=++Time;
    S.push(x);ins[x]=1;
    for(int t=idx[x];t;t=edge[t].nxt){
        E e=edge[t];
        if(!dfn[e.to]){
            dfs(e.to);
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
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        addedge(x,y);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) dfs(i);
    for(int i=1;i<=n;i++)
    {       
        printf("belong[%d]=%d\n",i,belong[i]);
    }   
    printf("%d\n",ans);
    return 0;
}
