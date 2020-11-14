#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=2007;

struct edge{
	int v,w,next;
}e[N<<1];
int head[N],cnt;

void Ins(int u,int v,int w){
	e[++cnt]=(edge){v,w,head[u]},head[u]=cnt;
	e[++cnt]=(edge){u,w,head[v]},head[v]=cnt;
}

ll dp[N][N];
int siz[N];
int n,m;

void dfs(int u,int fa){
	siz[u]=1;dp[u][0]=dp[u][1]=0;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		dfs(v,u);siz[u]+=siz[v];
		for(int j=min(siz[u],m);j>=0;j--){
			if(dp[u][j]!=-1) dp[u][j]+=dp[v][0]+1ll*siz[v]*(n-m-siz[v])*w;
			for(int k=min(siz[v],j);k>0;k--){
				if(dp[u][j-k]==-1) continue;
				ll tot=1ll*(m-k)*k+(n-m-(siz[v]-k))*(siz[v]-k);
				dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]+tot*w);
			}
		}
	}
}

int main(){
	memset(dp,-1,sizeof dp);

	n=input(),m=input();

	for(int i=1;i<n;i++){
		int u=input(),v=input(),w=input();

		Ins(u,v,w);
	}

	dfs(1,0);

	printf("%lld\n",dp[1][m]);
}