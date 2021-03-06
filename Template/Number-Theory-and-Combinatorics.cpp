#include<bits/stdc++.h>
using namespace std;
/*
Many number theoretic problems has the data which is bigger than INT_MAX, so use long long int.
Arrays index starts at 0 and all mod below must be prime if not explained.
All math formulas in the comments is written in LaTeX.
*/
typedef long long int ll;

/*
By using gcd(x,y) and lcm(x,y), you can get the gcd and lcm of two numbers.
*/
inline ll gcd(ll x,ll y)
{
    return !y?x:gcd(x%y);
}
inline ll lcm(ll x,ll y)
{
    return x/gcd(x,y)*y;
}
/*
By using GaussElimination(), you can solve the system of linear equations.
The array mat is the coefficients of every variable in every equation.
The array val is the constant term, it's also the value of each variable after the elimination.
The i-th equation is like this:
mat[i][0]*x_0+mat[i][1]*x_1+...+mat[i][size-1]*x_{size-1}=val[i]
*/
const ll MAXN=151;
const double eps=1e-6;
ll size;
double mat[MAXN][MAXN],val[MAXN];
inline void findPivot(ll cur)
{
    ll pivot=cur;
    for(register int i=cur+1;i<size;i++)
    {
        if(fabs(mat[pivot][cur]-mat[i][cur])>eps)
        {
            pivot=i;
        }
    }
    if(fabs(mat[pivot][cur])<eps)
    {
        printf("No Solution");
        exit(0);
    }
    swap(val[cur],val[pivot]);
    for(register int i=cur;i<size;i++)
    {
        swap(mat[cur][i],mat[pivot][i]);
    }
}
inline void eliminate(ll cur)
{
    double cof;
    for(register int i=cur+1;i<size;i++)
    {
        if(mat[i][cur]!=0)
        {
            cof=mat[i][cur]/mat[cur][cur];
            for(register int j=cur;j<size;j++)
            {
                mat[i][j]-=(cof*mat[cur][j]);
            }
            val[i]-=(cof*val[cur]);
        }
    }
}
inline void subsitute(ll cur)
{
    val[cur]/=mat[cur][cur],mat[cur][cur]=1;
    for(register int i=cur-1;i>=0;i--)
    {
        val[i]=val[i]-val[cur]*mat[i][cur],mat[i][cur]=0;
    }
}
inline void GaussElimination()
{
    for(register int i=0;i<=size-1;i++)
    {
        findPivot(i),eliminate(i);
    }
    for(register int i=size-1;i>=0;i--)
    {
        subsitute(i);
    }
}
/*
By using BSGS(x,y,z), you can get the minimum t of the equation x^t\equiv y\pmod z
I don't think that using hash table is perfect, it can be wrong if the extreme data exists,but it's faster than STL.
You can use your hash table instead of STL, cc_hash_table and gp_hash_table in pb_ds also can replace map.
Two fast multiplication templates is provided, the first is based on Divide and Conquer algorithm, and the second is based on distributive law.
*/
map<ll,ll>ht;
ll mod,val;
inline ll qmul(ll x,ll y,ll mod)
{
    if(!y)
    {
        return 0;
    }
    ll temp=qmul(x,y>>1,mod);
    ll res=(temp<<1)%mod;
    if(y&1)
    {
        res=(res+x)%mod;
    }
    return res;
}
inline ll qmul(ll x,ll y,ll mod)
{
    ll l=(y>>25)*x%mod*((1<<25)%mod),r=(y&((1<<25)-1))*x%mod;
    return (l+r)%mod;
}
inline ll qpow(ll base,ll exponent,ll mod)
{
    if(!exponent)
    {
        return 1;
    }
    ll temp=qpow(base,exponent>>1,mod);
    ll res=qmul(temp,temp,mod);
    if(exponent&1)
    {
        res=qmul(res,base,mod);
    }
    return res;
}
inline ll BSGS(ll base,ll res,ll mod)
{
    ht.clear(),res%=mod;
    ll temp,val,fail;
    temp=sqrt((long double)(mod))+1;
    for(register int i=0;i<temp;i++)
    {
        val=qmul(res,qpow(base,i,mod),mod);
        ht[val]=i;
    }
    base=qpow(base,temp,mod);
    if(!base)
    {
        return !res?1:-1;
    }
    for(register int i=0;i<=temp;i++)
    {
        val=qpow(base,i,mod),fail=ht.find(val)==ht.end()?-1:ht[val];
        if(fail>=0&&i*temp-fail>=0)
        {
            return i*temp-fail;
        }
    }
    return -1;
}
/*
Chinese Remainder Theorem.
*/
inline ll excrt(ll cnt)
{
	ll x,y,z,xx,yy,zz,xgzc,m=md[0],res=rs[0];
	for(register int i=1;i<cnt;i++)
	{
		xx=m,yy=md[i],zz=(rs[i]-res%yy+yy)%yy;
		exgcd(xx,yy,x,y),xgzc=gcd(xx,yy),z=yy/xgzc;
		if(zz%xgzc)
		{
			return -1;
		}
		x=(li)x*(zz/xgzc)%z,res+=x*m,m*=z;
		res=(res%m+m)%m;
	}
	return (res%m+m)%m;
	 
}
