#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define debug printf("PASS IN LINE:%d\n",__LINE__)

ll input(){
	ll x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define N (int)300050
const double pi=acos(-1.0);

namespace FFT{
	int rev[N],bit,len;
	struct complex{
		double r,i;
		complex(){}
		complex(double _r,double _i){r=_r,i=_i;}
	};
	complex operator +(const complex &x,const complex &y){return complex(x.r+y.r,x.i+y.i);}
	complex operator -(const complex &x,const complex &y){return complex(x.r-y.r,x.i-y.i);}
	complex operator *(const complex &x,const complex &y){return complex(x.r*y.r-x.i*y.i,x.r*y.i+x.i*y.r);}
	void FFT(complex *a,int n,int f){
		for(int i=0;i<n;i++){
			if(i<rev[i]) swap(a[i],a[rev[i]]);
		}
		for(int p=1;p<n;p<<=1){
			complex wn(cos(pi/p),sin(pi/p)*f);
			for(int i=0;i<n;i+=(p<<1)){
				complex e(1,0);
				for(int j=0;j<p;j++,e=e*wn){
					complex x=a[i+j],y=a[i+j+p]*e;
					a[i+j]=x+y,a[i+j+p]=x-y;
				}
			}
		}	
		if(f==-1){
			for(int i=0;i<n;i++) a[i].r/=n;
		}
		return;
	}
	void main(complex *a,complex *b,int *c,int n,int m,int &Len){
		len=1,bit=0;
		while(len<n+m-1) len<<=1,bit++;
		for(int i=1;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		FFT(a,len,1);FFT(b,len,1);
		for(int i=0;i<len;i++) a[i]=a[i]*b[i];
		FFT(a,len,-1);Len=n+m-1;
		for(int i=0;i<Len;i++) c[i]=int(a[i].r+0.5);
		while(Len-1&&!c[Len-1]) Len--;
		return;
	}
}

struct fnc{
	int a[N],len;bool flag;

	void Clear(){memset(a,0,sizeof(a));len=flag=0;}

	fnc operator *(const fnc &x){
		static fnc Kano;Kano.Clear();
		static FFT::complex Arch[N],Bers[N];
		Kano.flag=x.flag^flag;
		for(int i=0;i<len;i++) Arch[i].r=a[i];
		for(int i=0;i<x.len;i++) Bers[i].r=x.a[i];
		FFT::main(Arch,Bers,Kano.a,len,x.len,Kano.len);
		return Kano;
	}
};

fnc _A,_B;

int main(){
	_A.len=input()+1,_B.len=input()+1;
	for(int i=0;i<_A.len;i++){
		_A.a[i]=input();
	}
	for(int i=0;i<_B.len;i++){
		_B.a[i]=input();
	}
	fnc _C=_A*_B;
	for(int i=0;i<_C.len;i++){
		printf("%d ",_C.a[i]);
	}
	printf("\n");
	return 0;
}