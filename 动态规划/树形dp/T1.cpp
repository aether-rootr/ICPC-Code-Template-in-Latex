#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define debug printf("PASS IN LINE:%d\n",__LINE__)

const int N=1e5+7;

struct node{
	int x,y,len;
}d[N];

vector <int> G[N];

vector <node> nxt[N];

int ans[N];

void Ins(int u,int v){
	G[u].push_back(v);
	G[v].push_back(u);
}

int top[N],dep[N],fa[N],siz[N],son[N];;

namespace LCA{
	void dfs1(int now,int father){
		dep[now]=dep[father]+1;
		siz[now]=1;
		fa[now]=father;
		for(auto v:G[now]){
			if(v==father) continue;
			dfs1(v,now);
			siz[now]+=siz[v];
			if(!son[now]||siz[v]>siz[son[now]])
				son[now]=v;
		}
	}

	void dfs2(int now,int tp){
		top[now]=tp;
		if(!son[now]) return;
		dfs2(son[now],tp);
		for(auto v:G[now]){
			if(v==fa[now]||v==son[now]) continue;
			dfs2(v,v);
		}
	}
}


int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]>dep[v]? v:u;
}

int dis(int u,int v){
	return dep[u]+dep[v]-2*dep[lca(u,v)]+1;
}

node merge(node a,node b){
	node tmp=a.len>b.len? a:b;

	if(dis(a.x,b.y)>tmp.len)
		tmp=(node){a.x,b.y,dis(a.x,b.y)};
	
	if(dis(a.x,b.x)>tmp.len)
		tmp=(node){a.x,b.x,dis(a.x,b.x)};
	
	if(dis(a.y,b.y)>tmp.len)
		tmp=(node){a.y,b.y,dis(a.y,b.y)};
	
	if(dis(a.y,b.x)>tmp.len)
		tmp=(node){a.y,b.x,dis(a.y,b.x)};
	
	return tmp;
}

void dfs1(int u){
	d[u]=(node){u,u,1};
	for(auto v:G[u]){
		if(v==fa[u]) continue;
		dfs1(v);
		d[u]=merge(d[u],d[v]);
	}
}

void putans(int x,int y){
	if(x>y) swap(x,y);
	ans[x]=max(ans[x],y);
}

void dfs2(int u){
	nxt[u].push_back(d[u]);
	for(int i=G[u].size()-1;i>=0;i--){
		if(G[u][i]==fa[u])continue;
		nxt[u].push_back(merge(nxt[u][nxt[u].size()-1],d[G[u][i]]));
	}

	node pre=d[u];
	int i=nxt[u].size()-2;
	for(auto v:G[u]){
		if(v==fa[u]) continue;
		node tmp=merge(pre,nxt[u][i]);
		putans(d[v].len,tmp.len);
		pre=merge(pre,d[v]);
		d[v]=merge(tmp,(node){v,v,1});
		dfs2(v);
		i--;
	}
}

int main(){
	int T=input();
	while(T--){
		int n=input();
		
		for(int i=1;i<=n+3;i++)
			G[i].clear(),nxt[i].clear(),ans[i]=0,son[i]=0;

		for(int i=1;i<n;i++){
			int u=input(),v=input();
			Ins(u,v);
		}

		LCA::dfs1(1,-1);
		LCA::dfs2(1,1);

		dfs1(1);
		d[1]=(node){1,1,1};
		dfs2(1);

		ll Ans=0;
		for(int i=n;i;i--){
			ans[i]=max(ans[i],ans[i+1]);
			if(ans[i]) Ans+=1+(ans[i]-i)*2;
		}
		

		printf("%lld\n",Ans);
	}
}