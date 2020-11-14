// 约旦-高斯消元
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=107;
double a[N][N];
int n;

int main(){
	n=input();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			a[i][j]=input();

	for(int i=1;i<=n;i++){
		int mx=i;
		for(int j=i+1;j<=n;j++)
			if(fabs(a[j][i])>fabs(a[mx][i]))
				mx=j;

		for(int j=1;j<=n+1;j++)
			swap(a[i][j],a[mx][j]);

		if(!a[i][i]){
			printf("No Solution\n");
			exit(0);
		}

		for(int j=1;j<=n;j++){
			if(j!=i){
				double tmp=a[j][i]/a[i][i];
				for(int k=i+1;k<=n+1;k++){
					a[j][k]-=a[i][k]*tmp;
				}
			}
		}
	}

	for(int i=1;i<=n;i++){
		printf("%.2lf\n",a[i][n+1]/a[i][i]);
	}
}

///////////////////////////////////////////////


// //高斯消元
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const ll N=107;
const double eps=1e-7;

double a[N][N],Ans[N];

int main(){
	int n=input();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			a[i][j]=input();

	for(int i=1;i<=n;i++){
		int mx=i;
		for(int j=i+1;j<=n;j++)
			if(fabs(a[mx][i])<fabs(a[j][i]))
				mx=j;
		
		if(fabs(a[mx][i])<eps){
			printf("No Solution\n");
			return 0;
		}

		if(i!=mx) swap(a[i],a[mx]);

		double tmp=a[i][i];
		for(int j=i;j<=n+1;j++)
			a[i][j]/=tmp;

		for(int j=i+1;j<=n;j++){
			tmp=a[j][i];
			for(int k=i;k<=n+1;k++)
				a[j][k]-=a[i][k]*tmp;
		}
	}

	Ans[n]=a[n][n+1];
	for(int i=n-1;i>=1;i--){
		Ans[i]=a[i][n+1];
		for(int j=i+1;j<=n;j++)
			Ans[i]-=(a[i][j]*Ans[j]);
	}
	for(int i=1;i<=n;i++)
		printf("%.2lf\n",Ans[i]);
}