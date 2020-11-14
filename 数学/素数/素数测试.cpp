#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define IO ios::sync_with_stdio(false)
#define pb push_back
#define mk make_pair
const int N = 1e5+10;
const int mod = 1e9+7;
 
ll a, b;
 
const long long S=20;
 
ll mult_mod(ll a,ll b,ll mod)//快速乘
{
	ll res=0;
	for(;b;b>>=1){
		if(b&1) res=(res+a)%mod;
		a=(a+a)%mod;
	}
	return res;
}
ll pow_mod(ll a,ll b,ll mod)//快速幂
{
	ll res=1;
	a%=mod;
	for(;b;b>>=1){
		if(b&1) res=mult_mod(res,a,mod);
		a=mult_mod(a,a,mod);
	}
	return res;
}
int check(ll a,ll n,ll x,ll t){
    ll ret=pow_mod(a,x,n);//费马小定理 a^(p-1)%p==1
    ll last=ret;
    for(ll i=1;i<=t;i++){//二次检测定理 如果p是一个素数，则x^2%p==1的解为，则x=1或者x=n-1。
        ret=mult_mod(ret,ret,n);
        if(ret==1&&last!=1&&last!=n-1) return 1;
        last=ret;
    }
    if(ret!=1) return 1;
    return 0;
}
int Miller_Rabin(ll n){
    if(n<2)return 0;
    if(n==2)return 1;
    if((n&1)==0) return 0;
    ll x=n-1;
    ll t=0;
    while((x&1)==0){x>>=1;t++;}
    for(ll i=0;i<S;i++){
        ll a=rand()%(n-1)+1;
        if(check(a,n,x,t))  return 0;
    }
    return 1;
}
 
int main(){
	for(ll i=100000000000;i<=100000000100;++i){
        if(Miller_Rabin(i)) printf("%lld 是素数\n",i);
        else printf("%lld 不是素数\n",i);
	}
}


//////////////////////////////////////////////////////


#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
ll mul(ll a,ll b,ll mod){//高精度
    a%=mod;
    b%=mod;
    ll c=(long double)a*b/mod;
    ll ans=a*b-c*mod;
    return (ans%mod+mod)%mod;
}
ll pow_mod(ll x,ll n,ll mod){//快速幂
    ll res=1;
    while(n){
        if(n&1)
        res=mul(res,x,mod);
        x=mul(x,x,mod);
        n>>=1;
    }
    return (res+mod)%mod;
}
bool Miller_Rabbin(ll a,ll n){
    
    //把n-1  转化成 (2^r)*d
    ll s=n-1,r=0;
    while((s&1)==0){
        s>>=1;r++;
    }
    
    //算出 2^d  存在 k 里
    ll k=pow_mod(a,s,n);
    
    //二次探测  看变化过程中是不是等于1 或 n-1
    if(k==1)return true;
    for(int i=0;i<r;i++,k=k*k%n){
        if(k==n-1)return true;
    }
    return false;
}
bool isprime(ll n){
    //这里可以随机取a值进行探测  探测次数可以自己定
    ll times=7;
    ll prime[100]={2,325,9375,28178,450775,9780504,1795265022};
    for(int i=0;i<times;i++){
        if(n==prime[i])return true;
        if(Miller_Rabbin(prime[i],n)==false)return false;//未通过探测 返回假
    }
    return true;//所有探测结束 返回真
}