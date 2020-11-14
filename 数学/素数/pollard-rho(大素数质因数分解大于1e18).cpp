#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define LL __int128

ll gcd(ll a,ll b){
	if(b==0) return a;
	return gcd(b,a%b);
}

ll powmod(ll a,ll b,ll mod){
	ll res=1;
	while(b){
		if(b&1) res=(LL)res*a%mod;
		a=(LL)a*a%mod;
		b>>=1;
	}
	return res;
}

bool Miller_Rabin(ll p){
	if(p<2) return 0;
	if(p==2) return 1;
	if(p==3) return 1;
	ll d=p-1,r=0;
	while(!(d&1)) ++r,d>>=1;
	for(ll k=0;k<10;k++){
		ll a=rand()%(p-2)+2;
		ll x=powmod(a,d,p);
		if(x==1||x==p-1) continue;
		for(int i=0;i<r-1;i++){
			x=(LL)x*x%p;
			if(x==p-1) break;
		}
		if(x!=p-1) return 0;
	}
	return 1;
}

ll f(ll x,ll c,ll n){return ((LL)x*x+c)%n;}

ll Pollard_Rho(ll x){
	ll s=0,t=0;
	ll c=(ll)rand()%(x-1)+1;
	int step=0,goal=1;
	ll val=1;
	for(goal=1;;goal<<=1,s=t,val=1){
		for(step=1;step<=goal;step++){
			t=f(t,c,x);
			val=(LL)val*abs(t-s)%x;
			if((step%127)==0){
				ll d=gcd(val,x);
				if(d>1) return d;
			}
		}
		ll d=gcd(val,x);
		if(d>1) return d;
	}
}

vector<ll> pri;

void fac(ll x){
	if(x<2) return;
	if(Miller_Rabin(x)){
		pri.push_back(x);
		return;
	}
	ll p=x;
	while(p>=x) p=Pollard_Rho(x);
	while(x%p==0) x/=p;
	fac(x),fac(p);
}

int main(){
	srand((unsigned)time(NULL));
	int T=input();
	while(T--){
		pri.clear();
		ll n=input();
		ll max_factor=0;

		fac(n);

		for(int i=0;i<pri.size();i++){
			max_factor=max(max_factor,pri[i]);
		}

		if(max_factor==n) printf("Prime\n");
		else printf("%lld\n",max_factor);
	}
}