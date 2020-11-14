#include<cstdio>
const int MAXN = 1e5 + 5;
const int inf = 0x7fffffff;

inline int max(int a,int b){ return a>b? a: b;}
inline void chk_max(int &a,int b){ if(a<b) a=b;}

int ans[MAXN<<2],max_ans[MAXN<<2];//区间最大值	区间历史最大值 

bool vis[MAXN<<2];//是否进行过区间赋值操作 
int sum[MAXN<<2], val[MAXN<<2];//上次下放之后的加和	上次下放之后的赋值操作 （赋值之后的加操作一并算入赋值，下同）
int max_sum[MAXN<<2], max_val[MAXN<<2];//上次下放之后达到的最大加和	上次下放之后赋的最大值 
/*
注意这里实际上使用了4个lazy_tag，不过如果您理解了算法的核心，您应该知道我在干什么
*/
#define ls(u) ((u)<<1)
#define rs(u) ((u)<<1|1)//个人习惯，左右儿子


inline void push_up(int u)//push_up比较简单，就是用左右儿子的答案更新本节点的答案
{
    ans[u] = max(ans[ls(u)], ans[rs(u)]);
    max_ans[u] = max(max_ans[ls(u)], max_ans[rs(u)]);
}


//我将更新lazy_tag的操作打包成函数，不然有可能在细节上出错（其实我一开始就是在这里出的错）
/*
更新加操作的tag，分为两种情况：
 1.赋过值，算作赋值操作
 2.没赋过值
*/
inline void do_sum(int u,int k,int max_k)//max_k表示父节点在上一次push_down之后达到的最大加和
{
    if(vis[u])
    {
        chk_max(max_val[u], val[u]+max_k);
        chk_max(max_ans[u], ans[u]+max_k);
        ans[u]+=k;
        val[u]+=k;
    }
    else
    {
        chk_max(max_sum[u], sum[u]+max_k);
        chk_max(max_ans[u], ans[u]+max_k);
        ans[u]+=k;
        sum[u]+=k;
    }
}

inline void do_val(int u,int k,int max_k)//max_k表示父节点在上一次push_down之后达到的最大赋值
{
	if(vis[u])
	{
		chk_max(max_val[u], max_k);
    	chk_max(max_ans[u], max_k);
	}
    else
    {
    	vis[u]=1;//该点标记为赋过值
    	max_val[u] = max_k;
    	chk_max(max_ans[u], max_k);
	}
    ans[u] = val[u] = k;
}

inline void push_down(int u)
{
    do_sum(ls(u),sum[u],max_sum[u]);
    do_sum(rs(u),sum[u],max_sum[u]);//先传递和
    
    sum[u] = max_sum[u] = 0;//下传之后清零
    
    if(vis[u])
    {
        do_val(ls(u),val[u],max_val[u]);
        do_val(rs(u),val[u],max_val[u]);
        
        vis[u] = 0;
        val[u] = max_val[u] = 0;//下传之后清零
    }
}

void build(int u,int l,int r)//建树
{
    if(l==r)
    {
        scanf("%d",&ans[u]);
        max_ans[u]=ans[u];
        return;
    }
    
    int mid=(l+r)>>1;
    build(ls(u),l,mid);
    build(rs(u),mid+1,r);
    push_up(u);
}

int query(int u,int l,int r, int ql,int qr)//Q操作
{
    if(ql<=l && r<=qr) return ans[u];
    
    push_down(u);
    int mid=(l+r)>>1, ret=-inf;
    if(ql<=mid) ret = query(ls(u),l,mid, ql,qr);
    if(mid<qr) chk_max(ret, query(rs(u),mid+1,r, ql,qr));
    
    return ret;
}

int query_max(int u,int l,int r, int ql,int qr)//A操作，与Q类似
{
    if(ql<=l && r<=qr) return max_ans[u];
    
    push_down(u);
    int mid=(l+r)>>1, ret=-inf;
    if(ql<=mid) ret = query_max(ls(u),l,mid, ql,qr);
    if(mid<qr) chk_max(ret, query_max(rs(u),mid+1,r, ql,qr));
    
    return ret;
}

void add(int u,int l,int r, int ql,int qr,int k)//P操作
{
    if(ql<=l && r<=qr)
    {
        do_sum(u,k,k);//这里max_k也填k就行了
        return;
    }
    
    push_down(u);
    int mid = (l+r)>>1;
    if(ql<=mid) add(ls(u),l,mid, ql,qr,k);
    if(mid<qr) add(rs(u),mid+1,r, ql,qr,k);
    push_up(u);
}

void assign(int u,int l,int r, int ql,int qr,int k)//C操作
{
    if(ql<=l && r<=qr)
    {
        do_val(u,k,k);
        return;
    }
    
    push_down(u);
    int mid = (l+r)>>1;
    if(ql<=mid) assign(ls(u),l,mid, ql,qr,k);
    if(mid<qr) assign(rs(u),mid+1,r, ql,qr,k);
    push_up(u);
}

//这两个函数是调试用的，用于打印序列
void print(int u,int l,int r)
{
    if(l==r)
    {
        printf("%d ",ans[u]);
        return;
    }
    push_down(u);
    int mid=(l+r)>>1;
    print(ls(u),l,mid);
    print(rs(u),mid+1,r);
}
inline void test(int t)
{
    printf("=========================================\n");
    print(1,1,t);
    printf("\n=========================================\n");
}

int main(void)
{
    int t;
    scanf("%d",&t);
    build(1,1,t);
    
    int e;
    scanf("%d",&e);
    while(e--)
    {
        char c=getchar();
        while(c!='Q' && c!='A' && c!='P' && c!='C') c=getchar();//个人习惯，感觉这么写比较保险 
        int x,y;
        scanf("%d%d",&x,&y);
        
        if(c=='Q') printf("%d\n",query(1,1,t, x,y));
        if(c=='A') printf("%d\n",query_max(1,1,t, x,y));
        if(c=='P')
        {
            int z;
            scanf("%d",&z);
            add(1,1,t, x,y,z);
            //test(t);
        }
        if(c=='C')
        {
            int z;
            scanf("%d",&z);
            assign(1,1,t, x,y,z);
            //test(t);
        }
    }
    return 0;
}