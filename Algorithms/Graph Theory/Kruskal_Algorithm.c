#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	int color;
	struct node_ll *next;
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


void kruskal(struct node *graph[],struct node *MST[],int *u,int *v,int *w,int m,int n,struct col_num *color[])
{
	for(int i=0;i<m;i++)
	{
		if(graph[u[i]-1]->color != graph[v[i]-1]->color)
		{
			if(color[u[i]-1]->num >= color[v[i]-1]->num)
			{
				struct node_ll *temp = (graph[v[i]-1]->next);
				struct node *curr = graph[u[i]-1];
				while(curr->next != NULL)
				{
					curr = curr->next;

				}
				*(curr->next) = *temp;
				while(curr->next != NULL)
					curr = curr->next;
				struct node_ll *temppp;
				temppp->data = graph[v[i]-1]->data;
				temppp->next=NULL;
				temppp->parent = graph[v[i]-1];
				temppp->weight = w[i];

				curr = (graph[u[i]-1])->next;
				while(curr != NULL)
				{
					(curr->parent)->color = graph[u[i]-1]->color;
				}
				graph[v[i]-1]->next = NULL;	

			}
		}
	}
}
void swap(int *a,int *b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	struct node *graph[n];
	struct node *MST[n];
	struct col_num *color[n];
	for(int i=0i<n;i++)
	{
		graph[i] = (struct node*)malloc(sizeof(struct node));
		color[i] = (struct col_num*)malloc(sizeof(struct col_num));
		graph[i]->data = i+1;
		graph[i]->color = i+1;
		graph[i]->next = NULL;
		color[i]->next = graph[i];
	}
	int u[m],v[m],w[m];
	for(int i=0;i<m;i++)
		scanf("%d %d %d",u[i],v[i],w[i]);
	for(int i=0;i<m;i++)
	{
		for(int j=i+1;j<m;j++)
		{
			if(w[i] > w[j])
			{
				swap(w[i],w[j]);
				swap(u[i],u[j]);
				swap(u[i],u[j]);
			}
		}
	}

	kruskal(graph,MST,u,v,w)

}