//二叉苹果树
//设f[u][i]表示uu的子树上保留ii条边，至多保留的苹果数目
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=107;

struct egde{
	int v,w,next;
}e[N*2];
int head[N],cnt=0;

void Ins(int u,int v,int w){
	e[++cnt]=(egde){v,w,head[u]},head[u]=cnt;
	e[++cnt]=(egde){u,w,head[v]},head[v]=cnt;
}

int siz[N];

int dp[N][N];

int n,q;

void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v]+1;
		for(int j=min(siz[u],q);j>=0;j--){
			for(int k=min(siz[v],j-1);k>=0;k--){
				dp[u][j]=max(dp[u][j],dp[u][j-k-1]+dp[v][k]+w);
			}
		}
	}
}

int main(){
	n=input(),q=input();

	for(int i=1;i<n;i++){
		int u=input(),v=input(),w=input();
		Ins(u,v,w);
	}

	dfs(1,0);

	printf("%d\n",dp[1][q]);
}