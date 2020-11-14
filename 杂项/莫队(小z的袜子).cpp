#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define debug printf("PASS IN LINE:%d\n",__LINE__)

#define N (int)(50007)
int n,m,k;
int a[N];
struct Query{
	int l,r,id;
}qu[N];

bool operator <(Query &a,Query &b) { return a.l/k==b.l/k? a.r<b.r:a.l/k<b.l/k; }

ll Ans[N],Ans_[N];

ll l=0,r=0,now=0;

int cnt[N];

ll GCD(ll a, ll b){ return b?GCD(b, a%b):a; }

void move(int pos,int sign){
	now=now+2*sign*cnt[a[pos]]+1;
	cnt[a[pos]]+=sign;
}

void Solve(){
	k=ceil(pow(n,0.5));
	sort(qu+1,qu+m+1);
	l=1,r=0,now=0;
	for(int i=1;i<=m;i++){
		while(l > qu[i].l) move(--l,1);
		while(r < qu[i].r) move(++r,1);
		while(l < qu[i].l) move(l++,-1);
		while(r > qu[i].r) move(r--,-1);
		if(l==r) Ans[qu[i].id]=0,Ans_[qu[i].id]=1;
		else {
			Ans[qu[i].id]=1ll*now-(r-l+1),Ans_[qu[i].id]=1ll*(r-l+1)*(r-l);
			ll d=GCD(Ans[qu[i].id],Ans_[qu[i].id]);
			Ans[qu[i].id]/=d,Ans_[qu[i].id]/=d;
		}
	}
}

int main(){
	n=input(),m=input();
	for(int i=1;i<=n;i++){
		a[i]=input();
	}

	for(int i=1;i<=m;i++){
		qu[i].l=input(),qu[i].r=input(),qu[i].id=i;
	}

	Solve();

	for(int i=1;i<=m;i++){
		printf("%lld/%lld\n",Ans[i],Ans_[i]);
	}
}