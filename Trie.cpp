#include <bits/stdc++.h>
using namespace std;


//Note Alphabet Size is 26
//Implemented only for lowercases

/*
Notes : 

	Trie is an efficient information reTrieval data structure
	used to store strings
	one trie node store 26 pointers to trie  node and an end of word
	end of word tells whether word is present or not
	if word is present then it must point to a node containing true as end of word
	when no words in trie , root has only true and all pointers pointing to NULL

following trie contains words : c, car, cen


				|  C  |_
				|false| \
						 \	
					 _|  a  |
					/ |	 e  | _
				   /  |true|  \
				  /      	    \
			     /       	     \
			|  r | _		 |  n  | _
			|true|	\		 |false|  \
					/				   |true|
			   	   /
			   |true|

*/
/*TrieNode Containing pointers to children and end of word*/
struct TrieNode{

	//create 26 pointer to a TrieNode for each children
	TrieNode* children[26];
	//end of word
	bool end;
};

/*create an empty TrieNode*/
TrieNode* newTrieNode(void){
	//assign memory
	TrieNode* NewNode = new TrieNode;
	//end is false initially
	NewNode->end = false;
	//point all its children to NULL initially
	for(int i = 0 ; i  < 26 ; i++){
		NewNode->children[i] = NULL;
	}

	return NewNode;

}


/*Trie Class*/
class Trie{
	//root node
	TrieNode* root;
	//check where all children pointing to NULL and end of word is false
	bool isEmpty(TrieNode *currentTrieNode);
	//helps to delete the current Node recursively check if Node becomes empty then delete
	void deleteTrieHelper(string s, int depth , TrieNode* currentTrieNode);
public:
	//constructor
	Trie();
	//insert a string
	void insertTrie(string s);
	//search a string
	bool searchTrie(string s);
	//delete a string
	void deleteTrie(string s);

};

/*Constructor*/
Trie :: Trie(){
	this->root = newTrieNode();
}

//NOTE : 
//Q) When not to insert node
//ans-> if node is already present for some other string
//Q)when to create a node and insert the node ? 
//ans : when node is not present

/*Insert a string in Trie*/
void Trie :: insertTrie(string s){
	//node pointing to current TrieNode 
	TrieNode* currentTrieNode = this->root;

	for(int i = 0 ; i < s.length() ; i++){
		//index is calculated by character
		int currentIndex = s[i] - 'a' ;
		//if that child is pointiing to NULL
		//create a new child for that
		if(currentTrieNode->children[currentIndex] == NULL)
			currentTrieNode->children[currentIndex] = newTrieNode();
		//on next loop we will consider on child
		//so make child node to current node for next iteration
		currentTrieNode = currentTrieNode->children[currentIndex];
	}
	//current node is the last node 
	//so mark end = true to tell that string is contained in Trie
	currentTrieNode->end = true;
}



// NOTE : 
// Q) when does Trie not contain the string ?
// ans->
// case I : nodes are not present  
// case II : all nodes are present but child of last node has not end = true

/*searching a word in Trie*/
bool Trie :: searchTrie(string s){
	//starting searching from root
	TrieNode* currentTrieNode = this->root;

	// CASE I 
	
	for(int i = 0 ; i < s.length() ; i++){
		//index is calculated by character
		int currentIndex = s[i] - 'a' ;
		//current child found using index
		TrieNode* currentChild =  currentTrieNode->children[currentIndex];
		//if child is pointing to NULL means word is not present
		//otherwise it must have a child whose end = True
		if(currentChild == NULL)
			return false;
		//on next loop we will consider on child
		//so make child node to current node for next iteration
		currentTrieNode = currentChild;
	}

	// CASE II

	//if node pointed by last letter has end false that means
	//this node was created for other word
	if(currentTrieNode->end == false)
		return false;
	//otherwise true
	return true;
}

/*Check if node empty and end = false*/
bool Trie::isEmpty(TrieNode *currentTrieNode){
	//node end must be false for empty node
	if(currentTrieNode->end == true)
		return false;
	else 
		//check all if children is pointing to NULL
		for(int i = 0 ; i < 26 ; i++)
			// if not pointing to NULL then it is not empty
			if(currentTrieNode->children[i] != NULL)
				return false;
	//if passed all tests then it is empty
	return true;
}

/*

NOTES : 
Q)When to delete a Node ? 
ans->
CASE I : when string last index = depth and end = true for child 
		 then delete child and then parent points to NULL after child gets deleted
CASE II : while recursion when Node becomes empty delete that redundant node too
 */	



/*Helps to delete strings*/
void Trie :: deleteTrieHelper(string s, int depth, TrieNode* currentTrieNode){
	int string_length = s.length();

	//child at depth  
	//root has depth = 0
	//current Node is parent of node to be deleted 

	TrieNode* currentChild = currentTrieNode->children[s[depth] - 'a'];

	// CASE I
	if(depth == (string_length-1) ){
		//if child is NULL or its end = false then no need to delete
		if(currentChild == NULL || currentChild->end == false)
			return ;
		//when this is leaf  end = true so make it false to get deleted
		else 
			currentChild->end = false;
	}
		//if depth != string length -1 then check for next node in depth+1 to be deleted
	else
		deleteTrieHelper(s,depth+1,currentChild);
		

	//we always keep on checking at each node if it needs to be deleted due to 2 reasons
	//1)when it is leaf node and string found
	//2)recursing made a node empty
	if(isEmpty(currentChild)){
		currentTrieNode->children[s[depth]] = NULL;
		delete currentChild;
	}
}


void Trie :: deleteTrie(string s){
	deleteTrieHelper(s,0,this->root);
}


int main(int argc, char const *argv[])
{
	Trie T;
	T.insertTrie("ramesh");
	T.insertTrie("amesh");
	cout<<T.searchTrie("ramesh")<<endl;
	cout<<T.searchTrie("amesh")<<endl;
	T.deleteTrie("ramesh");
	T.deleteTrie("amesh");
	cout<<T.searchTrie("amesh")<<endl;
	cout<<T.searchTrie("ramesh")<<endl;

	return 0;
}