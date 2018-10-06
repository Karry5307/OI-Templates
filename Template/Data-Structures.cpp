#include<bits/stdc++.h>
using namespace std;
typedef int ll;
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
/*
Segment Tree can maintain the interval sum, the interval maximum value and the interval minimum value 
*/
//x.Maintain the interval sum and support interval addition, interval multplication.
const ll MAXN=2e5+51;
struct SegmentTree{
    ll l,r,sum,tag,mtag;
};
SegmentTree tree[MAXN<<2];
ll num[MAXN];
inline void update(ll node)
{
    tree[node].sum=(tree[node<<1].sum+tree[(node<<1)|1].sum)%mod;
}
inline void create(ll l,ll r,ll node)
{
    tree[node].l=l,tree[node].r=r,tree[node].mtag=1;
    if(l==r)
    {
        tree[node].sum=num[l];
        return;
    }
    ll mid=(l+r)>>1;
    create(l,mid,node<<1);
    create(mid+1,r,(node<<1)|1);
    update(node);
}
inline void spread(ll node)
{
    if(tree[node].tag||tree[node].mtag!=-1)
    {
        tree[node<<1].sum*=tree[node].mtag,tree[(node<<1)|1].sum*=tree[node].mtag;
        tree[node<<1].mtag*=tree[node].mtag,tree[(node<<1)|1].mtag*=tree[node].mtag;
        tree[node<<1].tag*=tree[node].mtag,tree[(node<<1)|1].tag*=tree[node].mtag;
        tree[node].mtag=1;
        tree[node<<1].tag+=tree[node].tag,tree[(node<<1)|1].tag+=tree[node].tag;
        tree[node<<1].sum+=tree[node].tag*(tree[node<<1].r-tree[node<<1].l+1);
        tree[(node<<1)|1].sum+=tree[node].tag*(tree[(node<<1)|1].r-tree[(node<<1)|1].l+1);
        tree[node].tag=0;
    }
}
inline void add(ll l,ll r,ll val,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        tree[node].sum+=val*(tree[node].r-tree[node].l+1);
        tree[node].tag+=val;
        return;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(l<=mid)
    {
        add(l,r,val,node<<1);
    }
    if(r>mid)
    {
        add(l,r,val,(node<<1)|1);
    }
    update(node);
}
inline void multiply(ll l,ll r,ll val,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        tree[node].mtag*=val,tree[node].sum*=val,tree[node].tag*=val;
        return;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(l<=mid)
    {
        multiply(l,r,val,node<<1);
    }
    if(r>mid)
    {
        multiply(l,r,val,(node<<1)|1);
    }
    update(node);
}
inline ll query(ll l,ll r,ll node) 
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        return tree[node].sum;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1,val=0;
    if(l<=mid)
    {
        val+=query(l,r,node<<1);
    }
    if(r>mid)
    {
        val+=query(l,r,(node<<1)|1);
    }
    return val;
}
