#include<stdio.h>
#include<stdlib.h>
#include<string.h>	
struct operator
{
	char a;
	float data;
	struct operator *next;
};
struct postfix
{
	char a;
	float data;
	struct postfix *next;
};
void Pushp(struct postfix **head,int key)
{
	struct postfix *temp;
	temp = malloc(sizeof(struct postfix));
	temp->a = key;
	temp->next = (*head);
	(*head) = temp;	
}
void Popp(struct postfix **head)
{
	(*head) = (*head)->next;
}
void Pusho(struct operator **head,int key)
{
	struct operator *temp;
	temp = malloc(sizeof(struct operator));
	temp->a = key;
	temp->next = (*head);
	(*head) = temp;	
}
void Popo(struct operator **head)
{
	(*head) = (*head)->next;
}
void printo(struct operator *head)
{
	while(head != NULL)
	{
		printf("%c -> ",head->a);
		head = head->next;
	}
	printf("\n");
}
void printp(struct postfix *head)
{
	while(head != NULL)
	{
		printf("%c -> ",head->a);
		head = head->next;
	}
	printf("\n");
}

void atodata(struct postfix *head)
{
	while(head->next != NULL)
	{
		if(head->a != '(' || head->a  != '+' || head->a  != ')' || 
		   head->a  != '-' || head->a  != '*' || head->a  != '/')
			head->data = atof(&(head->a));
		head= head->next;
	}
}
void cal(struct postfix *head)
{
	char b[4] = {'+','-','/','*'};
	float value = -98989;
	while(1)
	{
		if(((head->next)->next)->a == '+')
			value = head->data + (head->next)->data;
		if(((head->next)->next)->a == '-')
			value = head->data - (head->next)->data;
		if(((head->next)->next)->a == '/')
			value = head->data / (head->next)->data;
		if(((head->next)->next)->a == '*')
			value = head->data * (head->next)->data;						
		if(value != -98989)
			break;
		head = head->next;
	}
	head->next = (((head->next)->next)->next);
	head->data = value;
}
void reverse(struct postfix **head)
{
	struct postfix *p =NULL,*c=*head,*n;
	while(c!=NULL)
	{
		n = c->next;
		c->next = p;
		p=c;
		c=n;
	}
	*head = p;
}

int main()
{
	char b[100],expression[100];
	struct operator *heado,*fo;
	struct postfix *headp,*fp;
	scanf(" %s",b);

	//creating expression
	int l=0;
	expression[0] = '(';
	while(b[l] != '\0')
	{
		expression[l+1] = b[l];
		l++;
	}
	expression[l+1] = ')';
	expression[l+2] = '\0';
	////printf("%s\n",expression);

	//head
	fo = malloc(sizeof(struct operator));
	fo->a = expression[0];
	heado = fo;
	fp = malloc(sizeof(struct postfix));
	////fp->a = expression[1];
	headp = fp;
	////printp(headp);
	////printo(heado);

	int counter = 1;
	while(expression[counter] != '\0')
	{
		if(expression[counter] == '(' || expression[counter] == '+' || 
		   expression[counter] == '-' || expression[counter] == '*' || 
		   expression[counter] == '/')
		{
			Pusho(&heado,expression[counter]);
		}
		else if(expression[counter] == ')')
		{
			while(heado->a != '(')
			{
				Pushp(&headp,heado->a);
				Popo(&heado);
			}
			Popo(&heado);
		}
		else
		{
			Pushp(&headp,expression[counter]);
		}
		counter++;
	}
	
	////printp(headp);
	reverse(&headp);
	*headp = *headp->next;
	atodata(headp);

	////printp(headp);
	while(headp->next != NULL)
	{
		cal(headp);
	}	
	////printp(headp);
	printf("%f\n",headp->data);
	return 0;
}
