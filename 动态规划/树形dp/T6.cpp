// 二分可以选的边的上限选择一些边进行dp，类似与例题5
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=1007;

int dp[N];

struct edge{
	int v,w,next;
}e[N<<1];
int head[N],cnt=0;

void Ins(int u,int v,int w){
	e[++cnt]=(edge){v,w,head[u]},head[u]=cnt;
	e[++cnt]=(edge){u,w,head[v]},head[v]=cnt;
}

void dfs(int u,int fa,int limit){
	dp[u]=0;int flag=0;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		flag=1;
		dfs(v,u,limit);
		if(w<=limit) dp[u]+=min(dp[v],w);
		else dp[u]+=dp[v];
	}
	if(!flag) dp[u]=1000001;
}

int main(){
	while(1){
		int n=input(),m=input();
		if(n==0&&m==0) break;
		for(int i=1;i<=n;i++){
			head[i]=0;
		}cnt=0;

		for(int i=1;i<n;i++){
			int u=input(),v=input(),w=input();
			Ins(u,v,w);
		}

		dfs(1,0,m);
		if(dp[1]>m){
			printf("-1\n");
			continue;
		}

		int l=1,r=m,Ans;
		while(l<=r){
			int mid=(l+r)>>1;
			dfs(1,0,mid);
			if(1<=dp[1]&&dp[1]<=m) Ans=mid,r=mid-1;
			else l=mid+1;
		}

		printf("%d\n",Ans);
	}
}