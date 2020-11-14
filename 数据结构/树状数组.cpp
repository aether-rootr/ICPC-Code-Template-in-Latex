#include <iostream>
#include <cstdio>
#define lowbit(x) x&-x
using namespace std;
int a[10001];
int n;
void change(int x,int ad){while(x<n) a[x]+=ad,x+=lowbit(x);}
int sum(int l,int r){
	int ans1=0,ans2=0;l--;
	while(l>0) ans1+=a[l],l-=lowbit(l);
	while(r>0) ans2+=a[r],r-=lowbit(r);
	return ans2-ans1;
}
int main(){
	scanf("%d",&n);
	int re;
	for(int i=1;i<=n;i++){
		scanf("%d",&re);
		change(i,re);
	}
	int m;
	int l,r;
	scanf("%d",&m);
	while(m--){
		scanf("%d%d",&l,&r);
		printf("%d\n",sum(l,r));
	}
}