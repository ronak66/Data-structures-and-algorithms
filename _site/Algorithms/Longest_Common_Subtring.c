#include<stdio.h>
#include<string.h>
 
#define BASE 9584612342
#define MOD 34369934
int visited[35000000];
long long int head[35000000];
long long int next[35000000];
int mark=0;long long int i,l1=0,l2=0;
char s1[250010];
char s2[250010];
void insert(long long int hash,long long int position)
{
    if(visited[hash]!=mark)
    {
        visited[hash]=mark;
        head[hash]=-1;
    }
    next[position]=head[hash];
    head[hash]=position;
}
int check(long long int hash, long long int position,long long int l)
{
    if(visited[hash]!=mark)
        return 0;
    long long int j;
    for(i=head[hash];i!=-1;i=next[i])
    {
        for(j=0;j<l;j++)
        {
            if(s1[i+j]!=s2[position+j])
                break;
        }
        if(j==l)
            return 1;
    }
    return 0; 
}
long long int substring_exist(long long int l )
{
    mark++;
    if(l==0)
    {
        return -1;
    }
    long long int hash1=0,weight=1,hash2=0,i;
 
    for(i=0;i<l-1;i++)
    {
        weight=(weight*BASE)%MOD;
    }
    for(i=0;i<l;i++)
    {
        hash1=(hash1*BASE+s1[i])%MOD;
        hash2=(hash2*BASE+s2[i])%MOD;
    }
    insert(hash1,0);
    for(i=0;i<l1-l;i++)
    {
        hash1 = ((((hash1 - (s1[i]*weight)%MOD + MOD)%MOD)*BASE)%MOD + s1[i+l])%MOD;
        insert(hash1,i+1);
    }
    if(check(hash2,0,l))
        return 0;
    for(i=0;i<l2-l;i++)
    {
        hash2 = ((((hash2 - (s2[i]*weight)%MOD + MOD)%MOD * BASE)%MOD) + s2[i+l]%MOD);
        if(check(hash2,i+1,l))
            return i+1;
    }
    return -1;
}
int main()
 
{ 
    scanf("%s",s1);
    scanf("%s",s2);
    for(i=0;s1[i]!='\0';i++)
        l1++;
    for(i=0;s2[i]!='\0';i++)
        l2++;
        long long int low,mid,high,start_index;
        low=0;
        high=l2;
        while(high>low)
        {
            mid=(high+low+1)>>1;
            if(substring_exist(mid)!=-1)
                low=mid;
            else
                high=mid-1;
        }
        start_index=substring_exist(low);
        if(start_index!=-1)
        {
            s2[start_index+low]='\0';
            printf("%s\n%lld\n",s2+start_index,low);
        }
        else
            printf("0\n");
 
    return 0;
}
 
 

