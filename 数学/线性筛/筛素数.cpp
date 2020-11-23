/*
如果我们从小到大考虑每个数，然后同时把当前这个数的所有（比自己大的）
倍数记为合数，那么运行结束的时候没有被标记的数就是素数了。
*/
const int N=1e5+5;
bool mark[N];
int prim[N];
int cnt;
void initial(){
    cnt=0;
    for (int i=2 ; i<N ; ++i){
        if (!mark[i]) prim[cnt++]=i;
        for (int j=0 ; j<cnt && i*prim[j]<N ; ++j){
            mark[i*prim[j]]=1;
            /*
				i % prim[j] == 0
        		换言之，i 之前被 pri[j] 筛过了
        		由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定也是
        		pri[j] 的倍数它们都被筛过了，就不需要再筛了，所以这里直接 break掉就好了
            */
            if (!(i%prim[j])) break;
        }
    }
}