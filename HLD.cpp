//SPOJ375 QTREE 基于边的重编号
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 10005
#define lson rt<<1,left,mid
#define rson rt<<1|1,mid+1,right
struct edge{int to,next,w;}e[maxn*2];
int idx[maxn],fa[maxn],size[maxn],dep[maxn],son[maxn],tree[maxn<<2],d[maxn][3],top[maxn],w[maxn];
int num,n,root,totw;
char s[100];
void add(int a,int b,int c)
{
    e[num].to=b;
    e[num].next=idx[a];
    e[num].w=c;
    idx[a]=num++;
}
void dfs(int x)
{
    size[x]=1;
    son[x]=0;
    for(int i=idx[x];i;i=e[i].next)
    {
        if(e[i].to!=fa[x])
        {
            fa[e[i].to]=x;
            dep[e[i].to]=dep[x]+1;
            dfs(e[i].to);
            if(size[e[i].to]>size[son[x]]) son[x]=e[i].to;
            size[x]+=size[e[i].to];
        }
    }
}
void build_tree(int x,int tp)
{
    w[x]=++totw;
    top[x]=tp;
    if(son[x]) build_tree(son[x],tp);
    for(int i=idx[x];i;i=e[i].next)
    {
        if(e[i].to!=son[x]&&e[i].to!=fa[x])
            build_tree(e[i].to,e[i].to);
    }
}
void update(int rt,int left,int right,int loc,int x)
{
    if(loc>right||loc<left) return ;
    if(left==right) {tree[rt]=x;return ;}
    int mid=(left+right)>>1;
    update(lson,loc,x);update(rson,loc,x);
    tree[rt]=max(tree[rt<<1],tree[rt<<1|1]);
}
int maxi(int rt,int left,int right,int l,int r)
{
    if(l>right||r<left) return 0;
    if(l<=left&&right<=r) return tree[rt];
    int mid=(left+right)>>1;
    return max(maxi(lson,l,r),maxi(rson,l,r));
}
int find(int va,int vb)
{
    int f1=top[va];
    int f2=top[vb];
    int ret=0;
    while(f1!=f2)
    {
        if(dep[f1]<dep[f2])
        {
            swap(f1,f2);
            swap(va,vb);
        }
        ret=max(ret,maxi(1,1,totw,w[f1],w[va]));
        va=fa[f1];
        f1=top[va];
    }
    if(va==vb) return ret;
    if(dep[va]>dep[vb]) swap(va,vb);
    return max(ret,maxi(1,1,totw,w[son[va]],w[vb]));
}
int main()
{
    int kase;
    scanf("%d",&kase);
    while(kase--)
    {
        scanf("%d",&n);
        root=(n+1)/2;
        fa[root]=totw=dep[root]=0;
        num=1;
        memset(size,0,sizeof(size));
        memset(idx,0,sizeof(idx));
        memset(tree,0,sizeof(tree));
        for(int i=1;i<n;i++)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            d[i][0]=a,d[i][1]=b,d[i][2]=c;
            add(a,b,c);
            add(b,a,c);
        }
        dfs(root);
        build_tree(root,root);
        for(int i=1;i<n;i++)
        {
            if(dep[d[i][0]]>dep[d[i][1]]) swap(d[i][0],d[i][1]);
            update(1,1,totw,w[d[i][1]],d[i][2]);
        }
        while(1)
        {
            scanf("%s",s);
            if(s[0]=='D') break;
            else if(s[0]=='C')
            {
                int a,b;
                scanf("%d%d",&a,&b);
                update(1,1,totw,w[d[a][1]],b);
            }
            else if(s[0]=='Q')
            {
                int a,b;
                scanf("%d%d",&a,&b);
                printf("%d\n",find(a,b));
            }
        }
        if(kase!=0) printf("\n");
    }
    return 0;
}
