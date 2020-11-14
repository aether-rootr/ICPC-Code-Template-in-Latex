#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=1e5+7;

int a[1007],n;
bitset <N> bt;

int fd(int L,int R){
	if(L>=R) return 0;
	int l=L,r=L,res=0;
	while(1){
		while(bt[a[r]]==0&&r<R)
			bt[a[r++]]=1,res=max(res,r-l);
		if(l==R&&r==R) break;
		bt[a[l++]]=0;
		if(l==R&&r==R) break;
	}
	return res;
}

int main(){
	int T=input(),cas=0;
	while(T--){
		n=input();
		for(int i=0;i<n;i++) a[i]=input();

		int l=0,r=0,Ans=0;

		while(1){
			while(bt[a[r]]==0&&r<n)
				bt[a[r++]]=1,Ans=max(Ans,(r-l)+max(fd(0,l),fd(r,n)));
			if(l==n&&r==n) break;
			bt[a[l++]]=0;
			Ans=max(Ans,(r-l)+max(fd(1,l),fd(r,n)));
			if(l==n&&r==n) break;
		}
		printf("Case #%d: %d\n",++cas,Ans);
	}
}