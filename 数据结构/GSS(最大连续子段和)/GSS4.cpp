#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=1e5+7;

int n,m;
ll a[N];

struct seg{
	ll sum,mx;
}t[N*4];

void put(int rt){
	t[rt].mx=max(t[rt<<1].mx,t[rt<<1|1].mx);
	t[rt].sum=t[rt<<1].sum+t[rt<<1|1].sum;
}

void build(int rt,int l,int r){
	if(l==r){
		t[rt].mx=t[rt].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
	put(rt);
}

void update(int rt,int l,int r,int ul,int ur){
	if(l==r){
		t[rt].mx=sqrt(t[rt].mx);
		t[rt].sum=sqrt(t[rt].sum);
		return;
	}
	if(t[rt].mx==1) return;
	int mid=(l+r)>>1;
	if(ur<=mid) update(rt<<1,l,mid,ul,ur);
	else if(mid<ul) update(rt<<1|1,mid+1,r,ul,ur);
	else update(rt<<1,l,mid,ul,ur),update(rt<<1|1,mid+1,r,ul,ur);
	put(rt);
}

ll query(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return t[rt].sum;
	int mid=(l+r)>>1;
	if(qr<=mid) return query(rt<<1,l,mid,ql,qr);
	if(mid<ql) return query(rt<<1|1,mid+1,r,ql,qr);
	return query(rt<<1,l,mid,ql,qr)+query(rt<<1|1,mid+1,r,ql,qr);
}

int main(){
	int cas=0;
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++)
			a[i]=input();
		build(1,1,n);
		m=input();
		printf("Case #%d:\n",++cas);
		for(int i=1;i<=m;i++){
			int f=input(),l=input(),r=input();
			if(l>r) swap(l,r);
			if(f==0) update(1,1,n,l,r);
			else printf("%lld\n",query(1,1,n,l,r));
		}
	}
}