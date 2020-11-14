#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=507;

#define pb push_back

vector<int> G[N*2];
int n,m,e;
int match[N*2],vis[N*2];


bool dfs(int u){
	for(auto v:G[u]){
		if(!vis[v]){// 要求不在交替路中
			vis[v]=1;// 放入交替路
			if(!match[v]||dfs(match[v])){ // 如果是未盖点，说明交替路为增广路，则交换路径，并返回成功
				match[v]=u,match[u]=v;
				return 1;
			}
		}
	}
	return 0;
}

int main(){
	n=input(),m=input(),e=input();

	for(int i=1;i<=e;i++){
		int u=input(),v=input()+n;
		G[u].pb(v),G[v].pb(u);
	}

	int Ans=0;
	for(int i=1;i<=n;i++){
		if(!match[i]){
			memset(vis,0,sizeof(vis));
			if(dfs(i)) Ans++;
		}

	}

	printf("%d\n",Ans);
}