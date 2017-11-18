#include<cstdio>
#include<cstring>
using namespace std;
char s1[1000005];
char s2[1000005];
int next[1000005];
int n,m;
void getnext()
{
    next[0]=0;
    next[1]=0;
    for(int i=1;i<m;i++)
    {
        int j=next[i];
        while(j&&s2[j]!=s2[i]) j=next[j];
        next[i+1]=(s2[j]==s2[i])?(j+1):0;
    }
}
void kmp()
{
    int j=0;
    for(int i=0;i<n;i++)
    {
        while(j&&s2[j]!=s1[i]) j=next[j];
        if(s1[i]==s2[j]) j++;
        if(j==m) printf("%d\n",i-m+2);
    }
}
int main()
{
    scanf("%s%s",s1,s2);
    n=strlen(s1);
    m=strlen(s2);
    getnext();
    kmp();
    for(int i=1;i<=m;i++) printf("%d ",next[i]);
    return 0;
}
