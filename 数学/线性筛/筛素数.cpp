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
            if (!(i%prim[j])) break;
        }
    }
}