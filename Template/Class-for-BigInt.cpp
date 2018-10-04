//This is the template of bigInt.
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
class BigInt
{
    public:
        char val[4005];
        ll digit,isNegative;
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
};
inline BigInt operator +(Bigint x,Bigint y)
{
    BigInt res;
    ll up;
    for(register int i=0;i<max(x.digit,y.digit);i++)
    {
        res.val[i]=(x.val[i]-'0'+y.val[i]-'0')%10+up+'0';
        up=(x.val[i]-'0'+y.val[i]-'0')/10;
        res.digit++;
    }
    return res;
}
