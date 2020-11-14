#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct node{
	int next;
	int to;
}map[6014];
int head[3007];
int c=1;
int p[3007][13]={0};
int n;
int deep[3007]={0};
int bcj[3007];
void makemap(int x,int y){
	map[c].next=head[x];
	map[c].to=y;
	head[x]=c;
	c++;
}
void init(){
	int i,j;
	for(j=1;(1<<j)<=n;j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=0){
				p[i][j]=p[p[i][j-1]][j-1];
			}
		}
	}
}
void dfs(int u){
	for(int i=head[u]; i ;i=map[i].next){
		if(deep[map[i].to]==0){
			deep[map[i].to]=deep[u]+1;
			p[map[i].to][0]=u;
			dfs(map[i].to);
		}
	}
}
int lca(int a,int b){
	int i,j;
    if(deep[a]<deep[b])swap(a,b);
    for(i=0;(1<<i)<=deep[a];i++);
    i--;
    for(j=i;j>=0;j--)
        if(deep[a]-(1<<j)>=deep[b])
            a=p[a][j];
    if(a==b)return a;
    for(j=i;j>=0;j--)
    {
        if(p[a][j]!=0&&p[a][j]!=p[b][j])
        {
            a=p[a][j];
            b=p[b][j];
        }
    }
    return p[a][0];
}
int main(){
	cin>>n;
	int x,y;
	for(int i=1;i<=n;i++){
		bcj[i]=i;
	}
	for(int i=1;i<n;i++){
		cin>>x>>y;
		bcj[x]=bcj[y];
		makemap(y,x);
	}
	dfs(bcj[1]);
	init();
	int a,b,t;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>a>>b;
		cout<<lca(a,b)<<endl;
	}
	return 0;
}