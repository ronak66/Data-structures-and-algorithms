#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int mode[10] = {65701,44701,32297,50821,88789,22621,61843,31513,62921,49081};
int hash(char *a,int i,int j,int d,int q)
{
	int p=0;
	for(int k=i;k<j+i;k++)
		p = (d*p + a[k])%q;
	return p;
}
int *pallindrome(char *a,int n)
{
	char b[n];
	int *ans;
	ans = malloc(sizeof(int)*2);
	ans[0] = 0;
	ans[1] = 1;
	for(int i=0;i<n;i++)
		b[i] = a[n-1-i];
	srand(time(0));
	int d = 256,h=1,q = mode[rand()%10];
    for (int i = 0; i < 1; i++)
        h = (h*d)%q;	

	for(int l=2;l<=n;l++)
	{
		if(l != 2)
			h = (h*d)%q;
		int ll=0,kk;
		int h1 = hash(a,ll++,l,d,q);
		int h2 = hash(b,n-l,l,d,q);
 		for(int i=l;i<=n;i++)
 		{
 			if(h1 == h2)
 			{
 				/*int jj = i-l;
 				for(kk=jj;kk<jj+l;kk++)
 				{
 					if(a[kk] == b[n-i+kk])
 						continue;
 					else
 						break;
 				}
 				if(kk == jj+l)
 				{*/
 					ans[1] = l;
 					ans[0] = i-l;
 					break;
 				//}
 			}
 			h1 = (d*(h1-a[i-l]*h)+a[i])%q;
 			if(h1<0)
 				h1+=q;
 			//h1 = hash(a,ll++,l,d,q);
 			h2 = hash(b,n-(i+1),l,d,q);
 		}
	}
	
	return ans;

}

int main()
{
	int  a;
	scanf("%d",&a);
	char n[10];
	scanf("%s",n);
	//printf("%s\n",n);
	int *b;
	b = pallindrome(n,a);
	for(int i=b[0];i<b[0]+b[1];i++)
		printf("%c",n[i]);
	printf("\n%d\n",b[1]);

	return 0;
}