#include<iostream>
#include<cstdio>
#include<queue>
#define INF 19260817
using namespace std;
struct edge{
	int to,next,w;
}map[2007];
int head[1007]; 
int mapl[1007];//原点到i点的距离 
bool mapb[1007];//是否在队列中 
int c=0;
int n,m;
void makemap(int a,int b,int d){//建图 
	map[++c].to=b;
	map[c].w=d;
	map[c].next=head[a];
	head[a]=c;
}
void BEGIN(){//初始化
	for(int i=1;i<=n;i++){ 
		mapl[i]=INF; 
		mapb[i]=0;
		head[i]=-1;
	}
}
queue <int> q;
void spfa(int sta){
	int now;
	mapl[sta]=0;
	q.push(sta);
	while(!q.empty()){
		now=q.front();
		q.pop();
		mapb[now]=0;
		for(int i=head[now];i!=-1;i=map[i].next){
			if(map[i].to==now) continue; //双向边防止回到起始点 
			if(mapl[now]+map[i].w<mapl[map[i].to]){//松弛操作 
				mapl[map[i].to]=mapl[now]+map[i].w;
				if(mapb[map[i].to]==0){//判断是否入队 
					q.push(map[i].to);
					mapb[map[i].to]=1;
				}
			}
		}
	}
}
int main(){
	BEGIN();
	cin>>n>>m;
	int x,y,z;
	for(int i=1;i<=m;i++){
		cin>>x>>y>>z;
		makemap(x,y,z);
		makemap(y,x,z);//双向边存图 
	}
	spfa(1);
	for(int i=1;i<=n;i++) printf("%d ",mapl[i]);
}
