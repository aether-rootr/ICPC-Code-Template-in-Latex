// hdu1848
/*
roblem Description
任何一个大学生对菲波那契数列(Fibonacci numbers)应该都不会陌生，它是这样定义的：

F(1)=1;

F(2)=2;

F(n)=F(n-1)+F(n-2)(n>=3);

所以，1,2,3,5,8,13……就是菲波那契数列。

在HDOJ上有不少相关的题目，比如1005 Fibonacci again就是曾经的浙江省赛题。
今天，又一个关于Fibonacci的题目出现了，它是一个小游戏，定义如下：

1、  这是一个二人游戏;

2、  一共有3堆石子，数量分别是m, n, p个；

3、  两人轮流走;

4、  每走一步可以选择任意一堆石子，然后取走f个；

5、  f只能是菲波那契数列中的元素（即每次只能取1，2，3，5，8…等数量）；

6、  最先取光所有石子的人为胜者；

假设双方都使用最优策略，请判断先手的人会赢还是后手的人会赢。
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

const int N=1007;

int f[N],S[N],sg[N];

void init(){
	f[0]=1,f[1]=1;
	for(int i=2;f[i]<N;i++){
		f[i]=f[i-1]+f[i-2];
	}

	memset(sg,0,sizeof sg);

	for(int i=1;i<N;i++){
		memset(S,0,sizeof(S));
		for(int j=1;f[j]<=i;j++)
			S[sg[i-f[j]]]=1;
		
		for(int j=0;;j++)
			if(!S[j]){sg[i]=j;break;}
	}
}

int main(){
	init();

	int n,m,p;
	while(~scanf("%d%d%d",&n,&m,&p)){
		if(!(n||m||p)) break;
		if(sg[n]^sg[m]^sg[p]) printf("Fibo\n");
		else printf("Nacci\n");
	}
}