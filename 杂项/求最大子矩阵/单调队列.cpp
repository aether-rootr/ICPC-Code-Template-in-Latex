//O(NM)单调栈做法
//luogu P4147
//它要找一块矩形土地，要求这片土地都标着 'F' 并且面积最大

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
int a[N],h[N];
stack <int> stk;
int Ans=0;

int main(){
	int n=input(),m=input();

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch[2];
			scanf("%s",ch);
			if(ch[0]=='F') h[j]=h[j]+1;
			else h[j]=0;

			a[j]=h[j];

			int top=j;
			while(!stk.empty()&&a[stk.top()]>a[j]){
				top=stk.top();stk.pop();
				Ans=max(Ans,(j-top)*a[top]);
			}
			a[top]=a[j];
			stk.push(top);
		}
		while(!stk.empty()){
			Ans=max(Ans,(m+1-stk.top())*a[stk.top()]);
			stk.pop();
		}
	}
	printf("%d\n",Ans*3);
}