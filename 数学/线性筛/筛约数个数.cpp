#define ll long long
ll d[N],prim[N],num[N],cnt;
int vis[N];

void init(){
    d[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i])
            vis[i]=1,prim[i]=i,d[i]=2,num[i]=1;

        for(int j=1;j<=cnt&&i*prim[j]<=n;j++){
            vis[prim[j]*i]=1;
            if(i%p[j]==0){
                num[i*prim[j]]=num[i]+1;
                d[i*prim[j]]=d[i]/num[i*prim[j]]*(num[i*prim[j]]+1);
                break;
            }else{
                num[i*prim[j]]=1;
                d[i*prim[j]]=d[i]*2;
            }
        }
    }
}