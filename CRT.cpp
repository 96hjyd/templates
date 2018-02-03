void ext_gcd(LL a,LL b,LL &x,LL &y)
{
    if(b != 0) {
        ext_gcd(b, a % b, y, x);
        y -= (a/b) * x;
    }else {
        x = 1, y = 0;
    }
}
long long CRT(int k,LL *a,LL *m) //k方程数，a余数数组，m模数数组 
{
    long long x,y,ans=0,M=1;
    for(int i=0;i<k;i++) M*=m[i];
    for(int i=0;i<k;i++){
        LL w=M/m[i];
        ext_gcd(m[i],w,x,y);
        ans=(ans+y*w*a[i])%M;
    }
    return (ans+M)%M;
}
