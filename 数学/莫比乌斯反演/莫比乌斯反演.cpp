#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
    ll x=0,f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

const int N=50007;

bool vis[N];
int mu[N],pri[N],cnt=0;

void init(){
    mu[1]=1;
    for(int i=2;i<=N;++i){
        if(!vis[i]) pri[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt;++j){
            if(i*pri[j]>N) break;
            vis[i*pri[j]]=1;
            if(i%pri[j]==0){mu[i*pri[j]]=0;break;}
            else mu[i*pri[j]]=-mu[i];
        }
    }
    for(int i=1;i<=N;i++) mu[i]+=mu[i-1];
}

int solve(int n,int m){
    int res=0;
    for(int i=1,j;i<=min(n,m);i=j+1){
        j=min(n/(n/i),m/(m/i));
        res+=(mu[j]-mu[i-1])*(n/i)*(m/i);
    }
    return res;
}

int main(){
	init();
	int t,a,b,c,d,k;
    t=input();
    for(int i=1;i<=t;i++){
        a=input()-1,b=input(),c=input()-1,d=input(),k=input();
        a/=k,b/=k,c/=k,d/=k;
        printf("%d\n",solve(b,d)-solve(a,d)-solve(c,b)+solve(a,c));
    }
}