// dijkstra
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x; 
}

const int N=5007;
const int INF=0x3f3f3f3f;
#define PII pair <int,int> 
#define fr first
#define sc second
#define mp make_pair

struct MinCostFlow{
	struct edge{
		int v,f,c,r;
		edge(int _v, int _f, int _c, int _r) :v(_v), f(_f), c(_c), r(_r) {}
	};
	int V=0,h[N],dis[N],pv[N],pe[N];
	vector <edge> G[N];

	inline void init(int n){
		for(int i=0;i<=V;i++) G[i].clear();
		V=n;	
	}

	inline void Ins(int u,int v,int f,int c){
		G[u].push_back(edge(v,f,c,G[v].size() ));
		G[v].push_back(edge(u,0,-c,G[u].size()-1 ));
	}

	PII MCMF(int s,int t,int Flow){
		int cost=0,flow=0,newflow;fill(h,h+1+V,0);
		while(Flow){
			priority_queue <PII,vector<PII>,greater<PII> > Q;
			fill(dis,dis+V+1,INF);
			dis[s]=0,Q.push(mp(0,s));
			while(!Q.empty()){
				PII now=Q.top();Q.pop();
				int u=now.sc;
				if(dis[u]<now.fr) continue;
				for(int i=0;i<G[u].size();i++){
					edge &e=G[u][i];
					if(e.f>0&&dis[e.v]>dis[u]+e.c+h[u]-h[e.v]){
						dis[e.v]=dis[u]+e.c+h[u]-h[e.v];
						pv[e.v]=u,pe[e.v]=i;
						Q.push(PII(dis[e.v],e.v));
					}
				}
			}
			if(dis[t]==INF) break;
			for(int i=0;i<=V;i++) h[i]+=dis[i];
			newflow=Flow;
			for(int x=t;x!=s;x=pv[x]) newflow=min(newflow,G[pv[x]][pe[x]].f);
			Flow-=newflow,flow+=newflow,cost+=newflow*h[t];
			for(int x=t;x!=s;x=pv[x]){
				edge &e=G[pv[x]][pe[x]];
				e.f-=newflow;
				G[x][e.r].f+=newflow;
			}
		}
		return mp(flow,cost);
	}
}A;

int main(){
	int n=input(),m=input(),s=input(),t=input();
	A.init(n);
	for(int i=1;i<=m;i++){
		int u=input(),v=input(),w=input(),c=input();
		A.Ins(u,v,w,c);
	}
	PII Ans=A.MCMF(s,t,INF);
	printf("%d %d\n",Ans.fr,Ans.sc);
}

////////////////////////////////////////////////////////////////////////////////

//spfa
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x; 
}

const int N=5007;
const int M=50007;
#define clr(a,b) memset(a,b,sizeof(a))
#define PII pair <int,int> 
#define fr first
#define sc second
#define mp make_pair
#define debug printf("PASS IN LINE:%d\n",__LINE__)

struct edge{
	int v,w,c,next;
}e[M*2];
int head[N],cnt=-1;
int n,m;

void Ins(int u,int v, int w,int c){
	e[++cnt]=(edge){v,w,c,head[u]},head[u]=cnt;
	e[++cnt]=(edge){u,0,-c,head[v]},head[v]=cnt;
}

PII MCMF(int s,int t){
	int dis[N],pv[N],pe[N],flow[N],maxflow=0,mincost=0;
	bool vis[N];
	queue <int> q;
	while(1){
		clr(dis,0x3f),clr(flow,0x3f),clr(vis,0);
		q.push(s),vis[s]=1,dis[s]=0,pv[t]=-1;
		while(!q.empty()){
			int now=q.front();q.pop();
			vis[now]=0;
			for(int i=head[now];~i;i=e[i].next){
				if(e[i].w&&dis[now]+e[i].c<dis[e[i].v]){
					dis[e[i].v]=dis[now]+e[i].c;
					pv[e[i].v]=now,pe[e[i].v]=i;
					flow[e[i].v]=min(flow[now],e[i].w);
					if(!vis[e[i].v]){
						vis[e[i].v]=1;
						q.push(e[i].v);
					}
				}
			}
		}
		
		if(pv[t]==-1) break;
		
		maxflow+=flow[t];
		mincost+=flow[t]*dis[t];

		for(int x=t;x!=s;x=pv[x]) e[pe[x]].w-=flow[t],e[pe[x]^1].w+=flow[t];
	}
	return mp(maxflow,mincost);
}

int main(){
	clr(head,-1),clr(e,-1),cnt=-1;
	int s,t;
	n=input(),m=input(),s=input(),t=input();
	for(int i=1;i<=m;i++){
		int u=input(),v=input(),w=input(),c=input();
		Ins(u,v,w,c);
	}
	PII Ans=MCMF(s,t);
	printf("%d %d\n",Ans.fr,Ans.sc);

}

/////////////////////////////////////////////////////////////////////////////


//MCMF->init(N) -> MCMF.add(u,v,flow,cost) -> (flow,cost) = MCMF.run(s,t,UP)
//其中UP参数表示求s到t的流量不超过UP的情况下的最小费用，无要求填INF即可
//所有节点的id范围[0,N]
const int MAXN = 10005;
const int INF = 0x7fffffff;
struct MinCostMaxFlow {
	struct edge {
		int v, f, c, r;
		edge(int _v, int _f, int _c, int _r) :v(_v), f(_f), c(_c), r(_r) {}
	};
	int V = 0, H[MAXN + 5], dis[MAXN + 5], PreV[MAXN + 5], PreE[MAXN + 5];
	vector<edge> G[MAXN + 5];
	inline void init(int n) {
		for (int i = 0; i <= V; ++i) G[i].clear();
		V = n;
	}
	inline void add(int u, int v, int f, int c) {
		G[u].push_back(edge(v, f, c, G[v].size()));
		G[v].push_back(edge(u, 0, -c, G[u].size() - 1));
	}
	typedef pair<int, int> P;
	P run(int s, int t, int f) {
		int cost = 0, flow = 0, tf; fill(H, H + 1 + V, 0);
		while (f) {
			priority_queue <P, vector<P>, greater<P> > q;
			fill(dis, dis + 1 + V, INF);
			dis[s] = 0; q.push(P(0, s));
			while (!q.empty()) {
				P now = q.top(); q.pop();
				int v = now.second;
				if (dis[v] < now.first)continue;
				for (int i = 0; i < G[v].size(); ++i) {
					edge& e = G[v][i];
					if (e.f > 0 && dis[e.v] > dis[v] + e.c + H[v] - H[e.v]) {
						dis[e.v] = dis[v] + e.c + H[v] - H[e.v];
						PreV[e.v] = v, PreE[e.v] = i;
						q.push(P(dis[e.v], e.v));
					}
				}
			}
			if (dis[t] == INF)break;
			for (int i = 0; i <= V; ++i) H[i] += dis[i];
			tf = f;
			for (int v = t; v != s; v = PreV[v])
				tf = min(tf, G[PreV[v]][PreE[v]].f);
			f -= tf, flow += tf, cost += tf*H[t];
			for (int v = t; v != s; v = PreV[v]) {
				edge& e = G[PreV[v]][PreE[v]];
				e.f -= tf;
				G[v][e.r].f += tf;
			}
		}
		return P(flow, cost);
	}
}MCMF;