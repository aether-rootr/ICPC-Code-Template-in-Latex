#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=2e5+7;

struct edge{
	int _u,_v,v,w,next;
}e[N<<1];
int head[N],cnt;

void Ins(int u,int v){
	e[++cnt]=(edge){u,v,v,0,head[u]},head[u]=cnt;
	e[++cnt]=(edge){u,v,u,0,head[v]},head[v]=cnt;
}

int dp[N];
int Ans[N];

void dfs1(int u,int fa){
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w;
		if(e[i]._u==u&&e[i]._v==v) w=e[i].w=0;
		else w=e[i].w=1;
		if(v==fa) continue;
		dfs1(v,u);
		dp[u]+=dp[v]+w;
	}
}

void dfs2(int u,int fa){
	Ans[u]=dp[u];
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		int tmp1=dp[u],tmp2=dp[v];
		dp[u]=dp[u]-dp[v]-w;
		dp[v]=dp[v]+dp[u]+(!w);
		dfs2(v,u);
		dp[u]=tmp1;
		dp[v]=tmp2;
	}
}

vector<int> ans;

int main(){
	int n=input();

	for(int i=1;i<n;i++){
		int u=input(),v=input();
		Ins(u,v);
	}

	dfs1(1,0);
	dfs2(1,0);

	int mi=5e5;
	for(int i=1;i<=n;i++){
		if(Ans[i]<mi){
			mi=Ans[i];
			ans.clear();
			ans.push_back(i);
		}else if(Ans[i]==mi){
			ans.push_back(i);
		}
	}

	printf("%d\n",mi);
	for(int i=0;i<ans.size();i++) printf("%d%c",ans[i],i==ans.size()-1? '\n':' ');
}