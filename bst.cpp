#include <bits/stdc++.h>
using namespace std;
struct node
{
	int key;
	node *left, *right, *p;
	node(int x):key(x),left(NULL),right(NULL),p(NULL){}
};

node * new_node(int k){
	node *x = new node(k);
	return x;
}


class bst
{
	public:
	node *root = NULL;

	void InorderTreeWalk(node *);
	node *TreeSearch(node *, int);
	node *IterativeTreeSearch(node *, int);
	node *TreeMinimum(node *);
	node *IterativeTreeMinimum(node *);
	node *TreeMaximum(node *);
	node *IterativeTreeMaximum(node *);
	node *TreeSuccessor(node *);
	node *TreePredecessor(node *);
	
	void TreeInsert(node *);
	void Transplant(node *, node *);
	void TreeDelete(node *);
};




void bst :: InorderTreeWalk(node *x){
	if( x != NULL){
		InorderTreeWalk(x->left);
		cout<<x->key <<" ";
		InorderTreeWalk(x->right);
	}
	


}

node * bst :: TreeMinimum(node *x){
	if( x->left == NULL)
		return x;
	return TreeMinimum(x->left);	
}

node * bst :: TreeMaximum(node *x){
	if( x->right == NULL)
		return x;
	return TreeMaximum(x->right);	
}

node * bst :: IterativeTreeMinimum(node *x){
	while ( x->left != NULL)
		x = x->left;
	return x;
}
/* iteratively finds tree maximim */
node * bst :: IterativeTreeMaximum(node *x){
	while ( x->right != NULL)
		x = x->right;
	return x;
}
/* recursively finds key  */
node * bst::TreeSearch(node *x, int key){
	//base case
	cout<<x->key<<endl;
	if( x == NULL || x->key == key)
		return x;
	//recursion
	if(x->key > key)   // >= in right  : < in left
		return TreeSearch(x->left, key);
	else return TreeSearch(x->right, key);


}
/* iteratively search node having key : key */
node *IterativeTreeSearch(node *x, int key){

	while ( x != NULL && x->key != key){ //until x becomes NULL or x has the key
		if(x-> key > key )
			x = x->left;
		else x = x-> right;
	}
	return x; //x can be NULL or containing key
}
/* finds successor of node x in tree */
node * bst :: TreeSuccessor(node *x){
	if ( x-> right != NULL )             // if right node is non epmty then minimum to right side is successor
		return TreeMinimum(x->right);	// because all node in right side is greater than x
	//It cannot return NULL				// but we need the mimimum among them
	//if no right
	//find successor in parent 
	//x should be in left subtree of that parent then that will be greater than x
	node * y = x->p;
	while( y-> left != x && y != NULL){ // x is in left or parent becomes NULL
		x = y;
		y = y->p;
	}
	return y; //it can return NULL 

}
/* finds predecessor of node x */
node * bst :: TreePredecessor(node *x){
	if ( x-> left != NULL )             // if left node is non epmty then maximum to left side is successor
		return TreeMaximum(x->left);	// because all node in left side is smaller than x
	//It cannot return NULL				// but we need the maximum among them
	//if no left
	//find predecessor in parent 
	//x should be in right subtree of that parent then that will be smaller than x
	node * y = x->p;
	while( y-> right != x && y != NULL){ // x is in right or parent becomes NULL
		x = y;
		y = y->p;
	}
	return y; //it can return NULL 

}
/* insert node y in tree if tree is empty y is root */
void bst :: TreeInsert(node *y){
	node *x = root;
	node *z = NULL;

	while( x != NULL ){
		z = x;
		if(x->key > y->key)
			x = x->left;
		else x = x->right;
	}
	y->p = z;
	if(z == NULL)
		root = y;
	else {
		if(z->key <= y-> key)
			z->right = y;
		else z->left = y;
	}
}
/* replace subtree rooted at x by subtree rooted at y */
void bst ::  Transplant(node *x, node *y){ 
	// if x is root
	if(x->p == NULL )
	{
		root = y;
		return;
	}
	//if x is left then y should also be left and same for right
	if ( x->p->left == x)
		x->p->left = y;
	else x->p->right = y;
	//if y is NULL no need to assign its parent
	if(y != NULL)
		y->p = x->p;	
}
/* Delete a node from tree */
void bst :: TreeDelete(node *x){
	if(x != NULL){ //if x is NULL no need to anything

		if(x-> left == NULL){  // left is NULL and right is not NULL or may be too
			Transplant(x,x->right);
			return;
		}
		else if(x->right == NULL){ //right is NULL and left may or may not be NULL
			Transplant(x,x->left);
			return;
		}
		//The above two cases also handles the case if both of them might be NULL


		//node x will be replaced by its successor
		node *successor_of_x = TreeMinimum(x->right);
		//there are two cases
		// 1: successor is right of x
		// 2: successor is  not right of x
		if(successor_of_x->p != x)
		{
			//These only holds for second case
			Transplant(successor_of_x,successor_of_x->right); 	//because it may have right subtree 
			successor_of_x->right = x->right;					//so that subtree should be attached to its parent
			successor_of_x->right->p = successor_of_x;
		}
		//the below two lines hold for both the cases
		Transplant(x,successor_of_x);
		successor_of_x->left = x->left;
		successor_of_x->left->p = successor_of_x;
	
	}
}



int main(){
	bst T;
	
	node x(10);
	T.TreeInsert(&x);
	T.TreeInsert(new_node(15));
	T.TreeInsert(new_node(17));
	T.TreeInsert(new_node(12));
	T.TreeInsert(new_node(100));
	T.TreeInsert(new_node(6));
	T.TreeInsert(new_node(7));
	T.TreeInsert(new_node(4));
	node *y = T.TreeSearch(T.root,100);
	T.TreeDelete(y);
	T.InorderTreeWalk(T.root);
	cout<<endl;
	node *y1 = T.TreeSearch(T.root,15);
	T.TreeDelete(y1);
	T.InorderTreeWalk(T.root);
	cout<<endl;
	node *y2 = T.TreeSearch(T.root,7);
	T.TreeDelete(y2);
	T.InorderTreeWalk(T.root);
	cout<<endl;



    
    return 0;


}

