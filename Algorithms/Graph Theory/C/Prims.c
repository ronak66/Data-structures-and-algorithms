#include <stdio.h>
#include <stdlib.h>

struct list_node 		//linked list
{
	int data;
	int weight;
	struct list_node* next;
};

struct node       		//element of array
{
	int value;
	char c;
	struct list_node* list;
	struct list_node* current;
	struct list_node* start;
	int priority;
	struct node* parent;
};

void print_list(struct list_node* start)
{
	struct list_node* temp=malloc(sizeof(struct list_node));
	temp=start;
	while(start!=NULL)
	{
		printf("%d ",start->data);
		start=start->next;
	}
	start=temp;
	printf("\n");
}

void print_graph(int n, struct node* graph[])
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d : ",graph[i]->value);
		print_list(graph[i]->start);
	}
}

void bottom_up_heapify(struct node *a[],int i)
{
	int p=(i-1)/2;
	struct node *t = (struct node *)malloc(sizeof(struct node));
	while(i>0)
	{
		if(a[p]->priority > a[i]->priority)
		{
			t=a[p];
			a[p]=a[i];
			a[i]=t;
		}
		else 
			break;
		i=p;
		p=(i-1)/2;
	}
}

void top_down_heapify(struct node *a[], int n, int i)
{
	int l=2*i + 1;
	int r=2*i + 2,j;
	struct node *t = (struct node *)malloc(sizeof(struct node));
	if(l==n-1 && a[i]->priority > a[l]->priority)
	{
		t=a[l];
		a[l]=a[i];
		a[i]=t;
		return;
	}
	while(r<n)
	{
		if(a[l]->priority < a[r]->priority)
			j=l;
		else
			j=r;
		if(a[i]->priority < a[j]->priority)
			break;
		else
		{
			t=a[j];
			a[j]=a[i];
			a[i]=t;
		}
		i=j;
		l=2*i+1;
		r=2*i+1;
		if(l==n-1 && a[i]->priority > a[l]->priority)
		{
			t=a[l];
			a[l]=a[i];
			a[i]=t;
			break;	
		}
	}
}

void build_heap(struct node *a[],int n)
{
	int i = n/2;
	while(i >= 0)
	{
		top_down_heapify(a,n,i);
		i--;
	}
}

void heap_insert(struct node* a[], int* n, struct node *num) 
{
	num->c='y';
	a[*n] = num;
	bottom_up_heapify(a,*n);
	(*n)++;
}

struct node * delete_min(struct node *a[],int *n)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp=a[*n-1];
	a[*n-1]=a[0];
	a[0]=temp;
	temp=a[*n-1];
	temp->c='b';
	(*n)--;
	top_down_heapify(a,*n,0);
	return temp;
}

void add_edge(int u, int v, int wt, int n, struct node* graph[])  //edge from u to v
{
	int flag=0;
	for (int i = 0; i < n; ++i)
	{
		if (graph[i]->value==u)
		{
			graph[i]->list = (struct list_node*)malloc(sizeof(struct list_node));
			graph[i]->list->data=v;
			graph[i]->list->weight=wt;
			if (graph[i]->current==NULL)
			{
				graph[i]->current=graph[i]->list;
				graph[i]->current->next=NULL;
				graph[i]->start=graph[i]->current;
			}
			else
			{
				graph[i]->list->next=graph[i]->current;
				graph[i]->current=graph[i]->list;
				graph[i]->start=graph[i]->list;
			}
			flag=1;
		}
	}
	if (flag==0)
	{
		printf("Node doesn't exist.\n");
	}
}

char get_colour(struct node *g[], int n, struct list_node *x)
{
	int t = x->data;
	for (int i = 0; i < n; ++i)
	{
		if (g[i]->value==t)
		{
			return g[i]->c;
		}
	}
}

struct node * get_node(struct node *g[], int n, struct list_node *x)
{
	int t = x->data;
	for (int i = 0; i < n; ++i)
	{
		if (g[i]->value==t)
		{
			return g[i];
		}
	}
}

void Prims(struct node *graph[], int n, struct node * u)
{
	int m=0;
	struct node *a[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = (struct node*)malloc(sizeof(struct node));
	}
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	heap_insert(a,&m,u);
	u->priority=0;
	u->parent=u;
	while(m!=0)
	{
		u=delete_min(a,&m);
		while(u->start!=NULL)
		{
			if(get_colour(graph,n,u->start)=='r')
			{
				temp=get_node(graph,n,u->start);
				temp->priority = u->start->weight;
				temp->parent=u;
				heap_insert(a,&m,temp);
			}
			else if (get_colour(graph,n,u->start)=='y')
			{
				temp=get_node(graph,n,u->start);
				if (temp->priority > u->start->weight)
				{
					temp->priority = u->start->weight;
					temp->parent=u;
				}
			}
			u->start=u->start->next;
		}
	}
}

void shortest_path(struct node * graph[], int n, int a)
{
	struct node * v = (struct node *)malloc(sizeof(struct node));
	for (int i = 0; i < n; ++i)
	{
		if (graph[i]->value == a)
		{
			v=graph[i];
			break;
		}
	}
	Prims(graph,n,v);
	printf("MST :\n");
	for (int i = 1; i < n; ++i)
	{
		printf("%d : %d \n",graph[i]->parent->value,graph[i]->value);
	}	
}

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	//no.of vertices
	struct node* graph[n];
	for (int i = 0; i < n; ++i)
	{
		graph[i]=(struct node*)malloc(sizeof(struct node));
		graph[i]->value = i+1;
		graph[i]->start=graph[i]->current=NULL;
		graph[i]->c='r';
	}

	/*graph[0]->value=41;
	graph[1]->value=30;
	graph[2]->value=10;
	graph[3]->value=2;
	graph[4]->value=5;
	graph[5]->value=61;
	add_edge(41,30,10,n,graph);
	add_edge(30,2,5,n,graph);
	add_edge(30,10,1,n,graph);
	add_edge(10,41,3,n,graph);
	add_edge(10,5,4,n,graph);
	add_edge(5,61,7,n,graph);
	add_edge(2,61,6,n,graph);
	add_edge(30,5,15,n,graph);
	add_edge(30,41,10,n,graph);
	add_edge(2,30,5,n,graph);
	add_edge(10,30,1,n,graph);
	add_edge(41,10,3,n,graph);
	add_edge(5,10,4,n,graph);
	add_edge(61,5,7,n,graph);
	add_edge(61,2,6,n,graph);
	add_edge(5,30,15,n,graph);*/
	for(int i=0;i<m;i++)
	{
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w,n,graph);
	}
	shortest_path(graph,n,graph[1]->value);
	return 0;
}