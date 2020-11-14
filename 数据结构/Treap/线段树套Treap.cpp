#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=5e4+7;
const int INF=0x7fffffff;

#define ls(x) t[x].ch[0]
#define rs(x) t[x].ch[1]

struct node{
	int ch[2],val,key,size;
}t[N*25];
int tot;

void put(int rt){
	t[rt].size=t[ls(rt)].size+t[rs(rt)].size+1;
}

void split(int rt,int &x,int &y,int val){
	if(!rt){x=y=0;return;}
	if(t[rt].val<=val) x=rt,split(rs(rt),rs(x),y,val);
	else y=rt,split(ls(rt),x,ls(y),val);
	put(rt);
}

void merge(int &rt,int x,int y){
	if(!x||!y){rt=x+y;return;}
	if(t[x].key<t[y].key) rt=x,merge(rs(rt),rs(x),y);
	else rt=y,merge(ls(rt),x,ls(y));
	put(rt);
}

void Ins(int &rt,int val){
	int x=0,y=0,z=++tot;
	t[z].size=1,t[z].val=val,t[z].key=rand();
	split(rt,x,y,val);
	merge(x,x,z);
	merge(rt,x,y);
}

void erase(int &rt,int val){
	int x=0,y=0,z=0;
	split(rt,x,y,val);
	split(x,x,z,val-1);
	merge(z,ls(z),rs(z));
	merge(x,x,z);
	merge(rt,x,y);
}

int k_th(int rt,int k){
	while(t[ls(rt)].size+1!=k){
		if(t[ls(rt)].size>=k) rt=ls(rt);
		else k-=(t[ls(rt)].size+1),rt=rs(rt);
	}
	return t[rt].val;
}

int get_rank(int &rt,int val){
	int x=0,y=0,res;
	split(rt,x,y,val-1);
	res=t[x].size;
	merge(rt,x,y);
	return res;
}

int pre(int &rt,int val){
	int x=0,y=0,res=-INF;
	split(rt,x,y,val-1);
	if(t[x].size) res=k_th(x,t[x].size);
	merge(rt,x,y);
	return res;
}

int suf(int &rt,int val){
	int x=0,y=0,res=INF;
	split(rt,x,y,val);
	if(t[y].size)res=k_th(y,1);
	merge(rt,x,y);
	return res;
}

int T[N<<2],a[N];

void Add(int rt,int l,int r,int pos,int val){
	Ins(T[rt],val);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) Add(rt<<1,l,mid,pos,val);
	else Add(rt<<1|1,mid+1,r,pos,val);
}

void Del(int rt,int l,int r,int pos,int val){
	erase(T[rt],val);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) Del(rt<<1,l,mid,pos,val);
	else Del(rt<<1|1,mid+1,r,pos,val);
}

int query_rank(int rt,int l,int r,int ql,int qr,int val){
	if(ql<=l&&r<=qr) return get_rank(T[rt],val);
	int mid=(l+r)>>1,res=0;
	if(mid>=ql) res+=query_rank(rt<<1,l,mid,ql,qr,val);
	if(mid<qr) res+=query_rank(rt<<1|1,mid+1,r,ql,qr,val);
	return res;
}

int query_pre(int rt,int l,int r,int ql,int qr,int val){
	if(ql<=l&&r<=qr) return pre(T[rt],val);
	int mid=(l+r)>>1,res=-INF;
	if(mid>=ql) res=max(res,query_pre(rt<<1,l,mid,ql,qr,val));
	if(mid<qr) res=max(res,query_pre(rt<<1|1,mid+1,r,ql,qr,val));
	return res;
}

int query_suf(int rt,int l,int r,int ql,int qr,int val){
	if(ql<=l&&r<=qr) return suf(T[rt],val);
	int mid=(l+r)>>1,res=INF;
	if(mid>=ql) res=min(res,query_suf(rt<<1,l,mid,ql,qr,val));
	if(mid<qr) res=min(res,query_suf(rt<<1|1,mid+1,r,ql,qr,val));
	return res;
}

int query_kth(int n,int ql,int qr,int k){
	int l=0,r=1e8;
	int res=0;
	while(l<r){
		int mid=(l+r+1)>>1;
		if(query_rank(1,1,n,ql,qr,mid)<k) l=mid;
		else r=mid-1;
	}
	return l;
}

int n,m,opr,l,r,k;

int main(){
	srand(19260817);
	n=input(),m=input();
	for(int i=1;i<=n;i++){
		a[i]=input();
		Add(1,1,n,i,a[i]);
	}

	for(int i=1;i<=m;i++){
		opr=input();
		if(opr==1){
			l=input(),r=input(),k=input();
			printf("%d\n",query_rank(1,1,n,l,r,k)+1);
		}
		if(opr==2){
			l=input(),r=input(),k=input();
			printf("%d\n",query_kth(n,l,r,k));
		}
		if(opr==3){
			l=input(),k=input();
			Del(1,1,n,l,a[l]);
			a[l]=k;
			Add(1,1,n,l,k);
		}
		if(opr==4){
			l=input(),r=input(),k=input();
			printf("%d\n",query_pre(1,1,n,l,r,k));
		}
		if(opr==5){
			l=input(),r=input(),k=input();
			printf("%d\n",query_suf(1,1,n,l,r,k));
		}
	}
}