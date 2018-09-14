#include<stdio.h>
#include<stdlib.h>
struct node{
	int vertex;
	struct node *next;
};
struct vrtx{
	int color,pi;
};
void insert(struct node **root,int val){
	struct node *new;
	new=malloc(sizeof(struct node));
	new->vertex=val;
	new->next=*(root);
	*root=new;
}
void enqueue(struct node **head,struct node **tail,int val){
	struct node *new;
	new=malloc(sizeof(struct node));
	new->vertex=val;
	new->next=NULL;
	if(*head==NULL && *tail==NULL){
		*head=new;
		*tail=new;
	}
	else{
		(*head)->next=new;
		*head=new;
	}
}
int dequeue(struct node **head,struct node **tail){
	struct node *temp;
	int r=-1;
	temp=*tail;
	if(temp!=NULL){
		r=temp->vertex;
		*tail=temp->next;
		free(temp);
	}
	if(*tail==NULL)
		*head=NULL;
	return r;
}
void Graph(struct node * graph[],int n,int m){
	int i;
	printf("Enter the edges:\n");
	for(i=0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		insert(&(graph[u-1]),v);
		insert(&(graph[v-1]),u);
	}
}
void BFS(struct node *graph[],struct vrtx vertices[],int s,int n){
	vertices[s-1].color=1;
	//vertices[s-1].d=0;
	vertices[s-1].pi=-1;
	struct node *head,*tail;
	head=malloc(sizeof(struct node));
	tail=malloc(sizeof(struct node));
	head=NULL;
	tail=NULL;
	enqueue(&head,&tail,s);
	while(head!=NULL){
		int del;
		del=dequeue(&head,&tail);
		printf("%d ",del);
		struct node *curr;
		curr=graph[del-1];
		while(curr!=NULL){
			if(vertices[(curr->vertex)-1].color==0){
				vertices[(curr->vertex)-1].color=1;
				//vertices[(curr->vertex)-1].d=vertices[del-1].d+1;
				vertices[(curr->vertex)-1].pi=del;
				enqueue(&head,&tail,(curr->vertex));
			}
			curr=curr->next;
		}
		vertices[del-1].color=2;
	}
	printf("\n");
}
void view_graph(struct node *graph[],int n){
	int i;
	printf("\n");
	for(i=0;i<n;i++){
		struct node *curr;
		curr=graph[i];
		while(curr!=NULL){
			printf("%d ",curr->vertex);
			curr=curr->next;
		}
		printf("\n");
	}
}
int main(){
	int n,m,i;
	printf("Enter the value of n,m:\n");
	scanf("%d%d",&n,&m);
	struct node *graph[n];
	for(i=0;i<n;i++){
		graph[i]=malloc(sizeof(struct node));
		graph[i]=NULL;
	}
	Graph(graph,n,m);
	view_graph(graph,n);
	int s;
	printf("Enter the source vertex:\n");
	scanf("%d",&s);
	struct vrtx vertices[n];
	for(i=0;i<n;i++){
		vertices[i].color=0;
		//vertices[i].d=-1;
		vertices[i].pi=-1;
	}
	BFS(graph,vertices,s,n);
	for(i=0;i<n;i++){
		printf("color:%d pi:%d\n",vertices[i].color,vertices[i].pi);
	}
	
}