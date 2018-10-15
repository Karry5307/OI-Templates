#include<bits/stdc++.h>
using namespace std;
typedef int ll;
/*
Segment Tree can maintain many information on the interval,such as interval sum, interval maximum value and interval minimum value 
*/
//x.Segment Tree, maintain interval sum and support interval addition, interval multplication.
namespace SegmentTreeX{
    const ll MAXN=2e5+51;
    struct SegmentTree{
        ll l,r,sum,tag,mtag;
    };
    SegmentTree tree[MAXN<<2];
    ll cnt,qcnt,mod,x,l,r,op;
    ll num[MAXN];
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
    inline void update(ll node)
    {
        tree[node].sum=(tree[node<<1].sum+tree[(node<<1)|1].sum)%mod;
    }
    inline void create(ll l,ll r,ll node)
    {
        tree[node].l=l,tree[node].r=r,tree[node].mtag=1;
        if(l==r)
        {
            tree[node].sum=num[l]%mod;
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
            tree[node<<1].sum%=mod,tree[(node<<1)|1].sum%=mod;
            tree[node<<1].mtag*=tree[node].mtag,tree[(node<<1)|1].mtag*=tree[node].mtag;
            tree[node<<1].mtag%=mod,tree[(node<<1)|1].mtag%=mod;
            tree[node<<1].tag*=tree[node].mtag,tree[(node<<1)|1].tag*=tree[node].mtag;
            tree[node<<1].tag%=mod,tree[(node<<1)|1].tag%=mod;
            tree[node].mtag=1;
            tree[node<<1].tag+=tree[node].tag,tree[(node<<1)|1].tag+=tree[node].tag;
            tree[node<<1].tag%=mod,tree[(node<<1)|1].tag%=mod;
            tree[node<<1].sum+=tree[node].tag*(tree[node<<1].r-tree[node<<1].l+1);tree[(node<<1)|1].sum+=tree[node].tag*(tree[(node<<1)|1].r-tree[(node<<1)|1].l+1);
            tree[node<<1].sum%=mod,tree[(node<<1)|1].sum%=mod;
            tree[node].tag=0;
        }
    }
    inline void add(ll l,ll r,ll val,ll node)
    {
        if(l<=tree[node].l&&r>=tree[node].r)
        {
            tree[node].sum+=val*(tree[node].r-tree[node].l+1);
            tree[node].sum%=mod;
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
            tree[node].mtag%=mod,tree[node].sum%=mod,tree[node].tag%=mod;
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
    void main()
    {
        cnt=read(),qcnt=read(),mod=read();
        for(register int i=1;i<=cnt;i++)
        {
            num[i]=read();
        }
        create(1,cnt,1);
        for(register int i=1;i<=qcnt;i++)
        {
            op=read(),l=read(),r=read();
            switch(op)
            {
                case 1:{
                    x=read();
                    multiply(l,r,x,1);
                    break;
                }
                case 2:{
                    x=read();
                    add(l,r,x,1);
                    break;
                }
                case 3:{
                    printf("%lld\n",query(l,r,1)%mod);
                }
            }
        }
    }
}
/*
Persistent Segment Tree, also named President Tree, can maintain kth minimum value of the interval.
We sort and discrete the insertion data and create some new node to maintain the history versions, so we choose to create nodes dynamically.
Before insertion, call the function readDiscrete();
*/
//xi.Persistent Segment Tree, maintain the kth minimum sum but don't change value.(Static President Tree)
namespace PersistentSegmentTree{
    const ll MAXN=2e5+51;
    struct SegmentTree{
        ll l,r,ls,rs,sum;
    };
    SegmentTree tree[MAXN<<5];
    ll cnt,ccnt,tot,size,l,r,rk;
    ll root[MAXN],num[MAXN],dsc[MAXN];
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
    inline void readDiscrete()
    {
        cnt=read(),ccnt=read();
        for(register int i=1;i<=cnt;i++)
        {
            dsc[i]=num[i]=read();
        }
        sort(dsc+1,dsc+cnt+1);
        size=unique(dsc+1,dsc+cnt+1)-dsc-1;
    }
    inline void create(ll l,ll r,ll &node)
    {
        node=++tot;
        tree[node].l=l,tree[node].r=r,tree[node].sum=0;
        if(l==r)
        {
            return;
        }
        ll mid=(l+r)>>1;
        create(l,mid,tree[node].ls);
        create(mid+1,r,tree[node].rs);
    }
    inline ll insert(ll pos,ll node)
    {
        ll cur=++tot;
        tree[cur].l=tree[node].l,tree[cur].r=tree[node].r;
        tree[cur].sum=tree[node].sum+1;
        tree[cur].ls=tree[node].ls,tree[cur].rs=tree[node].rs;
        if(tree[node].l==tree[node].r)
        {
            return cur;
        }
        ll mid=(tree[node].l+tree[node].r)>>1;
        if(pos<=mid)
        {
            tree[cur].ls=insert(pos,tree[node].ls);
        }
        else
        {
            tree[cur].rs=insert(pos,tree[node].rs);
        }
        return cur;
    }
    inline ll findVal(ll l,ll r,ll rk,ll lcur,ll rcur)
    {
        ll mid=(l+r)>>1,diff=tree[tree[rcur].ls].sum-tree[tree[lcur].ls].sum;
        if(l==r)
        {
            return l;
        }
        if(rk<=diff)
        {
            return findVal(l,mid,rk,tree[lcur].ls,tree[rcur].ls);
        }
        else
        {
            return findVal(mid+1,r,rk-diff,tree[lcur].rs,tree[rcur].rs);
        }
    }
    void main()
    {
        readDiscrete(),create(1,size,root[0]);
        for(register int i=1;i<=cnt;i++)
        {
            root[i]=insert(lower_bound(dsc+1,dsc+size+1,num[i])-dsc,root[i-1]);
        }
        for(register int i=0;i<ccnt;i++)
        {
            l=read(),r=read(),rk=read();
            printf("%d\n",dsc[findVal(1,size,rk,root[l-1],root[r])]);
        }
    } 
}
/*
Persistent Data Structures, based on President Tree.
It can maintain values in the history versions, and we can change or query a value in a given version.
Most of these problems will use update(node), but Luogu P3919 will TLE on test 9 if using update(node).
*/
//xii.Persistent array,provide changing or querying a value in the given version and create a new version.
namespace PersistentArray{
}
