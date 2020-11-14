#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define PII pair<int,int>
#define fr first
#define sc second
#define mp make_pair
#define debug printf("PASS IN LINE %d\n",__LINE__)

const int N=10007;

vector<PII> G[N];

int n,m,k;
int rt,siz[N],f[N],dep[N],size,Ans;
vector <int> d;
bool vis[N];

void getrt(int u,int fa){
	siz[u]=1,f[u]=0;
	for(auto v:G[u]){
		if(v.fr==fa||vis[v.fr]) continue;
		getrt(v.fr,u);
		siz[u]+=siz[v.fr];
		f[u]=max(f[u],siz[v.fr]);
	}
	f[u]=max(f[u],size-siz[u]);
	if(f[u]<f[rt]) rt=u;
}

void getdep(int u,int fa){
	d.push_back(dep[u]);
	siz[u]=1;
	for(auto v:G[u]){
		if(vis[v.fr]||v.fr==fa) continue;
		dep[v.fr]=dep[u]+v.sc;
		getdep(v.fr,u);
		siz[u]+=siz[v.fr];
	}
}

int calc(int u,int init){
	d.clear(),dep[u]=init;
	getdep(u,0);
	sort(d.begin(),d.end());
	int res=0;
	for(int l=0,r=d.size()-1;l<r;)
		if(d[l]+d[r]<=k) res+=r-l++;
		else r--;
	return res;
}

void Solve(int u){
	Ans+=calc(u,0);
	vis[u]=1;
	for(auto v:G[u]){
		if(vis[v.fr]) continue;
		Ans-=calc(v.fr,v.sc);
		f[0]=size=siz[u];
		getrt(v.fr,rt=0);
		Solve(rt);
	}
}

int main(){
	n=input(),k=input();
	for(int i=1;i<=n;i++) G[i].clear();d.clear();
	memset(vis,0,sizeof vis);
	for(int i=1;i<n;i++){
		int u=input(),v=input(),w=input();
		G[u].push_back(mp(v,w));
		G[v].push_back(mp(u,w));
	}
	f[0]=size=n;
	getrt(1,rt=0);
	Ans=0;
	Solve(rt);
	printf("%d\n",Ans);
}


////////////////////////////////////////


// poj 1741

//求长度小于等于k的边的数量
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define PII pair<int,int>
#define fr first
#define sc second
#define mp make_pair
#define debug printf("PASS IN LINE %d\n",__LINE__)

const int N=10007;

vector<PII> G[N];

int n,m,k;
int rt,siz[N],f[N],dep[N],size,Ans;
vector <int> d;
bool vis[N];

void getrt(int u,int fa){
	siz[u]=1,f[u]=0;
	for(auto v:G[u]){
	for(int i=0;i<G[u].size();i++){
		PII v=G[u][i];
		if(v.fr==fa||vis[v.fr]) continue;
		getrt(v.fr,u);
		siz[u]+=siz[v.fr];
		f[u]=max(f[u],siz[v.fr]);
	}
	f[u]=max(f[u],size-siz[u]);
	if(f[u]<f[rt]) rt=u;
}

void getdep(int u,int fa){
	d.push_back(dep[u]);
	siz[u]=1;
	for(auto v:G[u]){
	for(int i=0;i<G[u].size();i++){
		PII v=G[u][i];
		if(vis[v.fr]||v.fr==fa) continue;
		dep[v.fr]=dep[u]+v.sc;
		getdep(v.fr,u);
		siz[u]+=siz[v.fr];
	}
}

int calc(int u,int init){
	d.clear(),dep[u]=init;
	getdep(u,0);
	sort(d.begin(),d.end());
	int res=0;
	for(int l=0,r=d.size()-1;l<r;)
		if(d[l]+d[r]<=k) res+=r-l++;
		else r--;
	return res;
}

void Solve(int u){
	Ans+=calc(u,0);
	vis[u]=1;
	for(auto v:G[u]){
	for(int i=0;i<G[u].size();i++){
		PII v=G[u][i];
		if(vis[v.fr]) continue;
		Ans-=calc(v.fr,v.sc);
		f[0]=size=siz[u];
		getrt(v.fr,rt=0);
		Solve(rt);
	}
}

int main(){
	while(1){
		n=input(),k=input();
		if(!n&&!k) break;
		for(int i=1;i<=n;i++) G[i].clear();d.clear();
		memset(vis,0,sizeof vis);
		for(int i=1;i<n;i++){
			int u=input(),v=input(),w=input();
			G[u].push_back(mp(v,w));
			G[v].push_back(mp(u,w));
		}
		f[0]=size=n;
		getrt(1,rt=0);
		Ans=0;
		Solve(rt);
		printf("%d\n",Ans);
	}
}