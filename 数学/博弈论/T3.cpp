//一棵树上，两个人进行博弈，每次操作至少删去一个叶子节点，不能删的人输。
/*
首先瞎编一个定义：一个叶子节点一直往上到分叉点为止（不包括分岔点）的这一条链称为一个枝条。

如果某棵树上存在一个长度为1的枝条，那么先手必胜。这个我们可以分两种情况进行证明：

如果删去这根长度为1的枝条，剩下的树先手必败，那么我们只需要删去这根长度为1的枝条，把必败的状态扔给对面就行了
如果删去这跟长度为1的枝条，剩下的树先手必胜，那么我们就删去剩下的树先手应该删的点，顺带删掉我们这个长度为1的枝条。
所以如果存在长度为1的枝条，先手必胜。那如果有人碰到枝条长度全是2的情况，就必败，因为它无论怎么删，必然制造出长度为1的枝条。

这样子的话，我们就可以把这棵树所有的枝条都拿出来，把他们的长度减去2，放进一个数组里。如果把数组里的数看成石子，题目转化成有若干个石子堆，每次至少拿走一颗石子，每个石子堆至多拿走一颗石子，不能拿的人输。

这就是个比较简单的博弈题，如果石子堆个数都是偶数，那先手必败，因为先手无论怎么取，后手都可以做一样的操作。如果存在奇数个石子堆，那先手必胜，他只需要把所有石子堆变成偶数即可。
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=2e6+7;

int deg[N],f[N];

int main(){
	int T=input();
	while(T--){
		int n=input();

		for(int i=0;i<=n;i++){
			f[i]=deg[i]=0;
		}

		for(int i=2;i<=n;i++){
			int x=input();
			deg[x]++;f[i]=x;
		}

		int Ans=0;
		for(int i=1;i<=n;i++){
			if(deg[i]==0){
				int now=i,cnt=0;
				while(deg[now]<2&&now){
					now=f[now];
					cnt++;
				}
				if(cnt&1) Ans=1;
			}
		}

		if(Ans) printf("Takeru\n");
		else printf("Meiya\n");
	}
}