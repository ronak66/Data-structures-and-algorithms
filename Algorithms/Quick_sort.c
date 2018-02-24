#include<stdio.h>
#include<stdlib.h>
int partition(int *a,int i,int j,int p)
{
	int l = i,r=j;
	while(l<=r)
	{
		while(a[l] <= p && l<=r)
			l++;
		while(a[r]>p && l<=r)
			r--;
		if(l<r)
		{
			int temp = a[l];
			a[l] = a[r];
			a[r] = temp;
			l++;
			r--;

		}
	}
	int ll=i;
	while(a[ll]<=p)
		ll++;
	return ll-1;
}
int quicksort(int *a,int i,int j)
{
	if(i<j)
	{
		int p = a[(rand()%(j+1-i))+i];
		int k = partition(a,i,j,p);
		quicksort(a,i,k);
		quicksort(a,k+1,j);
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	quicksort(a,0,n-1);
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;

}