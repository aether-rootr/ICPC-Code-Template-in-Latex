#include<cstdio>
#include<cstring>
#include<algorithm>
#define M 25
#define N 100005
using namespace std;
int n,m;
int a[N],Log[N];
int f[N][M];
void GetLog()
{
	int i;
	Log[1]=0;
	for(i=2;i<=n+1;++i)
	  Log[i]=Log[i/2]+1;
}
void RMQ()
{
	int i,j;
	for(i=1;i<=n;++i)
	  f[i][0]=a[i];
	for(j=1;(1<<j)<=n;++j)
	  for(i=1;i+(1<<(j-1))<=n;++i)
	    f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}
int main()
{
	int l,r,i,k,ans;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
	  scanf("%d",&a[i]);
	GetLog();
	RMQ();
	for(i=1;i<=m;++i)
	{
		scanf("%d%d",&l,&r);
		k=Log[r-l+1];
		ans=max(f[l][k],f[r-(1<<k)+1][k]);
		printf("%d\n",ans);
	}
	return 0;
}