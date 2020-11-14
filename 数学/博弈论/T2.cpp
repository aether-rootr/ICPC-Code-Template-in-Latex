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

int sg[N],vis[N];
vector<int> G[N];

void dfs(int u,int fa){
	for(auto v:G[u]){
		if(v==fa) continue;
		dfs(v,u);
	}

	memset(vis,0,sizeof vis);
	for(auto v:G[u]){
		if(v==fa) continue;
		vis[sg[v]]=1;
	}

	for(int i=0;i<N;i++){
		if(!vis[i]){sg[u]=i;break;}
	}
}

int main(){
	int T=input();
	while(T--){
		int n=input(),r=input();
		for(int i=1;i<=n;i++){
			G[i].clear();
			sg[i]=0;
		}

		for(int i=1;i<n;i++){
			int u=input(),v=input();
			G[u].push_back(v),G[v].push_back(u);
		}

		dfs(r,0);

		if(sg[r]) printf("Gen\n");
		else printf("Dui\n");
	}
}