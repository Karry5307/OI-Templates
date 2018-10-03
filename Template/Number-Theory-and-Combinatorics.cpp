#include<bits/stdc++.h>
using namespace std;
// Many number theoretic problems has the data which is bigger than INT_MAX, so use long long int.
typedef long long int ll;
//Arrays index starts at 0 if not explained.
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
By using BSGS,...
Two fast multiplication templates is provided, the first is based on Divide and Conquer algorithm, the second is based on distributive law.
*/
//gg
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
int main()
{
    val=read(),mod=read();
    val=(qmul(9,val,mod)+1)%mod;
    write(BSGS(10,val,mod));
}
