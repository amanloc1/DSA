#include<bits/stdc++.h>
using namespace std;


int left(int Parent){
	return Parent*2+1;
}

int right(int Parent){
	return Parent*2+2;
}

int parent(int child){
	return (child-1)/2;
}

/*

left = 2i+1
right = 2i-1
parent = (child-1)/2

				 0
			   /   \
			  1     2
			 / \   / \
			3   4 5   6
*/

/*Heap class*/
class heap
{
public:
	int* arr;       //heap array
	int heap_size;  //heap size
	int array_size; // heap array size
	void max_heapify(int start); 
	void build_maxheap(void); 
	heap(int *Array,int arraySize);
	void heap_sort();
	void print_array();

};


class maxheap : public heap{
public:
	maxheap(int *Array, int arraySize);
}

maxheap :: maxheap(int *Array, int arraySize){
	arr = 
	H->build_maxheap();
}


/*
when to max heapify
when the parent is not greater than both childern
*/

/*Max Heapify*/
void heap :: max_heapify(int start){
	// find left and right index
	int Left = left(start);
	int Right = right(start);
	//let largest is the parent
	int largest = start;
	//check which is largest among parent and children
	if(arr[start] < arr[Left] && Left < heap_size)
		largest = Left;
	if(arr[largest] < arr[Right] && Right < heap_size)
		largest = Right;
	//if parent is not the largest then swap with larger element and 
	//call max heapify on swapped to maintain max heap property
	if(largest != start){
		swap(arr[start],arr[largest]);
		max_heapify(largest);
	}
}

/*
What is max heap?
All child is smaller than parent
 */

/*Build array as max heap*/
void heap :: build_maxheap(void){
	for(int i = (heap_size-1)/2; i >= 0 ; i-- )
		max_heapify(i);
}

/*Heap sort*/
void heap :: heap_sort(){
	heap_size = array_size;
	for(int i = heap_size-1; i > 0; i--){
		build_maxheap();
		swap(arr[i], arr[0]);		
		heap_size--;
	}
	//restore heap size
	heap_size = array_size;
}


/*heap constructor*/
heap::heap(int *Array,int arraySize){
	array_size = arraySize;
	heap_size = arraySize;
	arr = Array;
}




void heap :: print_array(){
	cout<<"heap elements : ";
	for(int i = 0 ; i < array_size ; i++)
		cout<<arr[i]<<" ";
	cout<<endl;

}


int main(int argc, char const *argv[])
{
	int A[] = {7,6,5,4,3,2,1};
	heap H(A,7);
	H.print_array();
	H.heap_sort();
	H.print_array();
	/* code */
	return 0;
}
