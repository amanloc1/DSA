
#include <bits/stdc++.h>
using namespace std;


void i_sort(vector <int> &A ){

    int n  = A.size();
    int j; 
    int key;
    for(int i = 1; i < n ; i++)
    {
        j = i - 1;
        key = A[i];

        while( j >= 0 && key < A[j]  )
        {
            A[j+1] = A[j];
            j--;

        }
        A[j+1] = key ;
                

    }



}

void printv(vector <int> A){
    for(int i:A){
        cout<<i<<" ";
    }
    cout<<endl;
}



void Merge(vector <int>&A, int p, int q, int r ){
    int n1 = q-p+1;  //left length
    int n2 = r-q;  //right length

    int *L = new int [n1+1]; 
    int *R = new int [n2+1]; 

    for (int i = 0 ; i < n1 ; i++){
        L[i] = A[i + p];
    }
    L[n1] = INT_MAX;

    for (int i = 0 ; i < n2 ; i++){
        R[i] = A[i + q + 1];
    }
    R[n2] = INT_MAX;
    

    int i = 0;
    int j =0;

    for(int k = p ; k <= r ; k++){

        if(L[i] >= R[j])
        {
            A[k] = R[j];
            j++;
           

        } 
        else {
            A[k] = L[i] ; 
            i++;
        }
        

    } 



}



void merge_sort(vector<int> &A, int p, int q ){
    if ( p < q){
        int r = p/2 + q/2;
        merge_sort(A,p,r);
        merge_sort(A,r+1,q);
        Merge(A,p,r,q);
    }

}


        
int main(){
    vector <int> A = {1,7,5,9,4,2,10,12};
   merge_sort(A,0,7);
    printv(A);




    return 0;
}