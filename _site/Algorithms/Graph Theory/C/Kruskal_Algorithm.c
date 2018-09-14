N#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	int color;
	struct node_ll *next;
	struct node *nextt;
};
struct node_ll
{
	int data;
	struct node_ll *next;
	struct node *parent;
	int weight;
};
struct col_num
{
	int num;
	struct node *next;
};

void insert(struct node *graph[],int i,int *u,int *v,int *w)
{
	struct node_ll *new;
	new=(struct node_ll*)malloc(sizeof(struct node_ll));
	new->data=graph[v[i]-1]->data;
	new->weight=w[i];
	new->parent=graph[v[i]-1];
	
	if(graph[u[i]-1]->next == NULL)
		graph[u[i]-1]->next = new;
	else
	{
		struct node_ll *cur = graph[u[i]-1]->next;
		while(cur->next!=NULL)
			cur = cur->next;
		cur->next = new;
		new->next = NULL;
	}
}

void insert_color(struct node *graph[],struct col_num *color[],int i,int *u,int *v)
{
	struct node *temp;
	*temp = *(color[graph[v[i]-1]->color - 1]->next);
	struct node *curr;
	curr = color[graph[u[i]-1]->color - 1]->next;
	if(curr == NULL)
		color[graph[u[i]-1]->color - 1]->next = temp;
	else
	{
		while(curr->nextt != NULL)
			curr = curr->nextt;
		curr->nextt = temp;
	}
	int count = 0;
	struct node *test;
	test = color[graph[u[i]-1]->color - 1]->next;
	while(test)
	{
		count ++;
		test->color = graph[u[i]-1]->color;
		test = test->nextt;
	}
	//color[graph[u[i]-1]->color - 1]->num = count;
	//color[graph[v[i]-1]->color - 1]->next = NULL;
	//color[graph[v[i]-1]->color - 1]->num = 0;


}

void kruskal(struct node *graph[],int *u,int *v,int *w,int m,int n,struct col_num *color[])
{
	for(int i=0;i<m;i++)
	{
		if(graph[u[i]-1]->color != graph[v[i]-1]->color)
		{
			insert(graph,i,u,v,w);
			if(color[graph[u[i]-1]->color - 1]->num >= color[graph[v[i]-1]->color - 1]->num)
			{
				insert_color(graph,color,i,u,v);
			}
			else
				insert_color(graph,color,i,v,u);
		}
	}
		
		
}
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	* b = temp;
}

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	struct node *graph[n];
	struct node *MST[n];
	struct col_num *color[n];
	for(int i=0;i<n;i++)
	{
		graph[i] = (struct node*)malloc(sizeof(struct node));
		color[i] = (struct col_num*)malloc(sizeof(struct col_num));
		graph[i]->data = i+1;
		graph[i]->color = i+1;
		graph[i]->next = NULL;
		color[i]->num = 1;
		color[i]->next = graph[i];
	}
	
	int u[m],v[m],w[m];
	for(int i=0;i<m;i++)
	{
		scanf("%d %d %d",&u[i],&v[i],&w[i]);

	}
	//printf("kjasnkjanckjnskjcndskjcnv ds\n");
	for(int i=0;i<m;i++)
	{
		
		for(int j=0;j<m-i-1;j++)
		{
			
			if(w[j] > w[j+1])
			{
				
				swap(&w[j],&w[j+1]);
				swap(&u[j],&u[j+1]);
				swap(&v[j],&v[j+1]);
				
			}
		
		}
	}
	
	
	kruskal(graph,u,v,w,m,n,color);
	printf("\n");
	for(int i=0;i<n;i++)
	{
		struct node_ll *c;
		c = graph[i]->next;
		while(c)
		{
			printf("%d ",c->data);
			c = c->next;
		}
		printf("\n");
	}
}