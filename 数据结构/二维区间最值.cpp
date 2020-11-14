//二维区间最值
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=1007;

int h[N][N],sum[N][N],mind[N][N];
int n,m,q;

int Solve(int a,int b){
	int tmp[N];
	for(int j=1;j<=m;j++){
		int l=1,r=0;
		for(int i=1;i<a;i++){
			while(r>=l&&h[tmp[r]][j]>=h[i][j]) r--;
			tmp[++r]=i;
		}

		for(int i=1;i+a-1<=n;i++){
			while(r>=l&&h[tmp[r]][j]>=h[i+a-1][j])r--;
			tmp[++r]=i+a-1;
			while(tmp[l]<i) l++;
			mind[i][j]=h[tmp[l]][j];
		}
	}

	int Ans=1e9;
	for(int i=1;i+a-1<=n;i++){
		int l=1,r=0;

		for(int j=1;j<b;j++){
			while(r>=l&&mind[i][tmp[r]]>=mind[i][j]) r--;
			tmp[++r]=j;
		}

		for(int j=1;j+b-1<=m;j++){
			while(r>=l&&mind[i][tmp[r]]>=mind[i][j+b-1]) r--;
			tmp[++r]=j+b-1;
			while(tmp[l]<j) l++;
			int tmin=mind[i][tmp[l]];
			int ii=i+a-1,jj=j+b-1;
			int tsum=sum[ii][jj]-sum[ii][j-1]-sum[i-1][jj]+sum[i-1][j-1];
			Ans=min(Ans,tsum-tmin*a*b);
		}
	}
	return Ans;
}

int main(){
	n=input(),m=input();

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			h[i][j]=input();
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+h[i][j];
		}
	}

	q=input();
	for(int i=1;i<=q;i++){
		int a=input(),b=input();
		printf("%d\n",Solve(a,b));
	}
	return 0;
}