#include<stdio.h>
#include<stdlib.h>
int partition(int *a,int i,int j,int p)
{
	int l = i-1;
	for(int k=i;k<j;k++)
	{
		if(	a[k]<=p)
		{
			l++;
			int temp =a[l];
			a[l] = a[k];
			a[k] = temp;  
		}
	}
	int temp1 = a[l+1];
	a[l+1] = a[j];
	a[j] = temp1;
	return l+1;
}
int findrank(int *a,int i,int j,int r)
{
	if(i<=j)
	{
		int p = (rand()%(j+1-i))+i;
		int temp = a[j];
		a[j] = a[p];
		a[p] = temp;
		int k = partition(a,i,j,a[j]);
		
		if(k == r)
			return a[k];
		else if(k < r)
			return findrank(a,k+1,j,r);
		else
			return findrank(a,i,k-1,r);
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int r;
	scanf("%d",&r);
	int ans= findrank(a,0,n-1,n-r);
	printf("%d\n",ans);
	return 0;
}