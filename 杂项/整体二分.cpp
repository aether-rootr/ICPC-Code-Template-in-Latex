//k-th number
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define debug printf("pass in line:%d in [%s]\n",__LINE__,__FUNCTION__)
#define lowbit(x) x&-x

const int N = 2e5+7;
const int inf=0x3f3f3f3f;

struct opr{
	int f,l,r,k,pos,val;
	//修改中 val:数值, f:操作类型(1), pos:在数组中的位置
	//查询中 l,r,k:输入, f:操作类型(2), pos:询问编号 
};
opr q[N];
opr ql[N],qr[N];
int Ans[N];
int t[N];

int n,m;


//第一类操作是修改，也就是输入的 nn 个数。
// 这里用树状数组维护，最普通的吧，维护比一个数小的数的个数
void update(int pos,int x){
	for(;pos<=n;pos+=lowbit(pos)) t[pos]+=x;
}

int query(int l,int r){
	int res=0;l--;
	for(;l>0;l-=lowbit(l)) res-=t[l];
	for(;r>0;r-=lowbit(r)) res+=t[r];
	return res;
}

void solve(int l,int r,int head,int tail){
	//head,tail:操作区间; l,r:答案区间 
	if(head>tail) return;
	// //找到答案了
	if(l==r){//[ql,qr] 表示操作区间，[L,R]表示答案区间。如果 L=R 就说明找到答案了，将 [ql,qr] 中所有查询操作的答案赋为 L。
		for(int i=head;i<=tail;i++)
			if(q[i].f==2) Ans[q[i].pos]=l;
		return;
	}
	int mid=(l+r)>>1;
	int lcnt=0,rcnt=0;
	for(int i=head;i<=tail;i++){
		//但是并不是直接全都 add 进去。在二分的时候，如果 q[i].x<=mid，也就是会影响第 k 小的值，就 add(q[i].id,1)，并将这个操作存进 q1，因为在左区间也会用到，否则直接存进 q2，因为在右区间可能会用到。
		if(q[i].f==1){
			if(q[i].val<=mid){
				ql[++lcnt]=q[i];
				update(q[i].pos,1);
			}else qr[++rcnt]=q[i];
		}else{
			int num=query(q[i].l,q[i].r);
			if(num>=q[i].k) ql[++lcnt]=q[i];
			else q[i].k-=num,qr[++rcnt]=q[i];
		}

		/*
			第二类操作是查询。

			如果当前累计贡献 cnt 比要求贡献大，也就是数的个数大于 k，说明 mid 过大，
			满足标准的修改过多，我们需要给这个查询设置更小的答案区间，
			于是二分到答案区间 [L,mid]，否则二分到区间 [mid+1,R]，
			并将查询第 k 小改为查询第 k-cnt 小。
		*/
	}
	for(int i=1;i<=lcnt;i++){
		if(ql[i].f==1)
			update(ql[i].pos,-1);
	}

	// 最后把 q1 和 q2 再存回 q，进行二分就可以了。注意要把树状数组清空。
	tail=head-1;
	for(int i=1;i<=lcnt;i++) q[++tail]=ql[i];
	int div=tail;
	for(int i=1;i<=rcnt;i++) q[++tail]=qr[i];

	solve(l,mid,head,div);
	solve(mid+1,r,div+1,tail);
}

int main(){
	while(~scanf("%d%d",&n,&m)){
		memset(t,0,sizeof(t));
		int cnt=0;
		for(int i=1;i<=n;i++){
			q[++cnt].val=input();
			q[cnt].pos=i,q[cnt].f=1;
		}

		for(int i=1;i<=m;i++){
			q[++cnt].l=input(),q[cnt].r=input(),q[cnt].k=input();
			q[cnt].f=2,q[cnt].pos=i;
		}

		solve(-inf,inf,1,cnt);
	
		for(int i=1;i<=m;i++){
			printf("%d\n",Ans[i]);
		}
	}
}