// // 悬线法O(NM)用于障碍点比较多的情况
// // luogu p1169
// 给定一个01棋盘,求其中01交错的最大正方形与矩形。
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=2007;

int a[N][N];
int H[N][N],L[N][N],R[N][N];

int main(){
	int n=input(),m=input();

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=input();
			H[i][j]=1,L[i][j]=R[i][j]=j;
		}

		for(int j=2;j<=m;j++)
			if(a[i][j]!=a[i][j-1]) L[i][j]=L[i][j-1];//原题要求黑白相间，所以要不等于
		for(int j=m-1;j>=1;j--)
			if(a[i][j]!=a[i][j+1]) R[i][j]=R[i][j+1];//原题要求黑白相间，所以要不等于

		for(int j=1;j<=m;j++){
			if(i>1&&a[i][j]!=a[i-1][j]){//原题要求黑白相间，所以要不等于
				H[i][j]=H[i-1][j]+1;
				L[i][j]=max(L[i-1][j],L[i][j]),R[i][j]=min(R[i-1][j],R[i][j]);
			}
		}
	}

	int Ans1=0,Ans2=0;

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int a=H[i][j],b=R[i][j]-L[i][j]+1;
			Ans1=max(Ans1,min(a,b)*min(a,b));
			Ans2=max(Ans2,a*b);
		}
	}

	printf("%d\n%d\n",Ans1,Ans2);
}