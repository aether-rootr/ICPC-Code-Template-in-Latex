#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=1e6+7;

int nxt[N];

void get_nxt(char *s){
	int len=strlen(s+1);

	for(int i=2,j=0;i<=len;i++){
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	}
}

char s[N],t[N];

int main(){
	scanf("%s%s",s+1,t+1);

	get_nxt(t);
	int ls=strlen(s+1),lt=strlen(t+1);

	for(int i=1,j=0;i<=ls;i++){
		while(j&&s[i]!=t[j+1]) j=nxt[j];
		if(s[i]==t[j+1]) j++;
		if(j==lt){printf("%d\n",i-j+1);j=nxt[j];}
	}

	for(int i=1;i<=lt;i++) printf("%d%c",nxt[i],i==lt? '\n':' ');
}