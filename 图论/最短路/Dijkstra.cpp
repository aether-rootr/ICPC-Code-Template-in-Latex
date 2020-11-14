#include <bits/stdc++.h>

using namespace std;

inline int input(){
	int x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define N (int)1e5+7
#define clr(a,b) memset(a,b,sizeof a)

struct edge{int v,w,next;}e[5*N];
int head[N],Cnt=0;
int n,m,s;
int dis[N];
struct node{
	int u,d;
	bool operator <(const node& rhs) const {return d>rhs.d;}
};

void Ins(int u,int v,int w){
	e[++Cnt]=(edge){v,w,head[u]};
	head[u]=Cnt;
}

priority_queue <node> Q;

void Dijkstra(){
	clr(dis,0x3f);
	dis[s]=0;
	Q.push((node){s,0});
	while(!Q.empty()){
		node fr=Q.top(); Q.pop();
		int u=fr.u,d=fr.d,v,w;
		if(d!=dis[u]) continue;
		for(int i=head[u];i;i=e[i].next){
			if(dis[u]+(w=e[i].w)<dis[v=e[i].v])
				dis[v]=dis[u]+w,Q.push((node){v,dis[v]});
		}
	}
}

int main(){
	n=input(),m=input(),s=input();
	for(int i=1;i<=m;i++){
		int u=input(),v=input(),w=input();
		Ins(u,v,w);
	}
	Dijkstra();
	for(int i=1;i<=n;i++) printf("%d ",dis[i]);
	return 0;
}
