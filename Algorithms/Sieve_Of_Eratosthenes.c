#include<stdio.h>
#include<stdlib.h>
void SieveOfEratosthenes(int n)
{
    int prime[n+1];
    for(int i=2;i<n+1;i++)
        prime[i] = 1;
 
    for (int p=2; p*p<=n; p++)
    {
        if (prime[p] == 1)
        {
            for (int i=p*2; i<=n; i += p)
                prime[i] = 0;
        }
    }
 
    for (int p=2; p<=n; p++)
    {
        if (prime[p]==1)
            printf("%d ",p);
    }
    printf("\n");
}
int main()
{
    int n;
    scanf("%d",&n);
    SieveOfEratosthenes(n);
    return 0;
}

