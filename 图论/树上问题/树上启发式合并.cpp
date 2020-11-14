/*
树上启发式合并相当于对于每个点将其儿子按照轻重儿子进行划分。
对于当前节点来说首先向下递归计算以当前点的轻儿子为根子树的答案，并且按照相同的策略划分轻重儿子，然后清空信息。
再向下递归重儿子，并且采取相同的策略计算以重儿子为根子树的答案，并且保留信息。
树上启发式合并就是通过共用信息，来保证复杂度的。
一般来说树上启发式合并只需要根据题目修改calc()函数即可
*/
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
 
int c[N];
 
vector<int> G[N];
int siz[N],son[N];
 
void dfs(int u,int fa){
	siz[u]=1;
	for(auto v:G[u]){
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
 
ll Ans[N],col[N];
ll ans,mx=0;
vector<int> d;
 
void update(int x,int cl){
	// cout<<x<<" "<<cl<<endl;
	if(x>mx) mx=x,ans=cl;
	else if(x==mx) ans+=cl;
}
 
void dfs1(int u,int fa){
	col[c[u]]++;
	update(col[c[u]],c[u]);
	d.push_back(u);
	for(auto v:G[u]){
		if(v==fa) continue;
		dfs1(v,u);
	}
}
 
void calc(int u,int fa,int ch){
	col[c[u]]++;//把当前节点信息加入信息维护数组
	update(col[c[u]],c[u]);//更新答案
	d.push_back(u);//维护dfs序
 
	for(auto v:G[u]){//遍历轻儿子计算答案
		if(v==fa||v==ch) continue;
		dfs1(v,u);
	}
}
 
void Solve(int u,int fa,int flag){
	for(auto v:G[u]){//遍历轻儿子
		if(v==fa||v==son[u]) continue;
		Solve(v,u,1);
	}
	if(son[u]) Solve(son[u],u,0);//递归重儿子
 
	calc(u,fa,son[u]);//计算当前节点的答案，当前节点的重儿子已经计算（被保留），所以只需要算轻儿子
 
	Ans[u]=ans;
 
	if(flag){//如果当前为轻儿子
		//清空对答案数组的影响，这里利用dfs序来维护哪些节点需要清空，无需向下进行dfs
		for(auto t:d){
			col[c[t]]--;
		}
		d.clear();//dfs序数组清空
		ans=mx=0;
	}
}
 
int main(){
	int n=input();
 
	for(int i=1;i<=n;i++) c[i]=input();
 
	for(int i=1;i<n;i++){
		int u=input(),v=input();
		G[u].push_back(v);
		G[v].push_back(u);
	}
 
	dfs(1,0);
	Solve(1,0,0);
 
	for(int i=1;i<=n;i++){
		printf("%lld%c",Ans[i],i==n? '\n':' ');
	}
}

///////////////////////////////////////////////////


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

ll son[N],color[N],all[N],a[N],siz[N],Fa[N];
ll Ans[N];

struct edge{
	int v,next;
}e[N<<1];

int head[N],cnt=0;

void Ins(int u,int v){
	e[++cnt]=(edge){v,head[u]},head[u]=cnt;
	e[++cnt]=(edge){u,head[v]},head[v]=cnt;
}

void dfs(int u,int fa){
	siz[u]=1;Fa[u]=fa;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v]) son[u]=v;
	}
}

int ans=0;

void work(int u,int fa,int x,int ch){
	all[a[u]]-=x;
	if(color[a[u]]&&!all[a[u]]) ans--;
	if(!color[a[u]]&&all[a[u]]) ans++;
	color[a[u]]+=x;

	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa||v==ch) continue;
		work(v,u,x,ch);
	}
}

void dfs1(int u,int fa,bool flag){
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa||v==son[u]) continue;
		dfs1(v,u,1);
	}
	if(son[u]) dfs1(son[u],u,0);

	work(u,fa,1,son[u]);
	
	Ans[u]=ans;

	if(flag){
		work(u,fa,-1,0);
		ans=0;
	}
}

#define PII pair <int,int>
#define fr first
#define sc second
#define mp make_pair

vector<PII> E;

int main(){
	int n;
	while(~scanf("%d",&n)){
		E.clear();

		cnt=0;
		for(int i=0;i<=n;i++){
			color[i]=son[i]=all[i]=head[i]=0;
		}
		for(int i=1;i<=n;i++) a[i]=input(),all[a[i]]++;

		for(int i=1;i<n;i++){
			int u=input(),v=input();
			Ins(u,v);
			E.push_back(mp(u,v));
		}

		dfs(1,0);
		dfs1(1,0,0);

		for(auto t:E){
			int u=t.fr,v=t.sc;
			if(Fa[v]==u) swap(u,v);
			printf("%lld\n",Ans[u]);
		}
	}
}