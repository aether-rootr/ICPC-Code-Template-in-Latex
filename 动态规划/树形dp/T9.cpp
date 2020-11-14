//同T8
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

struct edge{
	int v,w,next;
}e[N<<1];
int head[N],cnt=0;

void Ins(int u,int v,int w){
	e[++cnt]=(edge){v,w,head[u]},head[u]=cnt;
	e[++cnt]=(edge){u,w,head[v]},head[v]=cnt;
}

int val[N];
int dp_down[2][N],dp_up[2][N];

void dfs1(int u,int fa){
	dp_down[0][u]=dp_down[1][u]=val[u];
	for(int i=head[u];i;i=e[i].next){
		ll v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		dfs1(v,u);
		if(dp_down[0][v]-w*2>=0){
			dp_down[0][u]+=dp_down[0][v]-w*2;
		}
	}

	ll mx=0;
	for(int i=head[u];i;i=e[i].next){
		ll v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		if(dp_down[0][v]-2*w>0){
			mx=max(mx,(dp_down[1][v]-w)-(dp_down[0][v]-2*w));
		}else{
			mx=max(mx,dp_down[1][v]-w);
		}
	}
	dp_down[1][u]=dp_down[0][u]+mx;
}

void dfs2(int u,int fa){
	int mx1=0,mx2=0,tmp;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		if(dp_down[0][v]-2*w>0) tmp=(dp_down[1][v]-w)-(dp_down[0][v]-2*w);
		else tmp=dp_down[1][v]-w;
		if(mx1<tmp){
			mx2=mx1;
			mx1=tmp;
		}else if(mx2<tmp){
			mx2=tmp;
		}
	}

	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;

		int tmp2;
		if(dp_down[0][v]-2*w>0){
			tmp2=dp_down[0][u]-(dp_down[0][v]-2*w);
		}else{
			tmp2=dp_down[0][u];
		}

		int mx=max(dp_up[0][u]-2*w,tmp2-2*w);
		mx=max(mx,dp_up[0][u]+tmp2-2*w-val[u]);
		dp_up[0][v]=val[v]+max(0,mx);

		if(dp_down[0][v]-2*w>0){
			if(mx1==(dp_down[1][v]-w)-(dp_down[0][v]-2*w)) tmp=dp_down[1][u]-(dp_down[1][v]-w)+mx2;
			else tmp=dp_down[1][u]-(dp_down[0][v]-2*w);
		}else if(dp_down[1][v]-w>0){
			if(mx1==dp_down[1][v]-w) tmp=dp_down[1][u]-(dp_down[1][v]-w)+mx2;
			else tmp=dp_down[1][u];
		}else tmp=dp_down[1][u];
		mx=max(dp_up[1][u]-w,tmp-w);
		mx=max(mx,max(dp_up[0][u]+tmp-w-val[u],dp_up[1][u]+tmp2-w-val[u]));
		dp_up[1][v]=val[v]+max(0,mx);

		dfs2(v,u);
	}
}

int main(){
	int T=input(),cas=0;
	while(T--){
		memset(head,0,sizeof head);
		cnt=0;

		int n=input();
		for(int i=1;i<=n;i++) val[i]=input();

		for(int i=1;i<n;i++){
			int u=input(),v=input(),w=input();
			Ins(u,v,w);
		}

		dfs1(1,1);

		dp_up[0][1]=dp_up[1][1]=val[1];

		dfs2(1,1);

		printf("Case #%d:\n",++cas);

		for(int i=1;i<=n;i++){
			printf("%d\n",max(dp_up[0][i]+dp_down[1][i],dp_up[1][i]+dp_down[0][i])-val[i]);
		}
	}
}