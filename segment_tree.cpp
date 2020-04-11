#include <bits/stdc++.h>
using namespace std;
#define left(i) i<<1
#define right(i) i<<1|1
#define parent(i) i>>1


            //                                          1:0-16
            //                      2:0-7                                     3:8-15
            //           4:0-3             5:4-7                   6:8-11                7:12-15
            //      8:0-1    9:2-3    10:4-5    11:6-7        12:8-9    13:10-11    14:12-13   15:14-15
            //   16:0 17:1 18:2 19:3 20:4 21:5 22:6 23:7    24:8 25:9 26:10 27:11 28:12 29:13 30:14 31:15   


//left(i) = 2*i     i << 1
//right(i) = 2*i+1  i << 1 ^ 1 or i << 1 | 1

//parent(i) = i/2 floor i.e i >> 1


void print_array(int A[],int N){
    for(int i = 0 ; i < N ; i++)
        cout<< A[i];
    cout<<endl;
}

int main(){

    int N;
    cin >> N;
    int A[N];

    for( int i = 0 ; i < N ; i++){
        cin >> A[i];
    }
    int segment_tree[2*N]; //1-2N-1

    for(int i = N ; i < 2*N ; i++){
        segment_tree[i] = A[i-N];
    }

    for(int i = N-1 ; i >0 ; i--){
        segment_tree[i] = segment_tree[left(i)] + segment_tree[right(i)];
    }

    print_array(segment_tree,2*N);




    










    return 0;
}

// geeksforgeeks implementation
#include <bits/stdc++.h> 
using namespace std; 

// limit for array size 
const int N = 100000; 

int n; // array size 

// Max size of tree 
int tree[2 * N]; 

// function to build the tree 
void build( int arr[]) 
{ 
	// insert leaf nodes in tree 
	for (int i=0; i<n; i++)	 
		tree[n+i] = arr[i]; 
	
	// build the tree by calculating parents 
	for (int i = n - 1; i > 0; --i)	 
		tree[i] = tree[i<<1] + tree[i<<1 | 1];	 
} 

// function to update a tree node 
void updateTreeNode(int p, int value) 
{ 
	// set value at position p 
	tree[p+n] = value; 
	p = p+n; 
	
	// move upward and update parents 
	for (int i=p; i > 1; i >>= 1) 
		tree[i>>1] = tree[i] + tree[i^1]; 
} 

// function to get sum on interval [l, r) 
int query(int l, int r) 
{ 
	int res = 0; 
	
	// loop to find the sum in the range 
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) 
	{ 
		if (l&1) 
			res += tree[l++]; 
	
		if (r&1) 
			res += tree[--r]; 
	} 
	
	return res; 
} 

// driver program to test the above function 
int main() 
{ 
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; 

	// n is global 
	n = sizeof(a)/sizeof(a[0]); 
	
	// build tree 
	build(a); 
	
	// print the sum in range(1,2) index-based 
	cout << query(1, 3)<<endl; 
	
	// modify element at 2nd index 
	updateTreeNode(2, 1); 
	
	// print the sum in range(1,2) index-based 
	cout << query(1, 3)<<endl; 

	return 0; 
} 
