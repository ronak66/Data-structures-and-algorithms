// Program to implement a queue using two stacks
#include<stdio.h>
#include<stdlib.h>

// structure of a stack node
struct sNode
{
    int data;
    struct sNode *next;
    int min;
};

// structure of queue having two stacks
struct queue
{
    struct sNode *stack1;
    struct sNode *stack2;
};

// Function to enqueue an item to queue
void enQueue(struct queue *q, int x)
{
    push(&q->stack1, x);
}

// Function to dequeue an item from queue
int deQueue(struct queue *q)
{
    int x;
    // If both stacks are empty then error
    if(q->stack1 == NULL && q->stack2 == NULL)
    {
        printf("Q is empty");
        getchar();
        exit(0);
    }

    // Move elements from satck1 to stack 2 only if stack2 is empty
    if(q->stack2 == NULL)
    {
        while(q->stack1 != NULL)
        {
            x = pop(&q->stack1);
            push(&q->stack2, x);

        }
    }

    x = pop(&q->stack2);
    return x;
}

// Function to push an item to stack
void push(struct sNode** top_ref, int new_data)
{
    struct sNode* new_node = (struct sNode*) malloc(sizeof(struct sNode));
    if(new_node == NULL)
    {
        printf("Stack overflow \n");
        getchar();
        exit(0);

    }
    if((*top_ref)==NULL)
    {
        new_node->min=new_data;
    }
    else
    {
        if((*top_ref)->min > new_data)
            new_node->min=new_data;
        else
            new_node->min=(*top_ref)->min;
    }
    new_node->data = new_data;
    new_node->next = (*top_ref);
    (*top_ref) = new_node;
}

//Function to pop an item from stack
int pop(struct sNode** top_ref)
{
    int res;
    struct sNode *top;

    //If stack is empty then error
    if(*top_ref == NULL)
    {
        printf("Stack overflow \n");
        getchar();
        exit(0);

    }
    else
    {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;

    }
}

int get_Min(struct queue *q)
{
    if(q->stack1==NULL && q->stack2==NULL)
        return -1;
    if(q->stack1==NULL)
    {
        return q->stack2->min;
    }
    else if(q->stack2==NULL)
    {
        return q->stack1->min;
    }
    else
    {
        if(q->stack1->min > q->stack2->min)
            return q->stack2->min;
        else
            return q->stack1->min;
    }
}

int main()
{
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->stack1 = NULL;
    q->stack2 = NULL;
    enQueue(q, 2);
    enQueue(q, 1);
    printf("min = %d\n",get_Min(q));
    enQueue(q, 0);
    printf("min = %d\n",get_Min(q));

    printf("%d ", deQueue(q));
    printf("%d ", deQueue(q));
    printf("min = %d\n",get_Min(q));
    printf("%d ", deQueue(q));

}
