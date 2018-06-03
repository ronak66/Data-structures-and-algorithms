#include<stdio.h>
void merge(int a[],int i,int k,int j)
{
	int b[j-i+1];
	int l = i,r = k+1,p=0;
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
	if(j>i)
	{
		int k = (i+j)/2;
		MS(a,i,k);
		MS(a,k+1,j);
		merge(a,i,k,j);
	}
}
int Binary_Search(int *arr,int i,int key,int j)
{
    int mid = (i+j)/2;
    if(i > j)
        return 0;    
    if(arr[mid] == key)
        return 1;
    if(arr[mid] < key)
        return Binary_Search(arr,mid+1,key,j);
    if(arr[mid] > key)
        return Binary_Search(arr,i,key,mid-1);
    return 0;
}
int main()
{
	int n;
	scanf("%d", &n);
	int a[n];
	for (int i=0;i<n;i++)
		scanf("%d", &a[i]);
	int key;
	scanf("%d",&key);
	MS(a,0,n-1);
	int ans = Binary_Search(a,0,key,n-1);
	if(ans == 1)
		printf("YES\n");
	else
		printf("NO\n");
}
