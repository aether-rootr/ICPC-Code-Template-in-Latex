//hdu1711
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=1e6+7;
int base[2]={19260817,(int)1e5+7},mod[2]={(int)1e9+7,998244353};
#define debug printf("PASS IN LINE:%d\n",__LINE__)

ll p[2][N],h[2][N];

void init(){
	p[0][0]=p[1][0]=1;
	for(int i=1;i<N;i++)
		p[0][i]=p[0][i-1]*base[0]%mod[0],
		p[1][i]=p[1][i-1]*base[1]%mod[1];
}

ll gethash(int l,int r,int id){
	return ((h[id][r]-h[id][l-1]*p[id][r-l+1])%mod[id]+mod[id])%mod[id];
}

int main(){
	init();
	int T=input();
	while(T--){
		int n=input(),m=input(),x;
		for(int i=1;i<=n;i++){
			x=input()+N;
			h[0][i]=(h[0][i-1]*base[0]+x)%mod[0];
			h[1][i]=(h[1][i-1]*base[1]+x)%mod[1];
		}
		
		ll H[2]={0,0};
		
		for(int i=1;i<=m;i++){
			x=input()+N;
			H[0]=(H[0]*base[0]+x)%mod[0];
			H[1]=(H[1]*base[1]+x)%mod[1];
		}
		
		int Ans=-1;
		
		for(int i=1;i+m-1<=n;i++){

			if(gethash(i,i+m-1,0)==H[0]&&gethash(i,i+m-1,1)==H[1]){
				Ans=i;break;
			}
		}
		
		printf("%d\n",Ans);
	}
}