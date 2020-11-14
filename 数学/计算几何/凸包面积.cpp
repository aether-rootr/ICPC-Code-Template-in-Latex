struct Point{
   double x,y;
}p[N];
 
int n;
double polygonarea()
{
    int i,j;
    double area = 0;
    for(i = 0;i < n;++i){
        j = (i+1)%n;
        area += p[i].x*p[j].y;
        area -= p[i].y*p[j].x;
    }
    //area /= 2.0;
    return area;
}