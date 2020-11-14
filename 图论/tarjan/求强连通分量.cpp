#include <bits/stdc++.h>

using namespace std;

int input(){
    int x=0,f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

#define N (int)1e6

int dfn[N],low[N],color[N];
bool vis[N];
stack <int> s;
int n,m;
struct edge{
    int v,next;
}e[N];
int head[N],top=0,col=0;

void Ins(int u,int v){
    e[++top]=(edge){v,head[u]},head[u]=top;
}

int dep=0;

void tarjan(int x){
    dfn[x]=++dep;
    low[x]=dep;
    vis[x]=1;
    s.push(x);
    for(int i=head[x];i;i=e[i].next){
        // cout<<x<<" "<<e[i].v<<endl;
        if(!dfn[e[i].v]){
            tarjan(e[i].v);
            low[x]=min(low[e[i].v],low[x]);
        }else if(vis[e[i].v]){
            low[x]=min(low[e[i].v],low[x]);
        }
    }
    if(dfn[x]==low[x]){
        color[x]=++col;
        vis[x]=0;
        while(s.top()!=x){
            color[s.top()]=col;
            vis[s.top()]=0;
            s.pop();
        }
        s.pop();
    }
}

int main(){
    n=input(),m=input();
    int u,v;
    for(int i=1;i<=m;i++){
        u=input(),v=input();
        Ins(u,v);
    }
    tarjan(1);
    for(int i=1;i<=n;i++){
        printf("%d ",color[i]);
    }
    printf("\n");
    return 0;
}