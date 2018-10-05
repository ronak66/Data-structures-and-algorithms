//HashTable is array of linked list
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
//int mode[10] = {65701,44701,32297,50821,88789,22621,61843,31513,62921,49081};

struct node
{
	int data;
	struct node *next;
};

// Prime number and size of hashtable
int m = 88789;
struct node *hashtable[88789];

int hashing_string(char *a,int i,int j,int x)
{
	int p=0;
	for(int k=i;k<j+i;k++)
		p = (p*x + a[k])%m;
	return p;
}

int hashing_int(long long int a)
{
	return a%m;
}

//Here the 'head' is the hashtable[hash], where 'hash' is the hash-value of string or integer
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


int *rolling_hash(char *a,int k,int x)
{
	int *rolling_hash_values = malloc(sizeof(int)*(strlen(a)-k+1));
	int t = hashing_string(a,0,k,x);
	rolling_hash_values[0] = t;
	int h=1;
	for(int i=1;i<k;i++) h = ( h%m * x%m)%m;
	// Calculate hash value for next window of text: Remove leading digit, add trailing digit
	for(int i=0;i<strlen(a)-k;i++){
        t = (x*(t - a[i]*h) + a[i+k])%m;
        // We might get negative value of t, converting it to positive
        if (t < 0) t = (t + m);

		// To confirm that if 't' is same as hashing_string(a,i+1,k,x) then uncomment the next line`
		// printf("%d %d\n",t,hashing_string(a,i+1,k,x));
		rolling_hash_values[i+1] = t;
    }
	return rolling_hash_values;
}
//ablity to handle conflicts
int main()
{
	char string_array[] = "HashtableAndHashing";
	int rollingHash_size = 4;
	int x = 25;
	int *hashed_values = rolling_hash(string_array,rollingHash_size,x);
	int n = strlen(string_array)-rollingHash_size+1;
	for(int i=0;i<n;i++) printf("%d ",hashed_values[i]);
	printf("\n");
	return 0;
}
