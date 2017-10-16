//求gcd(a,b)
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}
//ax+by=gcd(a,b),返回gcd(a,b)
int extgcd(int a, int b, int &x, int &y)
{

    int d = a;
    if(b != 0) {
        d  = extgcd(b, a % b, y, x);
        y -= (a/b) * x;
    }else {
        x = 1, y = 0;
    }
    return d;
}
//a×x+b×y=c,返回x的最小整数解
int cal(int a, int b, int c)
{
    int x, y;
    int gcd = extgcd(a, b, x, y);
    if(c % gcd != 0) return -1;
    x *= c/gcd;
    b /= gcd;
    if(b < 0) b = -b;
    int ans = x % b;
    if(ans <= 0) ans += b;
    return ans;
}
