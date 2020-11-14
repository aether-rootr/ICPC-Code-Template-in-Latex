#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=10007;

int n,m;
int a[N];

#define debug printf("PASS IN LINE:%d\n",__LINE__)

struct node{
	ll ls,rs,ms,ss;
}t[N*4];

node merge(node l,node r){
	node res;
	res.ss=l.ss+r.ss;
	res.ls=max(l.ls,l.ss+r.ls);
	res.rs=max(r.rs,l.rs+r.ss);
	res.ms=max(l.rs+r.ls,max(l.ms,r.ms));
	return res;
}

void build(int rt,int l,int r){
	if(l==r){
		t[rt].ls=t[rt].rs=t[rt].ss=t[rt].ms=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
	t[rt]=merge(t[rt<<1],t[rt<<1|1]);
}

node _query(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)
		return t[rt];
	int mid=(l+r)>>1;
	if(qr<=mid) return _query(rt<<1,l,mid,ql,qr);
	else if(ql>mid) return _query(rt<<1|1,mid+1,r,ql,qr);
	else return merge(_query(rt<<1,l,mid,ql,qr),_query(rt<<1|1,mid+1,r,ql,qr));
}

node query(int l,int r){
	if(l>r) return t[0];
	return _query(1,1,n,l,r);
}

int main(){
	int T=input();
	while(T--){
		n=input();
		for(int i=1;i<=n;i++) a[i]=input();
		build(1,1,n);
		m=input();
		for(int i=1;i<=m;i++){
			int x1=input(),y1=input(),x2=input(),y2=input();
			if(y1<x2)printf("%d\n",query(x1,y1).rs+query(y1+1,x2-1).ss+query(x2,y2).ls);
			else printf("%d\n",max(query(x2,y1).ms,max((query(x1,y1).rs+query(y1+1,y2).ls),(query(x1,x2-1).rs+query(x2,y2).ls))));
		}
	}
}