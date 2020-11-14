#include<iostream>
#include<cstdio>
#define mx(a,b) a>b? a:b
#define mi(a,b) a<b? a:b
#define INF 19260817
using namespace std;
int input(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}
struct edge{
	int to,next,w;
}map[20007];
struct stree{
	int l,r;
}stree[10007];
int head[10007];
int w[10007];
int c=0;
int size[10007],top[10007],fa[10007],deep[10007],son[10007],rank[10007],tid[10007];
void makemap(int x,int y){
	map[++c].to=y;
	map[c].next=head[x];
	head[x]=c;
}
void dfs1(int now,int father){
	deep[now]=deep[father]+1;
	size[now]=1;
	fa[now]=father;
	for(int i=head[now];i;i=map[i].next){
		if(map[i].to==father) continue;
		dfs1(map[i].to,now);
		size[now]+=size[map[i].to];
		if(!son[now]||size[map[i].to]>size[son[now]]) son[now]=map[i].to;
	}
}
int tim=0;
void dfs2(int now,int tp){
	top[now]=tp;
	tid[now]=++tim;
	rank[tid[now]]=w[now];
	stree[now].l=tim;
	if(!son[now]) return;
	dfs2(son[now],tp);
	for(int i=head[now];i;i=map[i].next){
		if(map[i].to==fa[now]||map[i].to==son[now]) continue;
		dfs2(map[i].to,map[i].to);
	}
	stree[now].r=tim;
}
class segment_tree{
	public:	
		void build(int rootr,int l,int r){
			tree[rootr].l=l;tree[rootr].r=r;
			if(l==r){tree[rootr].MX=tree[rootr].MI=tree[rootr].tot=rank[l];return;}
			int mid=(r-l>>1)+l;
			build(rootr*2,l,mid);
			build(rootr*2+1,mid+1,r);
			put(rootr);
		}
		int MX,MI,tot;
		void query(int l,int r){
			MX=0,MI=INF,tot=0;
			getans(1,l,r);
		}
		void updata(int rootr,int l,int r,int add){
			int L=tree[rootr].l,R=tree[rootr].r;
			if(L>r||R<l)return;
			if(l<=L&&R<=r){tree[rootr].tot+=add*(R-L);tree[rootr].MX+=add;tree[rootr].MI+=add;tree[rootr].lazy+=add;return;}
			putdown(rootr);
			updata(rootr*2,l,r,add);
			updata(rootr*2+1,l,r,add);
			put(rootr);
		}
	private:
	struct node{
			int l,r,lazy,MX,MI,tot;
		}tree[200007];
	void put(int rootr){
		tree[rootr].MX=tree[rootr*2].MX>tree[rootr*2+1].MX? tree[rootr*2].MX:tree[rootr*2+1].MX;
		tree[rootr].MI=tree[rootr*2].MI<tree[rootr*2+1].MI? tree[rootr*2].MI:tree[rootr*2+1].MI;
		tree[rootr].tot=tree[rootr*2].tot+tree[rootr*2+1].tot;
	}
	void putdown(int rootr){
		if(tree[rootr].lazy!=0){
			tree[rootr*2].lazy+=tree[rootr].lazy;
			tree[rootr*2+1].lazy+=tree[rootr].lazy;
			tree[rootr*2].MX+=tree[rootr].lazy;tree[rootr*2].MI+=tree[rootr].lazy;
			tree[rootr*2+1].MX+=tree[rootr].lazy;tree[rootr*2+1].MI+=tree[rootr].lazy;
			tree[rootr*2].tot+=tree[rootr].lazy*(tree[rootr*2].r-tree[rootr*2].l+1);
			tree[rootr*2+1].tot+=tree[rootr].lazy*(tree[rootr*2+1].r-tree[rootr*2+1].l+1);
			tree[rootr].lazy=0;
		}
	}
	void getans(int rootr,int l,int r){
		int L=tree[rootr].l,R=tree[rootr].r;
		if(L>r||R<l)return;
		if(l<=L&&R<=r){tot+=tree[rootr].tot;MX=MX>tree[rootr].MX?MX:tree[rootr].MX;MI=MI<tree[rootr].MI?MI:tree[rootr].MI;return;}
		putdown(rootr);
		getans(rootr*2,l,r);
		getans(rootr*2+1,l,r);
		put(rootr);
	}
};
segment_tree tree1;
namespace ttree{
	int cntT=0,cntX=0,cntI=INF;
	void up(){cntT+=tree1.tot;cntI=mi(cntI,tree1.MI);cntX=mx(cntX,tree1.MX);}
	void tquery(int u,int v){
		cntT=0;cntX=0;cntI=INF;
		while(top[u]!=top[v]){
			if(deep[top[u]]<deep[top[v]]) swap(u,v);
			tree1.query(tid[top[u]],tid[u]),up();
			u=fa[top[u]];
		}
		if(deep[u]<deep[v]) swap(u,v);
		tree1.query(tid[v],tid[u]),up;
	}
	void tupdata(int u,int v,int add){
		while(top[u]!=top[v]){
			if(deep[top[u]]<deep[top[v]]) swap(u,v);
			tree1.updata(1,tid[top[u]],tid[u],add);
			u=fa[top[u]];
		}
		if(deep[u]<deep[v]) swap(u,v);
		tree1.updata(1,tid[v],tid[u],add);
	}
	int lca(int u,int v){
		while(top[u]!=top[v]){
			if(deep[top[u]]<deep[top[v]]) swap(u,v);
			u=fa[top[u]];
		}
		return deep[u]>deep[v]? v:u;
	}
	void squery(int x){cntT=0;cntX=0;cntI=INF;tree1.query(stree[x].l,stree[x].r);}
	void supdata(int x,int add){tree1.updata(stree[x].l,stree[x].r,add);}
}
int n;
int main(){
	n=input();
	int x,y;
	for(int i=1;i<n;i++){
		x=input();
		y=input();
		makemap(x,y);
		makemap(y,x);
	}
	for(int i=1;i<=n;i++) w[i]=input();
	dfs1(1,0);dfs2(1,1);
	tree1.build(1,1,n);
	
	return 0;
}