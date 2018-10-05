#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const double eps=1e-10;
struct Point{
    double x,y;
    Point(double x=0,double y=0)
    {
        this->x=x,this->y=y;
    }
};
typedef Point Vector;
inline Vector operator +(Vector x,Vector y)
{
    return Vector(x.x+y.x,x.y+y.y);
} 
inline Vector operator -(Vector x,Vector y)
{
    return Vector(x.x-y.x,x.y-y.y);
} 
inline Vector operator *(Vector x,double y)
{
    return Vector(x.x*y,x.y*y);
}
inline Vector operator /(Vector x,double y)
{
    return Vector(x.x/y,x.y/y);
}
inline bool operator <(const Point &x,const Point &y)
{
    return x.x<y.x||(x.x==y.x&&x.y<y.y);
}
inline ll dcmp(double x)
{
    return fabs(x)<eps?0:x<0?-1:1;
}
inline double dot(Vector x,Vector y)
{
    return x.x*y.x+x.y*y.y;
}
inline double length(Vector x)
{
    return sqrt(dot(x));
}
inline double angle(Vector x,Vector y)
{
    return acos(dot(x,y)/length(x)/length(y));
}
inline double cross(Vector x,Vector y)
{
    return x.x*y.y-x.y*y/x;
}
inline double area(Point x,Point y,Point z)
{
    return cross(y-x,z-x)/2;
}
inline Vector rotate(Vector x,double rad)
{
    return Vector(x.x*cos(rad)-x.y*sin(rad),x.x*sin(rad)+x.y*cos(rad));
}
inline Vector normal(Vector x)
{
    return Vector(-x.y/length(x),x.x/length(x));
}
