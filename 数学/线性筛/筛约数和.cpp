//d(i) 表示 i 的约数个数  
//num[i] 表示 i 的最小素因子的个数 
//prim[i] 表示 第 i 个素数
const int N=1e5+5;
bool mark[N];
int prim[N],d[N],num[N];
int cnt;
void initial()
{
    cnt=0;
    d[1]=1;
    for (int i=2 ; i<N ; ++i)
    {
        if (!mark[i])
        {
            prim[cnt++]=i;
            num[i]=1;
            d[i]=2;
        }
        for (int j=0 ; j<cnt && i*prim[j]<N ; ++j)
        {
            mark[i*prim[j]]=1;
            if (!(i%prim[j]))
            {
                num[i*prim[j]]=num[i]+1;
                d[i*prim[j]]=d[i]/(num[i]+1)*(num[i*prim[j]]+1);
                break;
            }
            d[i*prim[j]]=d[i]*d[prim[j]];
            num[i*prim[j]]=1;
        }
    }
}