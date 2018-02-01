typedef long long LL;
const int maxn=22;
int dig[maxn];
LL f[maxn]/* [TODO] */;

LL dfs(int pos,/* TODO */,int limit){
    if (pos<0) return /* TODO */;
    if (!limit&&f[pos]/* [TODO] */!=-1) return f[pos]/* [TODO] */;
    LL res=0;
    int last=limit?dig[pos]:9;
    for (int i=0;i<=last;i++){
        res+=dfs(pos-1,/* TODO */,limit&&(i==last));
    }
    if (!limit) f[pos]/* [TODO] */=res;
    return res;
}

LL solve(LL n){
    int len=0;
    while (n){
        dig[len++]=n%10;
        n/=10;
    }
    return dfs(len-1,/* TODO */,1);
}
