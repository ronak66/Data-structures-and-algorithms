#include<iostream>
using namespace std;

class RBT{
		enum node_col{
			black,
			red
		};

		struct node{
			int data;
			node_col colour;
			node *left, *right, *parent;

			node(int d, node *p = nil, node_col c = red, node *l = nil, node *r = nil){
				data = d;
				parent = p;
				colour = c;
				left = l;
				right = r;
			}
		} *root;

		static node *nil;

		node* sibling(node *x){
			if(x->parent == nil) return nil;
			return ((x->parent->left == x) ? x->parent->right : x->parent->left);
		}

		bool is_left_child(node *x){
			return (x->parent->left == x);
		}

		void left_rotate(node *x){
			node *newParent = x->right;
			node *moveSubTree = newParent->left;

			newParent->parent = x->parent;
			if(x->parent == nil) root = newParent;
			else if(is_left_child(x)) x->parent->left = newParent;
			else x->parent->right = newParent;

			newParent->left = x;
			x->parent = newParent;

			x->right = moveSubTree;
			if(moveSubTree != nil) moveSubTree->parent = x;
		}

		void right_rotate(node *x){
			node *newParent = x->left;
			node *moveSubTree = newParent->right;

			newParent->parent = x->parent;
			if(x->parent == nil) root = newParent;
			else if(is_left_child(x)) x->parent->left = newParent;
			else x->parent->right = newParent;

			newParent->right = x;
			x->parent = newParent;

			x->left = moveSubTree;
			if(moveSubTree != nil) moveSubTree->parent = x;
		}

		void pretty_print(node *x, int indent);
		void inorder_traversal(node *x);
		RBT::node* inorder_predecessor(node *x);
		void swap_colours(node *x, node *y);

	public:

		RBT(node *x = nil){
			root = x;
			root->colour = black;
		}

		bool insert(int k);
		bool delete_node(int k);
		bool search(int k);

		void pretty_print(){
			pretty_print(root, 0);
		}

		void inorder_traversal(){
			inorder_traversal(root);
		}
};
RBT::node *RBT::nil = new RBT::node(0, NULL, black, NULL, NULL);

bool RBT::insert(int k){
	//Empty tree
	if(root == nil){
		root = new node(k, nil, black);
		//Overflow
		if(!root) return false;
		return true;
	}

	node *x = root, *p = NULL;

	while(x != nil){
		p = x;

		if(k > x->data) x = x->right;
		else if(k < x->data) x = x->left;
		//Duplicate key
		else return false;
	}

	x = ((k > p->data) ? p->right : p->left) = new node(k, p);
	//Overflow
	if(!x) return false;

	node *uncle = NULL;

	//Tree has to be fixed
	while(p->colour == red){
		uncle = sibling(p);

		//Uncle is red: Recolour
		if(uncle->colour == red){
			uncle->colour = p->colour = black;
			p->parent->colour = red;
			x = p->parent;
			p = x->parent;
		}

		//Rotations
		else{
			bool posx = is_left_child(x), posp = is_left_child(p);

			//zig-zag: rotation of parent (p)
			if(posx != posp){
				(posx) ? right_rotate(p) : left_rotate(p);

				//swap p and x to ensure p is still parent of x
				node *temp = p;
				p = x;
				x = temp;
			}

			//swap colour of parent and grandparent
			swap_colours(p, p->parent);

			//zig-zag: rotation of grand-parent (p->parent)
			//zig-zig rotation
			(posp) ? right_rotate(p->parent): left_rotate(p->parent);
		}
	}

	root->colour = black;
	return true;
}

void RBT::swap_colours(node *x, node *y){
	node_col temp = x->colour;
	x->colour = y->colour;
	y->colour = temp;
}

bool RBT::search(int k){
	node *temp = root;

	while(temp != nil){
		if(k > temp->data) temp = temp->right;
		else if(k < temp->data) temp = temp->left;
		else return true;
	}

	return false;
}

RBT::node* RBT::inorder_predecessor(node *x){
	x = x->left;

	while(x->right != nil){
		x = x->right;
	}

	return x;
}

void RBT::inorder_traversal(node *x){
	if(x == nil){
		return;
	}
	inorder_traversal(x->left);
	cout<<x->data<<" ";
	inorder_traversal(x->right);
}

void RBT::pretty_print(node *x, int indent){
	if(x == nil){
		return;
	}
	for(int i = 0; i < indent; ++i){
		cout<<"\t";
	}
	cout<<x->data<<","<<((x->colour == red)? "r" : ((x->colour == black) ? "b" : "?"))<<endl;
	pretty_print(x->left, indent+1);
	pretty_print(x->right, indent+1);
}

bool RBT::delete_node(int k){
	//Underflow
	if(root == nil) return false;

	node *m = root;
	while(m != nil){
		if(k > m->data) m = m->right;
		else if(k < m->data) m = m->left;
		//Delete node
		else{
			//Node has 2 children
			if(m->left != nil && m->right != nil){
	            node *temp = inorder_predecessor(m);
	            m->data = temp->data;
				m = temp;
		    }

			//Try to assign non null child to c
			node *c = (m->left != nil) ? m->left : m->right;
			c->parent = m->parent;

			((is_left_child(m)) ? (m->parent->left) : (m->parent->right)) =  c;
			node_col parentCol = m->colour;

			delete m;

			//Root being deleted
			if(c->parent == nil){
				root = c;
				c->colour = black;
				return true;
			}

			//Case 1: If parent or child is red
			if(c->colour == red || parentCol == red){
				c->colour = black;
				return true;
			}

			//Double black
			while(c->colour == black && c != root){
				node *s = sibling(c);

				if(s->colour == black){
					//Case 2: Black sibling has red child
					if(s->left->colour == red || s->right->colour == red){
						bool  poss = is_left_child(s);
						node *r = NULL;

						//Assigning r to red coloured child. In case both are red assign in a way that results in zig-zig rotation.
						if(poss) r = ((s->left->colour == red) ? s->left : s->right);
						else r = ((s->right->colour == red) ? s->right : s->left);

						bool posr = is_left_child(r);

						if(posr != poss){
							(posr) ? right_rotate(s) : left_rotate(s);

							swap_colours(s, s->parent);

							//swap s and r to maintain relation
							node *temp = s;
							s = r;
							r = temp;
						}
						r -> colour = black;
						swap_colours(s->parent, s);


						(poss) ? right_rotate(s->parent) : left_rotate(s->parent);

						//Tree fixed
						break;
					}

					//Case 3: Sibling and its children are black
					else{
						s->colour = red;
						c = s->parent;

						if(c->colour == red){
							c->colour = black;
							//Tree fixed
							break;
						}
						else continue;
					}
				}

				//Case 4: Red sibling
				else{
					s->parent->colour = red;
					s->colour = black;

					(is_left_child(s)) ? right_rotate(s->parent) : left_rotate(s->parent);
				}
			}

			root->colour = black;
			return true;
		}
	}
	return false;
}

int main(){
	RBT t;
	int n, k;
	while(true){
		cout<<"1 - Insert \n2 - Delete \n3 - Search \n4 - In-order traversal \n5 - Exit \nChoice: ";
		cin>>n;
		cout<<endl;

		switch(n){
			case 1:
				cout<<"Number to insert: ";
				cin>>k;
				if(t.insert(k)) cout<<"Insertion successful!\n";
				else cout<<"Insertion unsuccessful!\n";
				break;

			case 2:
				cout<<"Number to delete: ";
				cin>>k;
				if(t.delete_node(k)) cout<<"Deletion successful!\n";
				else cout<<"Deletion unsuccessful!\n";
				break;

			case 3:
				cout<<"Number to search: ";
				cin>>k;
				if(t.search(k)) cout<<"Found number!\n";
				else cout<<"Number not present in tree!\n";
				break;

			case 4:
				t.inorder_traversal();
				cout<<endl;
				break;

			case 5:
				exit(0);

			default:
				cout<<"Invalid choice!\n";
		}
		cout<<"\nTree:\n";
		t.pretty_print();
		cout<<endl<<endl;
	}

	return 0;
}
