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
}t[N];
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
	res=t[x].size+1;
	merge(rt,x,y);
	return res;
}

int pre(int &rt,int val){
	int x=0,y=0,res;
	split(rt,x,y,val-1);
	res=k_th(x,t[x].size);
	merge(rt,x,y);
	return res;
}

int suf(int &rt,int val){
	int x=0,y=0,res;
	split(rt,x,y,val);
	res=k_th(y,1);
	merge(rt,x,y);
	return res;
}

int n,rt;

int main(){
	srand(19260817);
	n=input();
	for(int i=1;i<=n;i++){
		int opr=input(),x=input();
		if(opr==1) Ins(rt,x);
		if(opr==2) erase(rt,x);
		if(opr==3) printf("%d\n",get_rank(rt,x));
		if(opr==4) printf("%d\n",k_th(rt,x));
		if(opr==5) printf("%d\n",pre(rt,x));
		if(opr==6) printf("%d\n",suf(rt,x));
	}
}