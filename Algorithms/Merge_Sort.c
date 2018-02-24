#include<stdio.h>
#include<stdlib.h>
void merge(int a[],int i,int k,int j)
{
	int b[j-i+1];
	int l = i,r = k+1,p=0;
	int count = 0;
	int see = l;
	int inversion=0;
	while(l<=k && r<=j)
	{
		if(a[l] > a[r])
			b[p++] = a[r++];
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

}
void MS(int a[],int i,int j)
{
	int count = 0,x,y,z;
	if(j>i)
	{
		int k = (i+j)/2;
		MS(a,i,k);
		MS(a,k+1,j);
		merge(a,i,k,j);
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	int a[n];
	for (int i=0;i<n;i++)
		scanf("%d", &a[i]);
	int count;
	MS(a,0,n-1);
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");

	return 0;
}

