#include<stdio.h>
int a[1000005],temp[1000005];
long long count; 
void Merge_sort(int L,int mid,int R)
{
	int i=L,j=mid+1,k=L;
	while(i<=mid&&j<=R)
	{
		if(a[i]<=a[j])
		temp[k++]=a[i++];
		else
		{
			temp[k++]=a[j++];
			count+=(mid-i+1);
		}
	}
	while(i<=mid)
	temp[k++]=a[i++];
	while(j<=R)
	temp[k++]=a[j++];
	for(i=L;i<=R;i++)
	a[i]=temp[i];
}
void Merge(int L,int R)
{
	if(L<R)
	{
		int mid=(L+R)/2;
		Merge(L,mid);
		Merge(mid+1,R);
		Merge_sort(L,mid,R);		
	}
}
int main()
{
	int N;
	while(~scanf("%d",&N)&&N)
	{
		int i;
		for(i=0;i<N;i++)
		scanf("%d",&a[i]);
		count=0;
		Merge(0,N-1);
		printf("%lld\n",count);
	}
}