#include <bits/stdc++.h>

using namespace std;

#define ll long long

inline ll input(){
	ll x=0,f=0;char ch=getchar();
	while (ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f? -x:x;
}

#define N 205
#define B 1000
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

struct BigNum{
	int a[N],len;bool flag;

	//Clear it,must
	void Clear(){memset(a,0x00,sizeof(a));len=flag=0;}

	//Get BigNum from Input,choice
	void GetInput(){
 	 	static char ch[N];char* c;Clear();
 	 	scanf("%s",ch+1);c=ch;
 	 	if (ch[1]=='-') flag=true,c++;
 	 	len=strlen(c+1);int k=100;
 		for (int i=len;i;i--)
 	 	  k=k==100?1:k*10,a[(len-i)/3]+=(c[i]-'0')*k;
 	 	len=(len-1)/3+1;
 	 	return;
 	 }

	//Get BigNum from a number,choice
	void GetInt(int w){
 	 	Clear();
 	 	if (w<0) flag=true,w=-w;
 	 	while (w) a[len++]=w%B,w/=B;
 	 	return;
 	 }

	//Repair it,make it legal,must
	void Repair(){
 	 	while (a[len]) a[len+1]=a[len]/B,a[len++]%=B;
 	 	while (len-1&&!a[len-1]) len--;
 	 	if (len==1&&!a[0]) flag=false;
 	 	return;
 	 }

 	//Plus it with unsigned x and assign the sign of flag
 	//+,- must
 	BigNum Plus(BigNum x,bool flag){
 	 	static BigNum Kano;Kano.Clear();
 	 	Kano.len=max(len,x.len);Kano.flag=flag;
 	 	for (int i=0;i<Kano.len;i++)
 	 	  Kano.a[i]+=a[i]+x.a[i],
 	 	  Kano.a[i+1]=Kano.a[i]/B,
 	 	  Kano.a[i]%=B;
 	 	Kano.Repair();
 	 	return Kano;
 	}

 	//Delete it by y from x and assign the sign of flag
 	//+,-,/,% must
 	BigNum Del(int x,BigNum y,bool flag){
 	 	static BigNum Kano;Kano.Clear();
 	 	Kano.len=len;Kano.flag=flag;
 	 	memcpy(Kano.a,a,sizeof a);
 	 	for (int i=0;i<y.len;i++){
 	 	 	Kano.a[i+x]-=y.a[i];
 	 	 	if (Kano.a[i+x]<0)
 	 	 	  Kano.a[i+x]+=B,Kano.a[i+x+1]--;
 	 	}
 	 	Kano.Repair();
 	 	return Kano;
 	}

 	//Be Deleted by x
 	//+,- must
 	BigNum Deled(int x,BigNum y,bool flag){
 	 	static BigNum Kano;Kano.Clear();
 	 	Kano.len=y.len;Kano.flag=flag;
 	 	memcpy(Kano.a,y.a,sizeof y.a);
 	 	for (int i=0;i<len;i++){
 	 	 	Kano.a[i+x]-=a[i];
 	 	 	if (Kano.a[i+x]<0)
 	 	 	  Kano.a[i+x]+=B,Kano.a[i+x+1]--;
 	 	 }
 	 	Kano.Repair();
 	 	return Kano;
 	}

 	//Compare it without sign from the xth
 	//+,-,<，/，%,must
 	bool compare(const BigNum &y,int x=0){
 	 	if (len-x!=y.len) return len-x<y.len;
 	 	for (int i=len-1;~(i-x);i--)
 	 	 if (a[i]!=y.a[i-x]) return a[i]<y.a[i-x];
 	 	return false;
 	 }

 	//Multi it with a int
 	//<<,%,/,must
 	BigNum operator* (const int &x){
 	 	static BigNum Kano;Kano.Clear();
 	 	Kano.flag=flag^(x<0);Kano.len=len;
 	 	for (int i=0;i<len;i++)
 	 	  Kano.a[i]+=a[i]*x,
 	 	  Kano.a[i+1]=Kano.a[i]/B,
 	 	  Kano.a[i]%=B;
 	 	Kano.Repair();
 	 	return Kano;
 	 }

 	//Multi it with a BigNum by NTT
 	BigNum operator* (const BigNum &x){
 	 	static BigNum Kano;Kano.Clear();
 	 	static FFT::complex Arch[N],Bers[N];
 	    Kano.flag=x.flag^flag;
 	 	for (int i=0;i<len;i++) Arch[i].r=a[i];
 	 	for (int i=0;i<x.len;i++) Bers[i].r=x.a[i];
 	 	FFT::main(Arch,Bers,Kano.a,len,x.len,Kano.len);
 	    for (int i=0;i<Kano.len;i++)
 	      Kano.a[i+1]+=Kano.a[i]/B,Kano.a[i]%=B;
 	    Kano.Repair();
 	 	return Kano;
 	 }

 	//Let it move to left for x bits
 	//%,/,must
 	BigNum operator<< (int x){
 	 	static BigNum Kano;
 	 	memcpy(Kano.a,a,sizeof a);
 	 	Kano.len=len;Kano.flag=flag;
 	 	while (x--) Kano=Kano*2;
 	 	return Kano;
 	 }

 	//Compare it with sign
 	//-,must
 	bool operator< (const BigNum &x){
 	 	if (flag^x.flag) return flag;
 	 	if (len!=x.len) return (len<x.len)^flag;
 	 	for (int i=len-1;~i;i--)
 	 	 if (x.a[i]!=a[i]) return (a[i]<x.a[i])^flag;
 	 	return false;
 	}

 	//Plus it to y with sign
 	BigNum operator+ (const BigNum &x){
 	 	if (flag==x.flag) return Plus(x,x.flag); else
 	 	 if (compare(x)) return Deled(0,x,x.flag); else
 	 	   return Del(0,x,flag);
 	}

 	//Delete y from it with sign
 	BigNum operator- (const BigNum &x){
 	 	bool Flag=*this<x;
 	 	if (flag^x.flag) return Plus(x,Flag); else
 	 	 if (compare(x)) return Deled(0,x,Flag); else
 	 	   return Del(0,x,Flag);
 	}

 	//Divide it by BigNum x
 	BigNum operator/ (BigNum &x){
 	 	static BigNum Kano,Hama,Kuro;Kano.Clear();
 	 	if (compare(x)) {Kano.len=1;return Kano;}
 	 	memcpy(Kuro.a,a,sizeof a);
 	 	Kano.flag=flag^x.flag;Kuro.flag=flag;
 	 	Kano.len=len-x.len+1;Kuro.len=len;
 	 	for (int i=len-x.len;~i;i--)
 	 	 for (int j=9;~j;j--){
 	 	  	 Hama=x << j;
 	 	  	 if (!Kuro.compare(Hama,i))
 	 	  	   Kuro=Kuro.Del(i,Hama,Kuro.flag),
 	 	  	   Kano.a[i]+=1 << j;
 	 	 }
 	 	Kano.Repair();
 	 	return Kano;
 	}

 	//Modulo it by BigNum x
 	BigNum operator% (BigNum &x){
 	 	static BigNum Hama,Kuro;
 	 	memcpy(Kuro.a,a,sizeof a);
 	 	Kuro.flag=flag;Kuro.len=len;
 	 	if (compare(x)) return Kuro;
 	 	for (int i=len-x.len;~i;i--)
 	 	 for (int j=9;~j;j--){
 	 	  	 Hama=x << j;
 	 	  	 if (!Kuro.compare(Hama,i))
 	 	  	   Kuro=Kuro.Del(i,Hama,Kuro.flag);
 	 	 }
 	 	Kuro.Repair();
 	 	return Kuro;
 	}

 	//Output it
 	void Output(bool Flag = false){
 	 	if (flag) putchar('-');
 	 	printf("%d",a[len-1]);
 	 	for (int i=len-2;i>=0;i--){
 	 	 	if (a[i]<100) putchar('0');
 	 	 	if (a[i]<10) putchar('0');
 	 	 	printf("%d",a[i]);
 	 	}
 	 	if (Flag) puts("");
 	 	return;
 	}
};

/*
	define BigNum bn
	support:
		bn=bn+bn
		bn=bn-bn
		bn=bn*bn
		bn=bn/bn
		bn=bn%bn
		int -> bn: bn.GetInt(int)
		read_bn: bn.GetInput()
*/