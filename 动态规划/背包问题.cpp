#include<iostream>
#include<cstdio>
#define DEBUG printf("PASS [%s] IN LINE %d\n",__FUNCTION__,__LINE__)
using namespace std;
int input(){
	int f=1,x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}
//有N件物品和一个容量为V的背包。第i件物品的费用是c[i]，价值是w[i]。求解将哪些物品装入背包可使价值总和最大。
class bag1{
	public:
		void solve(){
			n=input();v=input();
			int c,w;
			for(int i=1;i<=n;i++){
					c=input();w=input();
				for(int j=v;j>=c;j--){
					dp[j]=dp[j]>dp[j-c]+w? dp[j]:dp[j-c]+w;
				}
			}
			printf("%lld",dp[v]);
		}
	private:
		int dp[1007];
		int n,v;
};
//有N种物品和一个容量为V的背包，每种物品都有无限件可用。第i种物品的费用是c[i]，价值是w[i]。求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。
class bag2{
	public:
		void solve(){
			n=input();v=input();
			int c,w;
			for(int i=1;i<=n;i++){
					c=input();w=input();
				for(int j=c;j<=v;j++){
					dp[j]=dp[j]<dp[j-c]+w? dp[j]:dp[j-c]+w;
				}
			}
			printf("%d\n",dp[v]);
		}
	private:
		int dp[1007];
		int n,v;
};
// 有N种物品和一个容量为V的背包。第i种物品最多有n[i]件可用，每件费用是c[i]，价值是w[i]。求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。
class bag3{
	public:
		void solve(){
			l=1,r=0;
			n=input();v=input();
			int c,w,k;
			for(int i=1;i<=n;i++){
				c=input();w=input();k=input();
				if(v/c<k) k=v/c;
				for(int d=0;d<c;d++){
					l=1,r=0;
					for(int j=0;j<=(v-d)/c;j++){
						insert(j,dp[j*c+d]-j*w);
						if(Q[l]<j-k) l++;
						dp[j*c+d]=q[l]+j*w;
					}
				}
			}
			printf("%d\n",dp[v]);
		}
	private:
		int n,v;
		int dp[1007];
		int q[1007],Q[1007];
		int l,r;
		void insert(int x,int y){while(l<=r&&(q[r]<y))r--;q[++r]=y;Q[r]=x;}
};
// 如果将P01、P02、P03混合起来。也就是说，有的物品只可以取一次（01背包），有的物品可以取无限次（完全背包），有的物品可以取的次数有一个上限（多重背包）。应该怎么求解呢？
class bag4{
	public:
		void solve(){
			l=1,r=0;
			n=input();v=input();
			int w,c,k;
			for(int i=1;i<=n;i++){
				c=input();w=input();k=input();
				if(k==1) solve1(c,w);
				if(k==-1) solve2(c,w);
				if(k>1) solve3(c,w,k);
			}
			printf("%d\n",dp[v]);
		}
	private:
		int n,v;
		int dp[1007];
		int q[1007],Q[1007];
		int l,r;
		void insert(int x,int y){while(l<=r&&(q[r]<y))r--;q[++r]=y;Q[r]=x;}
		void solve1(int c,int w){
			for(int j=v;j>=c;j--){
					dp[j]=dp[j]>dp[j-c]+w? dp[j]:dp[j-c]+w;
				}
		}
		void solve2(int c,int w){
			for(int j=c;j<=v;j++){
						dp[j]=dp[j]>dp[j-c]+w? dp[j]:dp[j-c]+w;
					}
		}
		void solve3(int c,int w,int k){
			if(v/c<k) k=v/c;
			for(int d=0;d<c;d++){
				l=1,r=0;
				for(int j=0;j<=(v-d)/c;j++){
					insert(j,dp[j*c+d]-j*w);
					if(Q[l]<j-k) l++;
					dp[j*c+d]=q[l]+j*w;
				}
			}
		}
};
// 二维费用的背包问题是指：对于每件物品，具有两种不同的费用；选择这件物品必须同时付出这两种代价；对于每种代价都有 一个可付出的最大值（背包容量）。问怎样选择物品可以得到最大的价值。设这两种代价分别为代价1和代价2，第i件物品所需的两种代价分别为a[i]和 b[i]。两种代价可付出的最大值（两种背包容量）分别为V和U。物品的价值为w[i]。
class bag5{
	public:
		void solve(){
			vmax=input();mmax=input();n=input();
				int v,m,k;
			for(int l=1;l<=n;l++){
				v=input();m=input();k=input();
				for(int i=vmax;i>=v;i--){
					for(int j=mmax;j>=m;j--){
						dp[i][j]=dp[i][j]>dp[i-v][j-m]+k? dp[i][j]:dp[i-v][j-m]+k;
					}
		    	}
		    }
		    printf("%d",dp[vmax][mmax]);
		}
	private:
		int dp[1007][1007];
	int n;	
	int vmax,mmax;
};
// 有N件物品和一个容量为V的背包。第i件物品的费用是c[i]，价值是w[i]。这些物品被划分为若干组，每组中的物品互相冲突，最多选一件。求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。
class bag6{
	public:
		void solve(){
			k=input();v=input();
			int cc,w,c;
			for(int l=1;l<=k;l++){
				cc=input();
				for(int j=v;j>=0;j--){
					for(int i=1;i<=cc;i++){
						w=input();c=input();
						dp[j]=dp[j]>dp[j-c]+w? dp[j]:dp[j-c]+w;
					}
				}
			}
			printf("%d\n",dp[v]);
		}
	private:
		int dp[1007];
		int v,k;
};
//bag1 bag1;
//bag2 bag2;
//bag3 bag3;
//bag4 bag4;
//bag5 bag5;
//bag6 bag6;
int main(){
//	bag1.solve();
//	bag2.solve();
//	bag3.solve();
//	bag4.solve();
//	bag5.solve();
//	bag6.solve();
}