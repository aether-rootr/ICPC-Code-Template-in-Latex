#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const ll mod=1e9+7;

#define VI vector<int>

ll powmod(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}

int n;

#define debug printf("pass in line:%d\n",__LINE__)

namespace linear_seq{
	const int N=10010;
	ll res[N],base[N],_c[N],_md[N];

	vector<int> Md;

	void mul(ll *a,ll *b,int k){
		for(int i=0;i<k*2;i++) _c[i]=0;
		for(int i=0;i<k;i++)
			if(a[i])
				for(int j=0;j<k;j++)
					_c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
		for(int i=k*2-1;i>=k;i--)
			if(_c[i])
				for(int j=0;j<Md.size();j++)
					_c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
		for(int i=0;i<k;i++) a[i]=_c[i];
	}

	int solve(ll n,VI a,VI b){
		ll ans=0,pnt=0;
		int k=a.size();
		for(int i=0;i<k;i++) _md[k-1-i]=-a[i];_md[k]=1;
		Md.clear();	
		for(int i=0;i<k;i++) if(_md[i]!=0) Md.push_back(i);
		for(int i=0;i<k;i++) res[i]=base[i]=0;
		res[0]=1;
		while((1ll<<pnt)<=n) pnt++;
		for(int p=pnt;p>=0;p--){
			mul(res,res,k);
			if((n>>p)&1){
				for(int i=k-1;i>=0;i--) res[i+1]=res[i];res[0]=0;
				for(int j=0;j<Md.size();j++) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
			}
		}
		for(int i=0;i<k;i++) ans=(ans+res[i]*b[i])%mod;
		if(ans<0) ans+=mod;
		return ans;
	}

	VI BM(VI s){
		VI C(1,1),B(1,1);
		int L=0,m=1,b=1;
		for(int n=0;n<s.size();n++){
			ll d=0;
			for(int i=0;i<=L;i++) d=(d+(ll)C[i]*s[n-i])%mod;
			if(d==0) ++m;
			else if(2*L<=n){
				VI T=C;
				ll c=mod-d*powmod(b,mod-2)%mod;
				while(C.size()<B.size()+m) C.push_back(0);
				for(int i=0;i<B.size();i++) C[i+m]=(C[i+m]+c*B[i])%mod;
				L=n+1-L,B=T,b=d,m=1;
			}else{
				ll c=mod-d*powmod(b,mod-2)%mod;
				while(C.size()<B.size()+m) C.push_back(0);
				for(int i=0;i<B.size();i++) C[i+m]=(C[i+m]+c*B[i])%mod;
				++m;
			}
		}
		return C;
	}

	int gao(VI a,ll n){
		VI c=BM(a);
		c.erase(c.begin());
		for(int i=0;i<c.size();i++) c[i]=(mod-c[i])%mod;
		return solve(n,c,VI(a.begin(),a.begin()+c.size()));
	}
}

int main(){
	while(~scanf("%d",&n)){
		VI v;
		v.push_back(1);
        v.push_back(2);
        v.push_back(4);
        v.push_bac(7);
        v.push_back(13);
        v.push_back(24);
        printf("%d\n",linear_seq::gao(v,n-1));
	}
}