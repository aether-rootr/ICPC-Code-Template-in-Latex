#include <bits/stdc++.h>

using namespace std;

#define ll long long
int input(){
	int x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define N 107
const double eps=1e-4;
const int INF=1<<30;

double a[N],b[N],d[N];
struct edge{
	int v,next;
}e[2*N];
int head[N],tot;
double dp[N][N];
int siz[N];
int n,m;


void Ins(int u,int v){
	e[++tot]=(edge){v,head[u]},head[u]=tot;
	e[++tot]=(edge){u,head[v]},head[v]=tot;
}

void dfs(int x,int fa){
	dp[x][0]=0;
	siz[x]=1;
	for(int i=head[x];i;i=e[i].next){
		if(e[i].v==fa) continue;
		dfs(e[i].v,x);
		siz[x]+=siz[e[i].v];
		for(int j=min(siz[x],m);j>=0;j--){
			for(int k=0;k<=min(j,siz[x]);k++){
				dp[x][j]=max(dp[x][j-k]+dp[e[i].v][k],dp[x][j]);
			}
		}
	}
	for(int i=min(m,siz[x]);i>0;i--){
		dp[x][i]=dp[x][i-1]+d[x];
	}
}

bool check(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp[i][j]=-INF;
		}
	}

	dfs(1,0);

	double res=-INF;
	for(int i=1;i<=n;i++){
		res=max(dp[i][m],res);
	}

	return res>0;
}

int main(){
	n=input(),m=n-input();
	for(int i=1;i<=n;i++) a[i]=input();
	for(int i=1;i<=n;i++) b[i]=input();
	
	int u,v;
	for(int i=1;i<n;i++){
		u=input(),v=input();
		Ins(u,v);
	}

	double l=0.0,r=10000.0,mid;
	while(r-l>eps){
		mid=(l+r)/2;
		for(int i=1;i<=n;i++) d[i]=a[i]-mid*b[i];
		check()? l=mid:r=mid;
	}
	printf("%.1lf\n",mid);
}