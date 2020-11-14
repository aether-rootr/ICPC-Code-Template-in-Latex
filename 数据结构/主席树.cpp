#include <bits/stdc++.h>

using namespace std;

#define ll long long

int input(){
	int x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define N (int)(1e5+7)

int n,m;
struct node{
	int l,r,sum;
}t[N*40];
int rt[N],a[N];
int cnt,x,y,k;
vector <int> v;

int getid(ll x) {return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}

void updata(int l,int r,int &x,int y,int pos) {
	t[++cnt]=t[y],t[cnt].sum++,x=cnt;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(mid>=pos) updata(l,mid,t[x].l,t[y].l,pos);
	else updata(mid+1,r,t[x].r,t[y].r,pos);
}

int query(int l,int r,int x,int y,int k){
	if(l==r) return l;
	int mid=(l+r)>>1;
	int sum=t[t[y].l].sum-t[t[x].l].sum;
	if(sum>=k) return query(l,mid,t[x].l,t[y].l,k);
	else return query(mid+1,r,t[x].r,t[y].r,k-sum);
}

int main() {
	n=input(),m=input();
	for(int i=1;i<=n;i++) {
		a[i]=input();
		v.push_back(a[i]);
	}

	sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end());

	for(int i=1;i<=n;i++) updata(1,n,rt[i],rt[i-1],getid(a[i]));

	for(int i=1;i<=m;i++) {
		x=input(),y=input(),k=input();
		printf("%d\n",v[query(1,n,rt[x-1],rt[y],k)-1]);
	}

	return 0;
}