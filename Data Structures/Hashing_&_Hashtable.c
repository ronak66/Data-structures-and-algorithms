#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int mode[10] = {65701,44701,32297,50821,88789,22621,61843,31513,62921,49081};

//HashTable is actually array of linklist
struct node
{
	int data;
	struct node *next;
};
srand(time(0));
int q = mode[rand()%10];
struct node *hashtable[q]
int hashing_string(char *a,int i,int j,int d)
{
	int p=0;
	for(int k=i;k<j+i;k++)
		p = (d*p + a[k])%q;
	return p;
}
int hashing_int(long long int a)
{
	retrun a%q;
}

//Here the 'head' is the hashtable[hash], where hash is the hash-value of
//string or integer
void hash_insert(struct node **head,int key)
{
	struct node *temp;
	temp = malloc(sizeof(struct node));
	temp->data = key;
	if((*head)==NULL)
		(*head) = temp;
	else
	{
		temp->next = (*head);
		(*head) = temp;
	}	
}
void deleteatmid(struct node *head,int key)
{
	struct node *temp;
	temp = malloc(sizeof(struct node));
	for(int i=0;i<key;i++)
	{
		temp = head;
		head = head->next;
	}
	temp->next = head->next;
}

void rolling_hash(char *a,int m,int d)
{
	int t = hashing_string(a,0,m,d);
    // Calculate hash value for next window of text: Remove
    // leading digit, add trailing digit
    if ( i < N-M )
    {
        t = (d*(t - txt[i]*h) + txt[i+M])%q;

        // We might get negative value of t, converting it
        // to positive
        if (t < 0)
        	t = (t + q);
    }
}