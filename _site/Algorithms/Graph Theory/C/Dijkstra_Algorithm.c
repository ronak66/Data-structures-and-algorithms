#include<stdio.h>
#include<stdlib.h>
struct node
{
	int heap;
	int data;
	struct node_ll *next;
	int colour;
	struct node *p;
	int pri;
};
struct node_ll
{
	int data;
	struct node_ll *next;
	struct node *parent;
	int weight;
};

int heap_elements=0;
struct node *min_heap[100];
void swap(struct node** a,struct node** b);


void bottom_up_heapyfy(struct node *arr[] , int i)
{
	int p = (i-1)/2;
	while(p>=0)
	{
		if(arr[i]->pri<arr[p]->pri)
		{
			arr[i]->heap=p;
			arr[p]->heap=i;
			swap(&arr[i],&arr[p]);
		}
		else
			break;
		i = p;
		p = (i-1)/2;
	}
}
void top_down_heapyfy(struct node* arr[] , int i)
{
	int l = 2*i+1;
	int r = 2*i+2;
	int j;
	int k=i;
	while(r<heap_elements)
	{
		if(arr[l]->pri <= arr[r]->pri)
			j = l;
		else
			j = r;
		if(arr[i]->pri > arr[j]->pri)
		{
			arr[i]->heap=j;
			arr[j]->heap=i;
			swap(&arr[i],&arr[j]);
		}
		else
			break;
		i = j;
		l = 2*i+1;
		r = 2*i+2;
	}
	if (l == heap_elements-1 && arr[i] > arr[l])
	{
		arr[i]->heap=l;
		arr[l]->heap=i;
		swap(&arr[i],&arr[l]);
	}
}
void swap(struct node** a,struct node** b)
{
	struct node* t;
	t = *a;
	*a = *b;
	*b = t;
}
void Add_element(struct node* arr[],struct node* n)
{
	arr[heap_elements] = n;
	n->heap=heap_elements;			
	bottom_up_heapyfy(arr,heap_elements);
	heap_elements++;
}
struct node* Delete(struct node* arr[])
{
	if(heap_elements > 0)
	{
		arr[0]->heap=heap_elements-1;
		arr[heap_elements-1]->heap=0;
		swap(&arr[0],&arr[heap_elements-1]);
		heap_elements--;
		top_down_heapyfy(arr,0);
		return arr[heap_elements];
	}
	return NULL;
}
void add_edge(struct node *arr[],struct node *s,struct node *e,int w,int n)
{
	struct node_ll *new;
	int i;
	new=(struct node_ll*)malloc(sizeof(struct node_ll));
	new->data=e->data;
	new->weight=w;
	
	new->parent=e;
	
	if(s->next == NULL)
		s->next = new;
	else
	{
		struct node_ll *cur = s->next;
		while(cur->next!=NULL)
			cur = cur->next;
		cur->next = new;
		new->next = NULL;
	}
}
void dijkstra(struct node *arr[],struct node *s,int n)
{
	struct node *u,*w;
	struct node_ll *v;
	int i=0;
	Add_element(min_heap,s);
	s->colour = 1;
	s->p=s;
	s->pri=0;
	while(heap_elements>0)
	{
		u=Delete(min_heap);
		//printf("%d %d %d\n",u->data,(u->p)->data,u->pri);
		u->colour = 2;
		v=u->next;
		while(v!=NULL)
		{
			w = v->parent;
			if(w->colour==0)
			{
				w->pri=u->pri+v->weight;
				w->colour=1;
				w->p=u;
				Add_element(min_heap,w);
			}
			else if(w->colour==1)
			{
				if(w->pri>u->pri+v->weight)
				{
					w->pri=u->pri+v->weight;
					bottom_up_heapyfy(min_heap,w->heap);
					w->p=u;
				}
			}
			v=v->next;
		}
	}
}
void print_path(struct node *v)
{
	if(v->p==v)
		printf("%d ",v->data);
	else
	{
		print_path(v->p);
		printf("%d ",v->data);
	}
}



void main()
{
	int n,m;
	scanf("%d %d",&n,&m);

	struct node_ll *cur;
	struct node *arr[n];
	int i;

	for(int j=0;j<n;j++)
	{
		arr[j] = (struct node*)malloc(sizeof(struct node));
		arr[j]->data = j+1;
	}
	for(int j=0;j<m;j++)
	{
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		add_edge(arr,arr[u-1],arr[v-1],w,n);
	}

	dijkstra(arr,arr[0],5);
	printf("\n");
	print_path(arr[2]);
	printf("\n");
}