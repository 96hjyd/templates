//倍增（O(nlogn)~O(logn)，在线）
#include <iostream>
#include <cstdio>
using namespace std;
#define dbg(x) cout << #x << " = " << x << endl
#define read(x) x=getint()
#define rdm(u) for(int i=ihead[u]; i; i=e[i].next)
 
const int N=10000, M=15;
inline const int getint() { char c=getchar(); int k=1, ret=0; for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) ret=ret*10+c-'0'; return k*ret; }
struct ed { int to, next; } e[N<<1];
int cnt, ihead[N], n, m, dep[N], fa[N][M];
bool vis[N];
inline void add(const int &u, const int &v) {
    e[++cnt].next=ihead[u]; ihead[u]=cnt; e[cnt].to=v;
    e[++cnt].next=ihead[v]; ihead[v]=cnt; e[cnt].to=u;
}
void dfs(const int &u, const int &d) {
    vis[u]=1; dep[u]=d;
    rdm(u) if(!vis[e[i].to]) { dfs(e[i].to, d+1); fa[e[i].to][0]=u; }
}
inline void bz() { for(int j=1; j<M; ++j) for(int i=1; i<=n; ++i) fa[i][j]=fa[fa[i][j-1]][j-1]; }
inline int lca(int u, int v) {
    if(dep[u]<dep[v]) swap(u, v);
    int d=dep[u]-dep[v];
    for(int i=M-1; i>=0; --i) if((1<<i)&d) u=fa[u][i];
    if(u==v) return u;
    for(int i=M-1; i>=0; --i) if(fa[u][i]!=fa[v][i]) u=fa[u][i], v=fa[v][i];
    return fa[u][0];
}
int main() {
    read(n); read(m);
    for(int i=1; i<n; ++i) add(getint(), getint());
    dfs(1, 1); bz();
    while(m--) printf("%d\n", lca(getint(), getint()));
    return 0;
}
