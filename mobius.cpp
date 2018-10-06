//对于给出的k个询问,每次求有多少个数对(x,y),满足a≤x≤b,c≤y≤d,且gcd(x,y)=e
#include<bits/stdc++.h>
using namespace std;
const int maxn=50005;
int primes[maxn],top,is[maxn],mu[maxn],sum[maxn];
void seive()
{
    fill(mu,mu+maxn,1);
    mu[0]=0;
    for(int i=2;i<maxn;i++)
    {
        if(!is[i])
        {
            primes[top++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<top&&primes[j]*i<maxn;j++)
        {
            is[primes[j]*i]=1;
            if(i%primes[j]==0)
            {
                mu[primes[j]*i]=0;
                break;
            }
            else
            {
                mu[primes[j]*i]=-mu[i];
            }
        }
    }
    for(int i=1;i<maxn;i++) sum[i]=sum[i-1]+mu[i];
}
int f(int n,int m,int k)
{
    if(n>m) swap(n,m);
    int ans=0;
    n=n/k;
    m=m/k;
    int last;
    for(int i=1;i<=n;i=last+1)
    {
        last=min(n/(n/i),m/(m/i));
        ans+=(long long)(sum[last]-sum[i-1])*(m/i)*(n/i);
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k,a,b,c,d,e;
    cin>>k;
    seive();
    while(k--)
    {
        cin>>a>>b>>c>>d>>e;
        cout<<f(b,d,e)+f(a-1,c-1,e)-f(b,c-1,e)-f(a-1,d,e)<<endl;
    }
    return 0;
}
