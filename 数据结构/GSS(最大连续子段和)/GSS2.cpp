#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define ls rt<<1
#define rs rt<<1|1
#define N 800007

int n,m;
ll a[N],pre[N];
ll Ans[N];

struct seg{
	ll p,s,lazy,tag;
}t[N];

struct Q{
	int l,r,id;
	friend bool operator <(Q a,Q b){
		return a.r<b.r;
	}
}q[N];

void pushdown(int rt){
	if(!t[rt].tag&&!t[rt].lazy) return;
	t[ls].p=max(t[ls].p,t[ls].s+t[rt].lazy);
	t[ls].lazy=max(t[ls].lazy,t[ls].tag+t[rt].lazy);
	t[ls].s+=t[rt].tag,t[ls].tag+=t[rt].tag;
	t[rs].p=max(t[rs].p,t[rs].s+t[rt].lazy);
	t[rs].lazy=max(t[rs].lazy,t[rs].tag+t[rt].lazy);
	t[rs].s+=t[rt].tag;t[rs].tag+=t[rt].tag;
	t[rt].tag=0,t[rt].lazy=0;
}

void put(int rt){
	t[rt].s=max(t[ls].s,t[rs].s);
	t[rt].p=max(t[ls].p,t[rs].p);
}

void updata(int rt,int l,int r,int ul,int ur,int x){
	if(ul<=l&&r<=ur){
		t[rt].tag+=x,t[rt].s+=x;
		t[rt].lazy=max(t[rt].lazy,t[rt].tag);
		t[rt].p=max(t[rt].s,t[rt].p);
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(ul<=mid) updata(ls,l,mid,ul,ur,x);
	if(ur>mid) updata(rs,mid+1,r,ul,ur,x);
	put(rt);
}

ll query(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return t[rt].p;
	pushdown(rt);
	ll ans=-100005;
	int mid=(l+r)>>1;
	if(ql<=mid) ans=query(ls,l,mid,ql,qr);
	if(qr>mid) ans=max(ans,query(rs,mid+1,r,ql,qr));
	return ans;
}

int main(){
	n=input();
	for(int i=1;i<=n;i++) a[i]=input();

	m=input();
	for(int i=1;i<=m;i++){
		q[i].l=input(),q[i].r=input(),q[i].id=i;
	}

	sort(q+1,q+1+m);

	int tail=1;
	for(int i=1;i<=n;i++){
		if(tail>m) break;
		int tmp=a[i]+100005;
		updata(1,1,n,pre[tmp]+1,i,a[i]);
		pre[tmp]=i;
		while(q[tail].r==i) Ans[q[tail].id]=query(1,1,n,q[tail].l,i),tail++;
	}
	for(int i=1;i<=m;i++){
		printf("%lld\n",Ans[i]);
	}
}