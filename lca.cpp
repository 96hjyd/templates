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
//tarjan（O(n+并查集)~O(1) ，离线)
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define dbg(x) cout << #x << " = " << x << endl
#define read(x) x=getint()
#define rdm(u) for(int i=ihead[u]; i; i=e[i].next)
 
const int N=10005, M=10005;
inline const int getint() { char c=getchar(); int k=1, ret=0; for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) ret=ret*10+c-'0'; return k*ret; }
struct ed { int to, next; } e[N<<1];
int cnt, ihead[N], n, m, lca[M], fa[N], p[N];
bool vis[N];
vector<pair<int, int> > q[N];
inline void add(const int &u, const int &v) {
    e[++cnt].next=ihead[u]; ihead[u]=cnt; e[cnt].to=v;
    e[++cnt].next=ihead[v]; ihead[v]=cnt; e[cnt].to=u;
}
int ifind(const int &x) { return x==p[x]?x:p[x]=ifind(p[x]); }
void tarjan(int u) {
    p[u]=u;
    rdm(u) if(e[i].to!=fa[u]) {
        fa[e[i].to]=u; tarjan(e[i].to); p[e[i].to]=u;
    }
    vis[u]=1;
    int t=q[u].size();
    for(int i=0; i<t; ++i) if(vis[q[u][i].first]) lca[q[u][i].second]=ifind(q[u][i].first);
}
int main() {
    read(n); read(m);
    for(int i=1; i<n; ++i) add(getint(), getint());
    int u, v;
    for(int i=1; i<=m; ++i) {
        read(u); read(v);
        q[v].push_back(pair<int, int> (u, i));
        q[u].push_back(pair<int, int> (v, i));
    }
    tarjan(1);
    for(int i=1; i<=m; ++i) printf("%d\n", lca[i]);
    return 0;
}
