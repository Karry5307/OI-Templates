#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=2e3+51; 
struct BigInt{
	ll digit;
	ll num[MAXN];
	BigInt()
	{
		memset(num,0,sizeof(num));
	}
	inline void operator =(ll x)
	{
		while(x)
		{
			num[digit++]=x%10000,x/=10000;
		} 
	}
	inline void op()
	{
		printf("%d",num[digit-1]);
		for(register int i=digit-2;i>=0;i--)
		{
			if(!num[i])
			{
				printf("0000");
				continue;
			}
			ll rest=3-(ll)(log10(num[i]));
			for(register int j=rest;j;j--)
			{
				putchar('0');
			}
			printf("%d",num[i]);
		}
	}
	inline bool operator >(const BigInt &rhs)const
	{
		if(digit!=rhs.digit)
		{
			return digit>rhs.digit;
		}
		for(register int i=digit-1;i>=0;i--)
		{
			if(num[i]!=rhs.num[i])
			{
				return num[i]>rhs.num[i];
			}
		}
		return 0;
	}
}; 
struct Minister{
	ll l,r;
	inline bool operator <(const Minister &rhs)const
	{
		return l*r<rhs.l*rhs.r;
	}
}; 
BigInt prefix,temp,res;
Minister minister[MAXN];
ll cnt;
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
template<class T>
inline T Max(T x,T y)
{
	return x>y?x:y;
}
inline BigInt operator +(BigInt x,BigInt y)
{
	BigInt res;
	ll carry=0;
	res.digit=max(x.digit,y.digit)+1;
	for(register int i=0;i<=res.digit;i++)
	{
		res.num[i]=x.num[i]+y.num[i]+carry;
		carry=res.num[i]/10000,res.num[i]%=10000;
	}
	if(!res.num[res.digit-1])
	{
		res.digit--;
	}
	return res;
}
inline BigInt operator *(BigInt x,ll y)
{
	BigInt res;
	ll carry=0;
	res.digit=x.digit+1;
	for(register int i=0;i<=res.digit;i++)
	{
		res.num[i]=x.num[i]*y+carry;
		carry=res.num[i]/10000,res.num[i]%=10000;
	}
	if(!res.num[res.digit-1])
	{
		res.digit--;
	}
	return res;
}
inline BigInt operator /(BigInt x,ll y)
{
	BigInt res;
	ll cur=0;
	res.digit=x.digit;
	for(register int i=x.digit-1;i>=0;i--)
	{
		cur=cur*10000+x.num[i];
		if(cur>=y)
		{
			res.num[i]=cur/y,cur%=y;
		}
	}
	if(!res.num[res.digit-1])
	{
		res.digit--;
	}
	return res;
}
