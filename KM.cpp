//最大权匹配O(n^4)
#define M 505
#define inf 0x3fffffff
bool sx[M], sy[M];
int match[M], w[M][M], n, m, d, lx[M], ly[M];
//n：左集元素个数； m：右集元素个数
void init ()
{
    memset (w, 0, sizeof(w));    //不一定要，求最小值一般要初始化为负无穷！
}

bool dfs (int u)
{
    int v; sx[u] = true;
    for (v = 0; v < m; v++)
    {
        if (!sy[v] && lx[u]+ly[v]==w[u][v])
        {
            sy[v] = true;
            if (match[v] == -1 || dfs (match[v]))
            {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int KM ()
{
    int i, j, k, sum = 0;
    memset (ly, 0, sizeof(ly));
    for (i = 0; i < n; i++)
    {
        lx[i] = -inf;
        for (j = 0; j < m; j++)
            if (lx[i] < w[i][j])
                lx[i] = w[i][j];
    }
    memset (match, -1, sizeof(match));
    for (i = 0; i < n; i++)
    {
        while (1)
        {
            memset (sx, false, sizeof(sx));
            memset (sy, false, sizeof(sy));
            if (dfs (i))
                break;
            d = inf;
            for (j = 0; j < n; j++)
                if (sx[j])
                    for (k = 0; k < m; k++)
                        if (!sy[k])
                            d = min (d, lx[j]+ly[k]-w[j][k]);
            if (d == inf)    //找不到完美匹配
                return -1;
            for (j = 0; j < n; j++)
                if (sx[j])
                    lx[j] -= d;
            for (j = 0; j < m; j++)
                if (sy[j])
                    ly[j] += d;
        }
    }
    for (i = 0; i < m; i++)
        if (match[i] > -1)
            sum += w[match[i]][i];
    return sum;
}
/******************************************************************************/
//最大权匹配O(n^3)
/*其实在求最大 最小的时候只要用一个模板就行了,把边的权值去相反数即可得到另外一个.求结果的时候再去相反数即可*/
/*最大最小有一些地方不同。。*/
#include <iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
//赤裸裸的模板啊。。
const int maxn = 101;
const int INF = (1<<31)-1;
int w[maxn][maxn];
int lx[maxn],ly[maxn]; //顶标
int linky[maxn];
int visx[maxn],visy[maxn];
int slack[maxn];
int nx,ny;
bool find(int x)
{
    visx[x] = true;
    for(int y = 0; y < ny; y++)
    {
        if(visy[y])
            continue;
        int t = lx[x] + ly[y] - w[x][y];
        if(t==0)
        {
            visy[y] = true;
            if(linky[y]==-1 || find(linky[y]))
            {
                linky[y] = x;
                return true;        //找到增广轨
            }
        }
        else if(slack[y] > t)
            slack[y] = t;
    }
    return false;                   //没有找到增广轨（说明顶点x没有对应的匹配，与完备匹配(相等子图的完备匹配)不符）
}

int KM()                //返回最优匹配的值
{
    int i,j;

    memset(linky,-1,sizeof(linky));
    memset(ly,0,sizeof(ly));
    for(i = 0; i < nx; i++)
        for(j = 0,lx[i] = -INF; j < ny; j++)
            if(w[i][j] > lx[i])
                lx[i] = w[i][j];
    for(int x = 0; x < nx; x++)
    {
        for(i = 0; i < ny; i++)
            slack[i] = INF;
        while(true)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(find(x))                     //找到增广轨，退出
                break;
            int d = INF;
            for(i = 0; i < ny; i++)          //没找到，对l做调整(这会增加相等子图的边)，重新找
            {
                if(!visy[i] && d > slack[i])
                    d = slack[i];
            }
            for(i = 0; i < nx; i++)
            {
                if(visx[i])
                    lx[i] -= d;
            }
            for(i = 0; i < ny; i++)
            {
                if(visy[i])
                     ly[i] += d;
                else
                     slack[i] -= d;
            }
        }
    }
    int result = 0;
    for(i = 0; i < ny; i++)
    if(linky[i]>-1)
        result += w[linky[i]][i];
    return result;
}

int main()
{
    while(true)
    {
        scanf("%d%d",&nx,&ny);
        int a,b,c;
        while(scanf("%d%d%d",&a,&b,&c),a+b+c)
        {
            w[a][b]=c;
        }
        printf("%d\n",KM());
        break;
    }
    return 0;
}
