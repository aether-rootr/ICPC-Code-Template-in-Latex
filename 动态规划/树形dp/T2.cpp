#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
    ll x=0,f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f? -x:x;
}

#define PII pair <ll,ll>
#define fr first
#define sc second
#define mp make_pair

const int N=1e5+7;
const ll inf=1e18;

vector<int> G[N];
ll dp[N][2];
ll c[N];
vector<PII> nxt[N];
int n;
ll Ans;

void dfs1(int u,int fa){
    dp[u][0]=inf,dp[u][1]=-inf;
    for(auto v:G[u]){
        if(v==fa) continue;
        dfs1(v,u);
        dp[u][0]=min(dp[u][0],dp[v][1]);
        dp[u][1]=max(dp[u][1],dp[v][0]);
    }
    if(dp[u][0]==inf)
        dp[u][0]=dp[u][1]=0;
    dp[u][0]+=c[u],dp[u][1]+=c[u];
}


void dfs2(int u,int fa){
    dp[u][0]=inf,dp[u][1]=-inf;
    for(int i=G[u].size()-1;i>=0;i--){
        int v=G[u][i];
        dp[u][0]=min(dp[u][0],dp[v][1]);
        dp[u][1]=max(dp[u][1],dp[v][0]);
        nxt[u].push_back(mp(dp[u][0],dp[u][1]));
    }

    dp[u][0]+=c[u];
    dp[u][1]+=c[u];
    Ans=max(Ans,dp[u][0]);

    int i=G[u].size()-1;
    ll pre1=inf,pre2=-inf;

    for(auto v:G[u]){
        dp[u][0]=pre1;
        dp[u][1]=pre2;
        if(i){
            dp[u][0]=min(dp[u][0],nxt[u][i-1].fr);
            dp[u][1]=max(dp[u][1],nxt[u][i-1].sc);
        }
        if(dp[u][0]==inf) dp[u][0]=dp[u][1]=0;
        dp[u][0]+=c[u];
        dp[u][1]+=c[u];
        pre1=min(pre1,dp[v][1]);
        pre2=max(pre2,dp[v][0]);
        if(v!=fa)
            dfs2(v,u);
        i--;
    }
}

int main(){
    int T=input();
    while(T--){
        n=input();
        for(int i=1;i<=n;i++)
            c[i]=input();
        for(int i=1;i<=n;i++)
            c[i]-=input();
        for(int i=1;i<=n;i++)
            G[i].clear(),nxt[i].clear();

        for(int i=1;i<n;i++){
            int u=input(),v=input();
            G[u].push_back(v);
            G[v].push_back(u);
        }

        Ans=-inf;
        
        dfs1(1,0);
        dfs2(1,0);

        printf("%lld\n",Ans);
    }
}