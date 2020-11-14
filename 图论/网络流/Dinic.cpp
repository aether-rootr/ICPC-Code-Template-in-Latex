#include <bits/stdc++.h>

using namespace std;

int input(){
    int x=0,f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f? -x:x;
}

#define N 20007
#define M 200007
#define INF 999999999
#define clr(a,b) memset(a,b,sizeof(a))

int n,m,s,t;
int cnt=0;
int head[N];
int dis[N],q[N];
struct edge{
    int v,w,next;
}e[M];

void Ins(int u,int v,int w){
    e[cnt]=(edge){v,w,head[u]};head[u]=cnt++;
    e[cnt]=(edge){u,0,head[v]};head[v]=cnt++;
}

int MkLevel(){
    int x,l=0,r=0;
    clr(dis,0);
    dis[s]=1,q[r++]=s;
    while(l<r){
        x=q[l++];
        for(int i=head[x];i!=-1;i=e[i].next){
            if(e[i].w&&!dis[e[i].v]){
                dis[e[i].v]=dis[x]+1;
                if(e[i].v==t) return 1;
                q[r++]=e[i].v;
            }
        }
    }
    return 0;
}

int extend(int s,int Lim){
    if(s==t) return Lim;
    int tmp,cost=0;
    for(int i=head[s];i!=-1;i=e[i].next){
        if(e[i].w&&dis[s]==dis[e[i].v]-1){
            tmp=extend(e[i].v,min(Lim-cost,e[i].w));
            if(tmp>0){
                e[i].w-=tmp,e[i^1].w+=tmp,cost+=tmp;
                if(Lim==cost) break;
            }else dis[e[i].v]=-1;
        }
    }
    return cost;
}

int Dinic(){
    int ans=0;
    while(MkLevel()) ans+=extend(s,INF);
    return ans;
}

void Solve(){
    n=input(),m=input(),s=input(),t=input();
    int u,v,w;
    cnt=0;
    clr(head,-1);
    for(int i=1;i<=m;i++){
        u=input(),v=input(),w=input();
        Ins(u,v,w);
    }
    printf("%d\n",Dinic());
}

int main(){
    Solve();
}