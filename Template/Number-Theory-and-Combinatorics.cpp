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
