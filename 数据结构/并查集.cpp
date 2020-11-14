#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=1e4+7;

int fa[N],rk[N];
int find(int x){ return fa[x]==x? x:(fa[x]=find(fa[x]));} 
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x!=y){
		if(rk[x]>rk[y]) fa[y]=x,rk[x]+=rk[y];
		else fa[x]=y,rk[y]+=rk[x];
	}
}

int main(){
	int n=input(),m=input();
	for(int i=1;i<=n;i++){
		fa[i]=i,rk[i]=1;
	}

	while(m--){
		int t=input(),x=input(),y=input();
		if(t==1) merge(x,y);
		else{
			if(find(x)==find(y)) printf("Y\n");
			else printf("N\n");
		}
	}
}