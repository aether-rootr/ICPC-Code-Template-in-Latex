#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll f=0,x=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=50007;

ll n,m;
ll a[N];
struct node{
	ll mxl,mxr,mxs,sum;
}t[N*4];
node merge(node a,node b){
	node res;
	res.sum=a.sum+b.sum;
	res.mxs=max(a.mxr+b.mxl,max(a.mxs,b.mxs));
	res.mxl=max(a.mxl,a.sum+b.mxl);
	res.mxr=max(b.mxr,b.sum+a.mxr);
	return res;
}

void build(int rt,int l,int r){
	if(l==r){
		t[rt].sum=t[rt].mxl=t[rt].mxr=t[rt].mxs=a[l];
		return;
	}

	int mid=(l+r)>>1;
	build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
	t[rt]=merge(t[rt<<1],t[rt<<1|1]);
}

node query(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)
		return t[rt];
	node res;
	int mid=(l+r)>>1;
	if(qr<=mid) res=query(rt<<1,l,mid,ql,qr);
	else if(ql>mid) res=query(rt<<1|1,mid+1,r,ql,qr);
	else res=merge(query(rt<<1,l,mid,ql,qr),query(rt<<1|1,mid+1,r,ql,qr));
	return res;
}

int main(){
	n=input();
	for(int i=1;i<=n;i++) a[i]=input();
	build(1,1,n);
	m=input();
	for(int i=1;i<=m;i++){
		int l=input(),r=input();
		printf("%lld\n",query(1,1,n,l,r).mxs);
	}
}