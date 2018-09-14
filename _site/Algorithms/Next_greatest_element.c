#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	int i;
	struct node *next;
};
void push(struct node **head,int key,int i)
{
	struct node *temp;
	temp = malloc(sizeof(struct node));
	temp->data = key;
	temp->i = i;
	temp->next = (*head);
	(*head) = temp;	
}
void print(struct node *head)
{
	while(head != NULL)
	{
		printf("%d -> ",head->data);
		head = head->next;
	}
	printf("\n");
}
void pop(struct node **head)
{
	(*head) = (*head)->next;
}
int main()
{
	struct node *head;
	head = NULL;
	int n;
	scanf("%d", &n);
	int a[n],b[n];
	for (int j=0;j<n;j++)
		scanf("%d", &a[j]);	
	//push(&head,a[0],0);
	////printf("%d\n",head->i);
	for(int j=0;j<n;j++)
		b[j] = -1;
	for(int j=0;j<n;j++)
	{
		while(head != NULL && a[j]>head->data)
		{
			b[head->i] = j; 
			pop(&head);
		}

		if(head != NULL && a[j] < head->data)
			push(&head,a[j],j);
		if(head == NULL)
			push(&head,a[j],j);
	}
	for(int j=0;j<n;j++)
		printf("%d ",b[j]);
	printf("\n");
	return 0;	
}