#include <bits/stdc++.h>
using namespace std;
struct node
{
	int key;
    int h = 0;
	node *left, *right, *p;

	node():left(NULL),right(NULL),p(NULL){}
	node(int x):key(x),left(NULL),right(NULL),p(NULL){}
};

node * new_node(int k){
	node *x = new node(k);
	return x;
}


/* left minus right difference for node x*/
int balance ( node *x){
	if(x == NULL ) return 0;
 	return height(x->left) - height(x->right);
}

int height (node* x){
	if(x == NULL)
		return 0;
	else return x->h;
}

/* AVL Tree */
class AVL
{
	public:
	node *root = NULL;

	void InorderTreeWalk(node *);
	node *TreeSearch(node *, int);
	node *TreeMinimum(node *);
	node *TreeMaximum(node *);
	node *TreeSuccessor(node *);
	node *TreePredecessor(node *);
    node * left_rotate(node *);
    node * right_rotate(node *);
	
	node * TreeInsert(node *, int );
	void   Transplant(node *, node *);
	node * TreeDelete(node *,int k);
};
/* searching key from node x  */
node * AVL::TreeSearch(node *x, int key){
	//base case
	cout<<x->key<<endl;
	if( x == NULL || x->key == key)
		return x;
	//recursion
	if(x->key > key)   // >= in right  : < in left
		return TreeSearch(x->left, key);
	else return TreeSearch(x->right, key);


}

node * AVL :: TreeMinimum(node *x){
	if( x->left == NULL)
		return x;
	return TreeMinimum(x->left);	
}

node * AVL :: TreeMaximum(node *x){
	if( x->right == NULL)
		return x;
	return TreeMaximum(x->right);	
}

/* finds successor of node x in tree */
node * AVL :: TreeSuccessor(node *x){
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
node * AVL :: TreePredecessor(node *x){
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
// /* insert node y in tree if tree is empty y is root */
// void AVL :: TreeInsert(node *y){
// 	node *x = root;
// 	node *z = NULL;

// 	while( x != NULL ){
// 		z = x;
// 		if(x->key > y->key)
// 			x = x->left;
// 		else x = x->right;
// 	}
// 	y->p = z;
// 	if(z == NULL)
// 		root = y;
// 	else {
// 		if(z->key <= y-> key)
// 			z->right = y;
// 		else z->left = y;
// 	}
    
// }

/* 
        |                                  |
		x           					   y
	   / \				<-				  / \
	   y  T1        left rotate			 T2  x
	  / \         	      ->		    / \
     T2  T3        right rotate       T3  T1   
	 
	 return y // new root after right rotation
	 return x // new root after left rotation
	 Height of T1,T2,T3 remains the same
	x and y height changes accordingly 
	 
	    */
	
/* rotates right about node x */
node * AVL :: left_rotate(node *x){

	//left rotating 
    node *y = x->right;
    Transplant(x,y);
    x->right = y->left;
    if(y->left != NULL)
        y->left->p = y;
    y->left = x;
    x->p = y;

	//balancing the height
	y->h = 1 + max ( y->left->h , y->right->h);
	x->h = 1 + max ( y->h , x->right->h);

	return y;
}

/* rotates right about node x */
node * AVL :: right_rotate(node *x){

	//right rotate
    node *y = x->left;
    Transplant(x,y);
    x->left = y->right;
    if(y->right != NULL)
        y->right->p = y;
    y->right = x;
    x->p = y;

	//balancing the height
	x->h = 1 + max ( x->left->h , x->right->h);
	y->h = 1 + max ( y->left->h , x->h);

	return y;

}

void AVL ::  Transplant(node *x, node *y){ 
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

// Recursive function to insert a key 
// in the subtree rooted with node and 
// returns the new root of the subtree.  
/* AVL Tree Insertion */
node * AVL :: TreeInsert(node *y, int key){

	//first insert key 

	if(y == NULL)
		return new_node(key);
	else if(y->key > key)
		//becuase Treeinsert returns new root of that subtree
		//and when subtree rearranges we have to change the left or right son too
		y->left = TreeInsert(y->left , key); 
	else if(y->key < key) 
		y->right = TreeInsert(y->right , key); 
	else if(y->key == key )
		return y; 	//if node is already present no need to insert
					//assuming no duplicate node in AVL other may become O(n) for some operations

	//second balance the height of y
	y->h = 1 + max(height(y->left),height(y->right));

	//find left-right height difference
	int height_difference = balance(y);

	//check whether we need to rotate or not and return the new root

	//left-left case
	if(key < y->left->key &&  height_difference > 1)
		return right_rotate(y);
	//right-right case
	if(key > y->right->key &&  height_difference < -1)
		return left_rotate(y);
	//left-right case
	if(key > y->left->key &&  height_difference > 1)
	{
		left_rotate(y->left);
		return right_rotate(y);

	}
	// right-left case
	if(key < y->right->key &&  height_difference < -1)
	{
		right_rotate(y->right);
		return left_rotate(y);

	}

	// if no need to rotate return y
	return y;
}

/* deletes a node in AVL with key = k */
node * TreeDelete(node *x, int k){

	//if root is NULL no need to delete a node 
	if( x == NULL )
		return x;
	
	else if( x->key > k)
		x->left = TreeDelete(x->left , k);

	else if( x->key < k)
		x->right = TreeDelete(x->right , k);

	else{
		//one child or no child case
		if( x->left == NULL || x->right == NULL){
			node *y = new node();

			y = x->left ? x->left : x->right ;
			//no chld case 
			if( y == NULL){
				//assign x to y and delete that
				y = x ;
				//if no child x becomes NULL after deleting it
				x = NULL;				
			}
			//      x 
			//     / \
			//   NULL y
			//         
			//if one child case
			//copy contents of that child to 
			else
				*x = *y;
				









		}




	}



}





