//sd(i) 表示 i 的约数和
//sp[i] 表示 i 的最小素因子的等比数列的和
//prim[i] 表示第 i 个素数
const int N=1e5+5;
bool mark[N];
int prim[N];
long long sd[N],sp[N];
int cnt;
void initial()
{
    cnt=0;
    sd[1]=1;
    for (int i=2 ; i<N ; ++i)
    {
        if (!mark[i])
        {
            prim[cnt++]=i;
            sd[i]=i+1;
            sp[i]=i+1;
        }
        for (int j=0 ; j<cnt && i*prim[j]<N ; ++j)
        {
            mark[i*prim[j]]=1;
            if (!(i%prim[j]))
            {
                sp[i*prim[j]]=sp[i]*prim[j]+1;
                sd[i*prim[j]]=sd[i]/sp[i]*sp[i*prim[j]];
                break;
            }
            sd[i*prim[j]]=sd[i]*sd[prim[j]];
            sp[i*prim[j]]=1+prim[j];
        }
    }
}