//区间翻转
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

#define ls(x) t[x].ch[0]
#define rs(x) t[x].ch[1]

struct node{
	int ch[2],val,key,size;
	bool rev;
}t[N];
int tot;

int newnode(int val){
	t[++tot].val=val;
	t[tot].key=rand();
	t[tot].size=1;
	t[tot].rev=0;
	return tot;
}

void put(int rt){
	t[rt].size=t[ls(rt)].size+t[rs(rt)].size+1;
}

void putdown(int rt){
	swap(ls(rt),rs(rt));
	t[ls(rt)].rev^=1;
	t[rs(rt)].rev^=1;
	t[rt].rev=0;
}

void split(int rt,int &x,int &y,int siz){
	if(!rt){x=y=0;return;}
	if(t[rt].rev) putdown(rt);
	if(t[ls(rt)].size<siz) x=rt,split(rs(rt),rs(x),y,siz-t[ls(rt)].size-1);
	else y=rt,split(ls(rt),x,ls(y),siz);
	put(rt);
}

void merge(int &rt,int x,int y){
	if(!x||!y){rt=x+y;return;}
	if(t[x].key<t[y].key){
		if(t[x].rev) putdown(x);
		rt=x,merge(rs(rt),rs(x),y);
	}
	else{
		if(t[y].rev) putdown(y);
		rt=y,merge(ls(rt),x,ls(y));
	}
	put(rt);
}

void reverse(int &rt,int l,int r){
	int x=0,y=0,z=0;
	split(rt,x,y,l-1);
	split(y,y,z,r-l+1);
	t[y].rev^=1;
	merge(y,y,z);
	merge(rt,x,y);
}

void dfs(int now){
	if(!now) return;
	if(t[now].rev) putdown(now);
	dfs(ls(now));
	printf("%d ",t[now].val);
	dfs(rs(now));
}

int n,m,rt;

int main(){
	srand(19260817);
	n=input(),m=input();
	for(int i=1;i<=n;i++){
		merge(rt,rt,newnode(i));
	}

	for(int i=1;i<=m;i++){
		int l=input(),r=input();
		reverse(rt,l,r);
	}
	dfs(rt);
}