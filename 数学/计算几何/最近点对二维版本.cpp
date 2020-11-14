// 题意：给n个二维坐标，求任意两点最近的欧几里得距离的一半。
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node
{
    double x,y;
};
bool cmpx(node a,node b)
{
    return a.x<b.x;
}
bool cmpy(node a,node b)
{
    return a.y<b.y;
}
node p[N], a[N];
int cnt, n;
double dis(node a, node b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double run(int l, int r)
{
 
    if(l + 1 == r) return dis(p[l], p[r]);
    if(l + 2 == r){
        return min({dis(p[l],p[l+1]), dis(p[l],p[l+2]), dis(p[l+1],p[l+2])});
    }
    int mid = l + r >> 1;
    double ans = min(run(l, mid), run(mid+1, r));
    cnt = 0;
    for(int i=l;i<=r;++i){
        if(p[i].x >= p[mid].x - ans && p[i].x <= p[mid].x + ans){
            a[cnt++] = p[i];
        }
    }
    sort(a, a+cnt, cmpy);
    for(int i=0;i<cnt;++i){
        for(int j=i+1;j<cnt;++j){
            if(a[j].y-a[i].y > ans) break;
            ans = min(ans, dis(a[i], a[j]));
        }
    }
    return ans;
 
}
int main()
{
    while(~scanf("%d", &n)&&n){
        for(int i=0;i<n;++i){
            scanf("%lf%lf", &p[i].x,&p[i].y);
        }
        sort(p, p+n, cmpx);
        printf("%.2f\n", run(0, n - 1) / 2);
    }
}