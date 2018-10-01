//In Queue, you add at the end and delete at the beginning
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node* next;
};

// Adding an element to the Queue
void Enqueue(struct node **head,struct node **tail,int key)
{
	struct node *temp;
	temp = malloc(sizeof(struct node));
	temp->data = key;
	if((*head) == NULL)
	{
		(*tail) = temp;
		(*head) = temp;
	}
	else
	{
		(*tail)->next = temp;
		(*tail) = temp;
	}

}

// Deleting an element from the queue
void Dequeue(struct node **head)
{
	(*head) = (*head)->next;
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

int main()
{
	struct node *head,*tail;
	head = NULL;
	tail = NULL;
	Enqueue(&head,&tail,1);
	Enqueue(&head,&tail,2);
	Enqueue(&head,&tail,3);
	Enqueue(&head,&tail,4);
	Enqueue(&head,&tail,5);
	print(head);
	Dequeue(&head);
	print(head);

	return 0;
}
