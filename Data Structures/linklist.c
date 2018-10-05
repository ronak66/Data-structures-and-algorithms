#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node* next;
};
void addatbegin(struct node **head,int key)
{
	struct node *temp;
	temp = malloc(sizeof(struct node));
	temp->data = key;
	temp->next = (*head);
	(*head) = temp;
}


void addatend(struct node *head,int key)
{
	struct node *temp;
	temp = malloc(sizeof(struct node));
	temp->data = key;
	while(head->next != NULL)
		head = head->next;
	head->next = temp;
	temp->next = NULL;
}

void addatmiddle(struct node *head,int key,int middata)
{
	struct node *temp,*pev;
	temp = malloc(sizeof(struct node));
	temp->data = key;
	while(head->data != middata)
		head = head->next;
	temp->next = head->next;
	head->next = temp;
}

void deleteatbeg(struct node **head)
{
	(*head) = (*head)->next;
}

void deleteatend(struct node *head)
{
	while((head->next)->next != NULL)
		head = head->next;
	head->next = NULL;
}
void deleteatmid(struct node *head,int key)
{
	struct node *temp;
	for(int i=0;i<key;i++)
	{
		temp = head;
		head = head->next;
	}
	temp->next = head->next;
}

void print(struct node* head)
{
	while(head != NULL)
	{
		printf("%d -> ",head->data);
		head = head->next;

	}
	printf("\n");
}
int  main()
{
	struct node *head,*a;
	a = malloc(sizeof(struct node));
	a->data = 1;
	a->next = NULL;
	head = a;
	addatend(head,2);
	addatend(head,3);
	addatbegin(&head,0);
	//deleteatbeg(&head);
	deleteatmid(head,2);
	print(head);
	return 0;
}
