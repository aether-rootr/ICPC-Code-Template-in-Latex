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


/////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<cstdio>
#define INF 19260817
using namespace std;
int input(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}
int n,m;
class segment_tree{
	public:
		int a[100007];	
		void build(int rootr,int l,int r){
			tree[rootr].l=l;tree[rootr].r=r;
			if(l==r){tree[rootr].MAX=tree[rootr].MIN=tree[rootr].tot=a[l];return;}
			int mid=(r-l>>1)+l;
			build(rootr*2,l,mid);
			build(rootr*2+1,mid+1,r);
			put(rootr);
		}
		int MAX=0,MIN=INF,tot=0;
		void query(int l,int r){
			MAX=0,MIN=INF,tot=0;
			getans(1,l,r);
		}
		void updata(int rootr,int l,int r,int add){
			int L=tree[rootr].l,R=tree[rootr].r;
			if(L>r||R<l)return;
			if(l<=L&&R<=r){tree[rootr].tot+=add*(R-L+1);tree[rootr].MAX+=add;tree[rootr].MIN+=add;tree[rootr].lazy+=add;return;}
			putdown(rootr);
			updata(rootr*2,l,r,add);
			updata(rootr*2+1,l,r,add);
			put(rootr);
		}
	private:
	struct node{
			int l,r,lazy,MAX,MIN,tot;
		}tree[200007];
	void put(int rootr){
		tree[rootr].MAX=tree[rootr*2].MAX>tree[rootr*2+1].MAX? tree[rootr*2].MAX:tree[rootr*2+1].MAX;
		tree[rootr].MIN=tree[rootr*2].MIN<tree[rootr*2+1].MIN? tree[rootr*2].MIN:tree[rootr*2+1].MIN;
		tree[rootr].tot=tree[rootr*2].tot+tree[rootr*2+1].tot;
	}
	void putdown(int rootr){
		if(tree[rootr].lazy!=0){
			tree[rootr*2].lazy+=tree[rootr].lazy;
			tree[rootr*2+1].lazy+=tree[rootr].lazy;
			tree[rootr*2].MAX+=tree[rootr].lazy;tree[rootr*2].MIN+=tree[rootr].lazy;
			tree[rootr*2+1].MAX+=tree[rootr].lazy;tree[rootr*2+1].MIN+=tree[rootr].lazy;
			tree[rootr*2].tot+=tree[rootr].lazy*(tree[rootr*2].r-tree[rootr*2].l+1);
			tree[rootr*2+1].tot+=tree[rootr].lazy*(tree[rootr*2+1].r-tree[rootr*2+1].l+1);
			tree[rootr].lazy=0;
		}
	}
	void getans(int rootr,int l,int r){
		int L=tree[rootr].l,R=tree[rootr].r;
		if(L>r||R<l)return;
		if(l<=L&&R<=r){tot+=tree[rootr].tot;MAX=MAX>tree[rootr].MAX?MAX:tree[rootr].MAX;MIN=MIN<tree[rootr].MIN?MIN:tree[rootr].MIN;return;}
		putdown(rootr);
		getans(rootr*2,l,r);
		getans(rootr*2+1,l,r);
		put(rootr);
	}
};
segment_tree tree1;
int main(){
	n=input();
	m=input();
	for(int i=1;i<=n;i++){
		tree1.a[i]=input();
	}
	tree1.build(1,1,n);
	int fl,a,b,c;
	for(int i=1;i<=m;i++){
		fl=input();a=input();b=input();
		if(fl==1){tree1.query(a,b);printf("%d\n%d\n%d\n",tree1.MIN,tree1.MAX,tree1.tot);}
		if(fl==2){c=input();tree1.updata(1,a,b,c);}
	}
	return 0;	

}

/*
10 10
1 2 3 4 5 6 7 8 9 10
	
*/