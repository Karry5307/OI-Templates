//This is the template of bigInt.
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
class BigInt
{
    public:
        char val[4005];
        ll digit,isNegative;
        BigInt()
        {
            digit=isNegative=0;
        }
        inline void operator =(ll num)
        {
            while(num)
            {
                val[digit++]=num%10+'0';
                num/=10;
            }
        }    
        inline void operator =(BigInt num)
        {
            digit=num.digit;
            for(register int i=0;i<digit;i++)
            {
                val[i]=num.val[i];
            }
        }
        inline void operator =(string num)
        {
            digit=num.length();
            for(register int i=num.length()-1;i>=0;i--)
            {
                val[num.length()-1-i]=num[i];
            }
        }
};
inline ostream& operator <<(ostream& out,BigInt x)
{
    for(register int i=x.digit-1;i>=0;i--)
    {
        out<<x.val[i];
    }
}
inline BigInt operator +(BigInt x,BigInt y)
{
    BigInt res;
    ll up;
    for(register int i=0;i<max(x.digit,y.digit);i++)
    {
        res.val[i]=(x.val[i]-'0'+y.val[i]-'0'+up)%10+'0';
        up=(x.val[i]-'0'+y.val[i]-'0'+up)/10;
        res.digit++;
    }
    if(up)
    {
        res.val[res.digit++]=up+'0';
    }
    return res;
}
