#include <bits/stdc++.h>

using namespace std;

#define ll long long
ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

const int N=1e5+7;

//stk[] 是整型存的是下标
int stk[N],top=0;
int vis[N];
int n;

//点或者向量结构体
struct Point{
	double x,y;

	Point(){}

	Point(double _x,double _y){x=_x,y=_y;};

	Point operator -(const Point &b)const{
		return Point(x-b.x,y-b.y);
	}

	double operator ^(const Point &b)const{
		return x*b.y-y*b.x;
	}
}p[N];

bool cmp(Point a,Point b){
	if(a.x==b.x) return a.y<b.y;
	else return a.x<b.x;
}

double dis(Point a,Point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void Andrew(){
	top=0;//初始化栈
	sort(p+1,p+1+n,cmp);//对点进行排序
	stk[++top]=1;
	//求下凸壳
	for(int i=2;i<=n;i++){
		(p[stk[top]]-p[stk[top-1]]);
		(p[i]-p[stk[top]]);
		while(top>=2&&((p[stk[top]]-p[stk[top-1]])^(p[i]-p[stk[top]]))<=0) vis[stk[top--]]=0;
		vis[i]=1;
		stk[++top]=i;
	}
	int tmp=top;

	for(int i=n-1;i>=1;i--){
		if(!vis[i]){
			//求上凸壳时不影响下凸壳
			while(top>tmp&&((p[stk[top]]-p[stk[top-1]])^(p[i]-p[stk[top]]))<=0)vis[stk[top--]]=0;
			vis[i]=1;
			stk[++top]=i;
		}
	}
}

int main(){
	n=input();

	for(int i=1;i<=n;i++){
		double x,y;
		scanf("%lf%lf",&x,&y);
		p[i]=Point(x,y);
	}

	Andrew();

	double Ans=0;

	for(int i=1;i<top;i++){
		Ans+=dis(p[stk[i]],p[stk[i+1]]);
	}

	printf("%.4lf\n",Ans);
}