struct Point
{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
}p[10005],ch[10005];
Point operator+(Point A,Point B) {return Point(A.x+B.x,A.y+B.y);}
Point operator-(Point A,Point B) {return Point(A.x-B.x,A.y-B.y);}
Point operator*(Point A,double p) {return Point(A.x*p,A.y*p);}
Point operator/(Point A,double p) {return Point(A.x/p,A.y/p);}
bool operator<(const Point& a,const Point& b)
{   
    return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
const double eps=1e-10;
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;else return x<0?-1:1;
}
bool operator==(const Point& a,const Point& b)
{
    return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
}
double Cross(Point A,Point B) {return A.x*B.y-A.y*B.x;}
double Dot(Point A,Point B) {return A.x*B.x+A.y*B.y;}
double Length(Point A) {return sqrt(Dot(A,A));}
double Angle(Point A,Point B) {return acos(Dot(A,B))/Length(A)/Length(B);}
int ConvexHall(Point* p,int n,Point* ch)
{
    sort(p,p+n);
    int m=0;
    for(int i=0;i<n;i++)
    {
        while(m>1&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++]=p[i];
    }
    int k=m;
    for(int i=n-2;i>=0;i--)
    {
        while(m>k&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++]=p[i];
    }
    if(n>1) m--;
    return m;
}
