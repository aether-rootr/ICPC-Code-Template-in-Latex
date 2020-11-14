//维护当前节点向下的最大值和次大值，并且用这些信息去更新向上的节点信息
// #include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=1e6+7;

struct edge{
	ll v,w,next;
}e[N<<1];
ll head[N],cnt=0;

void Ins(ll u,ll v,ll w){
	e[++cnt]=(edge){v,w,head[u]};head[u]=cnt;
	e[++cnt]=(edge){u,w,head[v]};head[v]=cnt;
}

ll dp[N][3];

void dfs(ll u,ll fa){
	for(ll i=head[u];i;i=e[i].next){
		ll v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		dfs(v,u);
		if(dp[v][0]+w>=dp[u][0]){
			dp[u][1]=dp[u][0];
			dp[u][0]=dp[v][0]+w;
		}else if(dp[v][0]+w>dp[u][1]){
			dp[u][1]=dp[v][0]+w;
		}
	}
}

void dfs2(ll u,ll fa){
	for(ll i=head[u];i;i=e[i].next){
		ll v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		if(dp[v][0]+w==dp[u][0]) dp[v][2]=max(dp[u][1],dp[u][2])+w;
		else dp[v][2]=max(dp[u][0],dp[u][2])+w;
		dfs2(v,u);
	}
}

ll ans[N];
ll Ans;

ll mx[N*4],mi[N*4];

void build(ll rt,ll l,ll r){
	if(l==r){
		mx[rt]=ans[l];mi[rt]=ans[l];
		return;
	}
	ll mid=(l+r)>>1;
	build(rt<<1,l,mid);build(rt<<1|1,mid+1,r);
	mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
	mi[rt]=min(mi[rt<<1],mi[rt<<1|1]);
}

ll querymx(ll rt,ll l,ll r,ll ql,ll qr){
	if(ql<=l&&r<=qr) return mx[rt];
	ll mid=(l+r)>>1;
	if(qr<=mid) return querymx(rt<<1,l,mid,ql,qr);
	if(mid<ql) return querymx(rt<<1|1,mid+1,r,ql,qr);
	return max(querymx(rt<<1,l,mid,ql,qr),querymx(rt<<1|1,mid+1,r,ql,qr));
}

ll querymi(ll rt,ll l,ll r,ll ql,ll qr){
	if(ql<=l&&r<=qr) return mi[rt];
	ll mid=(l+r)>>1;
	if(qr<=mid) return querymi(rt<<1,l,mid,ql,qr);
	if(mid<ql) return querymi(rt<<1|1,mid+1,r,ql,qr);
	return min(querymi(rt<<1,l,mid,ql,qr),querymi(rt<<1|1,mid+1,r,ql,qr));
}

int main(){
	ll n,m;
	while(~scanf("%lld%lld",&n,&m)){
		for(int i=1;i<=n;i++) head[i]=0;
		cnt=0;
		memset(dp,0,sizeof dp);

		for(ll i=2;i<=n;i++){
			ll fa=input(),w=input();
			Ins(i,fa,w);
		}

		dfs(1,0);
		dfs2(1,0);

		for(ll i=1;i<=n;i++){
			ans[i]=max(dp[i][0],dp[i][2]);
		}

		build(1,1,n);

		Ans=0;
		for(ll r=1,l=1;r<=n;r++){
			while(l<r&&querymx(1,1,n,l,r)-querymi(1,1,n,l,r)>m) l++;
			Ans=max(Ans,r-l+1);
		}

		printf("%lld\n",Ans);
	}	
}