#include<stdio.h>
#include<stdlib.h>
int merge(int a[],int i,int k,int j)
{
	int b[j-i+1];
	int l = i,r = k+1,p=0;


	int inversion=0;
	while(l<=k && r<=j)
	{
		if(a[l] > a[r])
		{
			b[p++] = a[r++];
			inversion += k-l+1;
		}
		else
			b[p++] = a[l++];
	}
	while(l <= k)
		b[p++] = a[l++];
	while(r<=j)
		b[p++] = a[r++];
	p=0;
	l=i;
	while(l<=j)
		a[l++]=b[p++];
	return inversion;
}
int MS(int a[],int i,int j)
{
	int x,y,z;
	if(i>=j)
		return 0;
	if(j>i)
	{
		int k = (i+j)/2;
		x = MS(a,i,k);
		y = MS(a,k+1,j);
		z = merge(a,i,k,j);
	}
	return x+y+z;
}
int main()
{
	int n;
	scanf("%d", &n);
	int a[n];
	for (int i=0;i<n;i++)
		scanf("%d", &a[i]);
	int count;
	count = MS(a,0,n-1);
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	printf("count = %d\n",count);
	return 0;
}

