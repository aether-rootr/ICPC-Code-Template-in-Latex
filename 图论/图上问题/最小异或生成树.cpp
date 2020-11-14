#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=2e5+7;
const int inf=0x3f3f3f3f;

#define ls(x) t[x][0]
#define rs(x) t[x][1]
int L[N*40],R[N*40],t[N*40][2],cnt;
int n,a[N],root;

void Insert(int &rt,int x,int dep){
	if(!rt) rt=++cnt;
	L[rt]=min(L[rt],x),R[rt]=max(R[rt],x);
	if(dep<0) return;
	int bit=a[x]>>dep&1;
	Insert(t[rt][bit],x,dep-1);
}

int query(int rt,int val,int dep){
	if(dep<0) return 0;
	int bit=val>>dep&1;
	if(t[rt][bit]) return query(t[rt][bit],val,dep-1);
	else return query(t[rt][bit^1],val,dep-1)+(1<<dep);
}

ll dfs(int rt,int dep){
	if(dep<0) return 0;
	if(R[ls(rt)]&&R[rs(rt)]){
		int mi=inf;
		for(int i=L[ls(rt)];i<=R[ls(rt)];i++) mi=min(mi,query(rs(rt),a[i],dep-1));
		return dfs(ls(rt),dep-1)+dfs(rs(rt),dep-1)+mi+(1<<dep);
	}
	if(R[ls(rt)]) return dfs(ls(rt),dep-1);
	if(R[rs(rt)]) return dfs(rs(rt),dep-1);
	return 0;
}

int main(){
	n=input();
	memset(L,0x3f,sizeof L);
	for(int i=1;i<=n;i++) a[i]=input();
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++) Insert(root,i,30);
	printf("%lld\n",dfs(root,30));
}