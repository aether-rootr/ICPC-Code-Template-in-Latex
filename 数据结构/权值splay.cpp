#include <bits/stdc++.h>

using namespace std;

int input(){
    int x=0,f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f? -x:x;
}

#define N 500007
#define debug printf("pass in line:%d\n",__LINE__)

class splay{
    public:
        struct node{
            int ch[2];
            int fa,cnt,val,siz;
        }t[N];

        int rt;

        splay(){
            tot=0;
            rt=0;
        }

        void Splay(int x,int goal){
            while(t[x].fa!=goal){
                int y=t[x].fa,z=t[y].fa;
                if(z!=goal) (t[y].ch[0]==x)^(t[z].ch[0]==y)? Rot(x):Rot(y);
                Rot(x);
            }
            if(!goal) rt=x;
        }
        
        void Ins(int x){
            int u=rt,fa=0;
            while(u&&t[u].val!=x) fa=u,u=t[u].ch[x>t[u].val];
            if(u) t[u].cnt++;
            else{
                u=++tot;
                if(fa) t[fa].ch[x>t[fa].val]=u;
                t[tot].ch[0]=0,t[tot].ch[1]=0;
                t[tot].fa=fa,t[tot].val=x;
                t[tot].cnt=1,t[tot].siz=1;
            }
            Splay(u,0);
        }

        int find(int x){
            Find(x);
            return t[t[rt].ch[0]].siz;
        }

        int Next(int x,int f){
            Find(x);
            int u=rt;
            if((t[u].val>x&&f)||(t[u].val<x&&!f)) return u;
            u=t[u].ch[f];
            while(t[u].ch[f^1]) u=t[u].ch[f^1];
            return u;
        }

        void Del(int x){
            int last=Next(x,0),next=Next(x,1);
            Splay(last,0),Splay(next,last);
            int del=t[next].ch[0];
            if(t[del].cnt>1){
                t[del].cnt--;
                Splay(del,0);
            }else t[next].ch[0]=0;
        }

        int K_th(int x){
             int u=rt;
             if(t[u].siz<x) return 0;
             while(1){
                int y=t[u].ch[0];
                if(x>t[y].siz+t[u].cnt) x-=t[y].siz+t[u].cnt,u=t[u].ch[1];
                else if(t[y].siz>=x) u=y;
                else return t[u].val;
             }
        }
    private:
        int tot;
        
        void Push_up(int u){
            t[u].siz=t[t[u].ch[0]].siz+t[t[u].ch[1]].siz+t[u].cnt;
        }

        void Rot(int x){
            int y=t[x].fa,z=t[y].fa,k=t[y].ch[1]==x;
            t[z].ch[t[z].ch[1]==y]=x,t[x].fa=z;
            t[y].ch[k]=t[x].ch[k^1],t[t[x].ch[k^1]].fa=y;
            t[x].ch[k^1]=y;t[y].fa=x;
            Push_up(y),Push_up(x);
        }

         void Find(int x){
            int u=rt;
            if(!u) return;
            while(t[u].ch[x>t[u].val]&&x!=t[u].val) u=t[u].ch[x>t[u].val];
            Splay(u,0);
        }
};

splay Splay;
int n;

int main(){
    n=input();
    Splay.Ins(-2147483647);
    Splay.Ins(2147483647);
    while(n--){
        int opt=input();
        if(opt==1) Splay.Ins(input());
        else if(opt==2) Splay.Del(input());
        else if(opt==3) printf("%d\n",Splay.find(input()));
        else if(opt==4) printf("%d\n",Splay.K_th(input()+1));
        else if(opt==5) printf("%d\n",Splay.t[Splay.Next(input(),0)].val);
        else if(opt==6) printf("%d\n",Splay.t[Splay.Next(input(),1)].val);
    }
}