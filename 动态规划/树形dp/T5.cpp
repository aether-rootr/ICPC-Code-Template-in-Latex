#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=5e5+7;

struct edge{
	ll v,w,next;
}e[N<<1];

int head[N],cnt;

void Ins(int u,int v,int w){
	e[++cnt]=(edge){v,w,head[u]},head[u]=cnt;
	e[++cnt]=(edge){u,w,head[v]},head[v]=cnt;
}

ll dp[N],Ans=0;

void dfs(int u,int fa){
	dp[u]=0;
	for(int i=head[u];i;i=e[i].next){
		ll v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		dfs(v,u);
		dp[u]=max(dp[u],dp[v]+w);
	}

	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		Ans+=dp[u]-(dp[v]+w);	
	}
}

int main(){
	int n=input(),s=input();

	for(int i=1;i<n;i++){
		int u=input(),v=input(),w=input();
		Ins(u,v,w);
	}

	dfs(s,0);

	printf("%lld\n",Ans);
}