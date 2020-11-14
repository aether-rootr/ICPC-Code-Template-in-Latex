#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define mem(a,x) memset(a,x,sizeof(a))
#define pb emplace_back
#define pii pair<int,int>
#define mk make_pair
using namespace std;
typedef long long ll;
const ll mod = 998244353;
ll gcd(ll a, ll b) { return b?gcd(b,a%b):a;}
ll powmod(ll a,ll b) {ll res=1;a%=mod;
assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res%mod;}
inline ll read()
{
    ll x=0,w=1; char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') w=-1; c=getchar();}
    while(c<='9'&&c>='0') {x=(x<<1)+(x<<3)+c-'0'; c=getchar();}
    return w==1?x:-x;
}

const int N = 1e2 + 10, M=1e5 + 10;
int u[M], v[M];
ll w[M];
ll f[35], K[N][N];
ll Gauss(int n){
    ll res=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++)
            if(K[j][i]){
                for(int k=i;k<=n;k++)swap(K[i][k],K[j][k]);
                if(i!=j)res=-res;
                break;
            }
        if(!K[i][i])return 0;
        for(ll j=i+1,iv=powmod(K[i][i],mod-2);j<=n;j++){
                ll t=K[j][i]*iv%mod;
                for(int k=i;k<=n;k++)
                    K[j][k]=(K[j][k]-t*K[i][k]%mod+mod)%mod;
        }
        res=(res*K[i][i]%mod+mod)%mod;
    }
    return res;
}
//void Gauss(int n){
//    for(int i=1;i<=n;i++){
//        int j=i;
//        while(j<=n&&!a[j][i]) j++;
//        if(j!=i) for(int k=1;k<=n+1;k++) swap(a[i][k],a[j][k]);
//        int inv=Inv(a[i][i]);
//        for(int j=i+1;j<=n;j++){
//            int t=a[j][i]*inv%P;
//            for(int k=i;k<=n+1;k++) a[j][k]=(a[j][k]-t*a[i][k]%P+P)%P;
//        }
//    }
//    for(int i=n;i>=1;i--){
//        for(int j=n;j>i;j--) a[i][n+1]=(a[i][n+1]-a[j][n+1]*a[i][j]%P+P)%P;
//        a[i][n+1]=a[i][n+1]*Inv(a[i][i])%P;
//    }
//}

int main()
{
    f[0] = 1;
    for(int i = 1;i < 31; ++i) f[i] = f[i-1] * 2;

    int _ = read();
    while (_--) {
        int n = read(), m = read();
        for (int i = 1; i <= m; i++) u[i] = read(), v[i] = read(), w[i] = read();

        ll fz = 0;
        for (int j=0; j<=30; j++) {
            memset(K, 0, sizeof(K));

            for (int i = 1; i <= m; i++) {
                K[u[i]][u[i]] += (w[i] >> j) & 1;
                K[v[i]][v[i]] += (w[i] >> j) & 1;
                K[u[i]][v[i]] -= (w[i] >> j) & 1;
                K[v[i]][u[i]] -= (w[i] >> j) & 1;
            }
            fz = (fz + Gauss(n - 1) * f[j] % mod) % mod;
        }

        memset(K, 0, sizeof(K));
        for (int i = 1; i <= m; i++) {
            K[u[i]][u[i]]++;
            K[v[i]][v[i]]++;
            K[u[i]][v[i]]--;
            K[v[i]][u[i]]--;
        }
        ll fm = powmod(Gauss(n - 1), mod - 2);
        ll ans = fz * fm  % mod;
        printf("%lld\n", ans);
    }
    return 0;
}



////////////////////////////////////////////////////////////


const int N = 1e2 + 10, M=1e5 + 10;
int u[M], v[M], w[M];
ll f[35], K[N][N];
ll Gauss(int n){
    ll res=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++)
            if(K[j][i]){
                for(int k=i;k<=n;k++)swap(K[i][k],K[j][k]);
                if(i!=j)res=-res;
                break;
            }
        if(!K[i][i])return 0;
        for(ll j=i+1,iv=powmod(K[i][i],mod-2);j<=n;j++){
                ll t=K[j][i]*iv%mod;
                for(int k=i;k<=n;k++)
                    K[j][k]=(K[j][k]-t*K[i][k]%mod+mod)%mod;
        }
        res=(res*K[i][i]%mod+mod)%mod;
    }
    return res;
}