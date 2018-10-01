//In structures, we add at the beginning and delete at the beginning
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
};

// Adding an element to the stack
void Push(struct node **head,int key)
{
	struct node *temp;
	temp = malloc(sizeof(struct node));
	temp->data = key;
	if((*head) == NULL)
		(*head) = temp;
	else
	{
		temp->next = (*head);
		(*head) = temp;
	}
}

// Deleting an element from the stack
void Pop(struct node **head)
{
	(*head) = (*head)->next;
}

struct node *last(struct node *head)
{
	while(head->next != NULL)
		head = head->next;
	return head;
}

void print(struct node *head)
{
    printf("begginning: ");
	while(head != NULL)
	{
		printf("%d -> ",head->data);
		head = head->next;
	}
	printf("Null :end\n");
}

int main()
{
	int b[4];
	struct node *head;
	Push(&head,1);
	Push(&head,2);
	Push(&head,3);
	Push(&head,4);
	Push(&head,5);
	print(head);
	Pop(&head);
	print(head);

	return 0;
}
