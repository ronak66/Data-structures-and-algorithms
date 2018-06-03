#include<stdio.h>
#include<stdlib.h>
struct node{
	int vertex;
	struct node *next;
};
struct vrtx{
	int color,d,f,pi;
};
int time=0;
void insert(struct node **root,int val){
	struct node *new;
	new=malloc(sizeof(struct node));
	new->vertex=val;
	new->next=*(root);
	*root=new;
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
void dfs_visit(struct node *graph[],struct vrtx vertices[],int u){
	time++;
	vertices[u-1].d=time;
	vertices[u-1].color=1;
	struct node *curr;
	curr=graph[u-1];
	while(curr!=NULL){
		if(vertices[(curr->vertex)-1].color==0){
			vertices[(curr->vertex)-1].pi=u;
			dfs_visit(graph,vertices,(curr->vertex));
		}
		curr=curr->next;
	}
	vertices[u-1].color=2;
	time++;
	vertices[u-1].f=time;
}
void DFS(struct node *graph[],struct vrtx vertices[],int n){
	int i;
	for(i=0;i<n;i++){
		if(vertices[i].color==0){
			dfs_visit(graph,vertices,i+1);
		}
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
	struct vrtx vertices[n];
	for(i=0;i<n;i++){
		vertices[i].color=0;
		vertices[i].pi=-1;
		vertices[i].d=0;
		vertices[i].f=0;
	}
	DFS(graph,vertices,n);
	for(i=0;i<n;i++){
		printf("color:%d d:%d f:%d pi:%d\n",vertices[i].color,vertices[i].d,vertices[i].f,vertices[i].pi);
	}
}