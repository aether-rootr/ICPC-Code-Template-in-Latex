//luogu p1578
#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define PII pair <int,int>
#define fr first
#define sc second
#define mp make_pair

const int N=5007;

PII a[N];
int n,m,k,Ans;

bool cmp(PII a,PII b){return a.sc<b.sc;}

int main(){
	n=input(),m=input(),k=input();

	for(int i=1;i<=k;i++){
		a[i].fr=input(),a[i].sc=input();
	}

	a[++k]=mp(0,0),a[++k]=mp(0,m);
	a[++k]=mp(n,0),a[++k]=mp(n,m);

	sort(a+1,a+k+1);

	for(int i=1;i<=k;i++){
		int h1=m,h2=0,v=n-a[i].fr,f=0;

		for(int j=i+1;j<=k;j++){
			if(h2<=a[j].sc&&a[j].sc<=h1){
				if(v*(h1-h2)<=Ans) break;

				Ans=max(Ans,(h1-h2)*(a[j].fr-a[i].fr));

				if(a[j].sc==a[i].sc){
					f=1;
					break;
				}

				if(a[j].sc>a[i].sc) h1=min(h1,a[j].sc);
				else h2=max(h2,a[j].sc);
			}
		}
		if(!f) Ans=max(Ans,v*(h1-h2));

		h1=m,h2=0,v=a[i].fr,f=0;
		for(int j=i-1;j>=1;j--){
			if(h2<=a[j].sc&&a[j].sc<=h1){
				if(v*(h1-h2)<=Ans) break;

				Ans=max(Ans,(h1-h2)*(a[i].fr-a[j].fr));

				if(a[j].sc==a[i].sc){
					f=1;
					break;
				}

				if(a[j].sc>a[i].sc) h1=min(h1,a[j].sc);
				else h2=max(h2,a[j].sc);
			}
		}
		if(!f) Ans=max(Ans,v*(h1-h2));
	}

	sort(a+1,a+k+1,cmp);
	for(int i=1;i<k;i++){
		Ans=max(Ans,(a[i+1].sc-a[i].sc)*n);
	}
	printf("%d\n",Ans);
}