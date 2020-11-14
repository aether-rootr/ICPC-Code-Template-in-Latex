//foo.size() 返回大小（位数）
//foo.count() 返回1的个数
//foo.any() 返回是否有1
//foo.none() 返回是否没有1
//foo.set() 全都变成1
//foo.set(p) 将第p + 1位变成1
//foo.set(p, x) 将第p + 1位变成x
//foo.reset() 全都变成0
//foo.reset(p) 将第p + 1位变成0
//foo.flip() 全都取反
//foo.flip(p) 将第p + 1位取反
//foo.to_ulong() 返回它转换为unsigned long的结果，如果超出范围则报错
//foo.to_ullong() 返回它转换为unsigned long long的结果，如果超出范围则报错
//foo.to_string() 返回它转换为string的结果
// #include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

bitset<10007> bs[1007];
int n;

int main(){
	n=input();
	for(int i=1;i<=n;i++){
		int m=input();
		for(int j=1;j<=m;j++){
			bs[i][input()]=1;
		}
	}

	int Q=input();

	for(int i=1;i<=Q;i++){
		int x=input(),y=input();
		bool f=0;
		for(int j=1;j<=n;j++){
			if(bs[j][x]&&bs[j][y]){printf("Yes\n");f=1;break;}
		}
		if(!f) printf("No\n");
	}
	return 0;
}