#include<stdio.h>
#include <stdlib.h>

struct node{
	int key;
	int height;
	int numNodes; 
	struct node *left,*right;
};

int max(int a,int b)
{
	return (a>b)? a:b;
}

struct node* newNode(int key)
{
    struct node* nodee = malloc(sizeof(struct node));
    nodee->key   = key;
    nodee->left   = NULL;
    nodee->right  = NULL;
    nodee->height = 0; 
    nodee->numNodes = 1;
    return(nodee);
}

int height(struct node *N)
{
    if (N == NULL)
        return -1;
    return N->height;
}
int getnodes(struct node *N)
{
	if(N == NULL)
		return 0;
	return N->numNodes;
}

int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* r_zigzag(struct node* z)
{
	struct node *y = z->right;
	struct node *x = y->left;
	struct node *T2 = x->left, *T3 = x->right;
	x->left = z;
	x->right = y;
	z->right = T2;
	y->left = T3;

	z->height = max(height(z->left),height(z->right))+1;
	y->height = max(height(y->left),height(y->right))+1;
	x->height = max(height(x->left),height(x->right))+1;

	z->numNodes = getnodes(z->left)+getnodes(z->right)+1;
	y->numNodes = getnodes(y->left)+getnodes(y->right)+1;
	x->numNodes = getnodes(x->left)+getnodes(x->right)+1;



	return x;
}
struct node* l_zigzag(struct node* z)
{
	struct node *y = z->left;
	struct node *x = y->right;
	struct node *T2 = x->left, *T3 = x->right;
	x->left = y;
	x->right = z;
	z->left = T2;
	y->right = T3;

	z->height = max(height(z->left),height(z->right))+1;
	y->height = max(height(y->left),height(y->right))+1;
	x->height = max(height(x->left),height(x->right))+1;

	z->numNodes = getnodes(z->left)+getnodes(z->right)+1;
	y->numNodes = getnodes(y->left)+getnodes(y->right)+1;
	x->numNodes = getnodes(x->left)+getnodes(x->right)+1;

	return x;
}
struct node* r_zigzig(struct node* z)
{
	struct node *y = z->right;
	struct node *x = y->right;
	struct node *T2 = y->left;
	y->right = x;
	y->left = z;
	z->right = T2;

	z->height = max(height(z->left),height(z->right))+1;
	x->height = max(height(x->left),height(x->right))+1;
	y->height = max(height(y->left),height(y->right))+1;

	z->numNodes = getnodes(z->left)+getnodes(z->right)+1;
	x->numNodes = getnodes(x->left)+getnodes(x->right)+1;
	y->numNodes = getnodes(y->left)+getnodes(y->right)+1;
	
	return y;
}
struct node* l_zigzig(struct node* z)
{
	struct node *y = z->left;
	struct node *x = y->left;
	struct node *T2 = y->right;
	y->right = z;
	y->left = x;
	z->left = T2;

	z->height = max(height(z->left),height(z->right))+1;
	x->height = max(height(x->left),height(x->right))+1;
	y->height = max(height(y->left),height(y->right))+1;

	z->numNodes = getnodes(z->left)+getnodes(z->right)+1;
	x->numNodes = getnodes(x->left)+getnodes(x->right)+1;
	y->numNodes = getnodes(y->left)+getnodes(y->right)+1;
	
	return y;
}
struct node* insert(struct node* node,int key)
{
	if(node == NULL)
		return newNode(key);
	if(key < node->key)
		node->left = insert(node->left,key);
	else if(key > node->key)
		node->right = insert(node->right,key);
	else
		return node;
	
	node->height = max(height(node->left),height(node->right))+1;
	int balance = 0;
	balance = abs(getBalance(node));
	node->numNodes = getnodes(node->left)+getnodes(node->right)+1;

	if(balance > 1)
	{
		if(node->right)
		{	
			if(key > (node->key) && key < ((node->right)->key))
				return r_zigzag(node);
			if(key > (node->key) && key > ((node->right)->key))
				return r_zigzig(node);
		}
		if(node->left)
		{
			if(key < (node->key) && key > ((node->left)->key))
				return l_zigzag(node);
			if(key < (node->key) && key < ((node->left)->key))
				return l_zigzig(node);
		}

	}
	return node;

}

struct node* minV(struct node* root)
{
	while(root->left)
		root = root->left;
	return root;
}

struct node* delete(struct node* node,int key)
{
	if(node == NULL)
		return node;
	if(key < node->key)
		node->left = delete(node->left,key);
	else if(key > node->key)
		node->right = delete(node->right,key);
	else
	{
		if(node->left == NULL || node->right==NULL)
		{
			struct node *temp = node->left? node->left : node->right;
			if(temp == NULL)
				node = NULL;
			else
				*node = *temp;
		}
		else
		{
			struct node *temp = minV(node->right);
			node->key = temp->key;
			node->right = delete(node->right,temp->key);
		}
	}

	if(node == NULL)
		return node;

	node->height = max(height(node->left),height(node->right))+1;
	int balance = 0;
	balance = abs(getBalance(node));
	node->numNodes = getnodes(node->left)+getnodes(node->right)+1;

	if(balance > 1)
	{
		if(node->right)
		{	
			if(key > (node->key) && key < ((node->right)->key))
				return r_zigzag(node);
			if(key > (node->key) && key > ((node->right)->key))
				return r_zigzig(node);
		}
		if(node->left)
		{
			if(key < (node->key) && key > ((node->left)->key))
				return l_zigzag(node);
			if(key < (node->key) && key < ((node->left)->key))
				return l_zigzig(node);
		}

	}
	return node;
}

void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d %d %d\n", root->key,root->height,root->numNodes);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
	
	struct node *root = NULL;
 
	root = insert(root, 10);
  	root = insert(root, 20);
  	root = insert(root, 30);
  	root = insert(root, 40);
  	root = insert(root, 50);
  	root = insert(root, 25);
 	root = delete(root, 30);
  
  	preOrder(root);
  	
 
  	return 0;

}