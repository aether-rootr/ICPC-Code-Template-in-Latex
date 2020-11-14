#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int maxn=107;
ll n,m;
ll ai[maxn],bi[maxn];

ll mul(ll a,ll b,ll mod){
    ll res=0;
    while(b>0){
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}

ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){x=1;y=0;return a;}
    ll gcd=exgcd(b,a%b,x,y);
    ll tp=x;
    x=y; y=tp-a/b*y;
    return gcd;
}

ll excrt(){
    ll x,y,k;
    ll M=bi[1],ans=ai[1];//第一个方程的解特判
    for(int i=2;i<=n;i++){
        ll a=M,b=bi[i],c=(ai[i]-ans%b+b)%b;//ax≡c(mod b)
        ll gcd=exgcd(a,b,x,y),bg=b/gcd;
        if(c%gcd!=0) return -1; //判断是否无解，然而这题其实不用

        x=mul(x,c/gcd,bg);
        ans+=x*M;//更新前k个方程组的答案
        M*=bg;//M为前k个m的lcm
        ans=(ans%M+M)%M;
    }
    return (ans%M+M)%M;
}

int main()
{
    n=input();
    for(int i=1;i<=n;++i)
    bi[i]=input(),ai[i]=input(); //bi为a数组，ai为b数组
    printf("%lld",excrt());
    return 0;
}