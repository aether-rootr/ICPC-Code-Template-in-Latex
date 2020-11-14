#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int input(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}
int n,m;
class bcj{
	public:
		void BEGIN(){
			for(int i=1;i<=n;i++){
				fa[i]=i;
				rank[i]=1;
			}
		}
		int find(int x){return x==fa[x]? x:(fa[x]=find(fa[x]));}
		int merge(int x,int y){
			x=find(x);y=find(y);
			x==y? 0:(rank[x]>=rank[y]? (fa[y]=x,rank[x]+=rank[y]):(fa[x]=y,rank[y]+=rank[x]));
			return rank[x]>=rank[y]? rank[x]:rank[y];
		}
	private:
		int fa[1007],rank[1007];
};
bcj bcj_;
struct edge{
	int from,w,to;
}map[2024];
struct mst{
	int next,w,to;
}tree[2024];
int head[1024];
int c=0;
int cnt=0;
bool cmp(edge a,edge b){
	return a.w<b.w;
}
void makemap(int x,int y,int z){
	tree[++c].to=y;
	tree[c].w=z;
	tree[c].next=head[x];
	head[x]=c;
}
void kruskal(){
	int size=0,now=1;
	while(size<n){
		if(bcj_.find(map[now].from)!=bcj_.find(map[now].to)){
			size=bcj_.merge(map[now].from,map[now].to);
			cnt+=map[now].w;
			makemap(map[now].from,map[now].to,map[now].w);makemap(map[now].to,map[now].from,map[now].w);
		}
		now++;
	}
}
int main(){
	n=input();m=input();
	bcj_.BEGIN();
	for(int i=1;i<=m;i++){
		map[i].from=input();map[i].to=input();map[i].w=input();
	}
	sort(map+1,map+1+n,cmp);
	kruskal();
	cout<<cnt<<endl;
}