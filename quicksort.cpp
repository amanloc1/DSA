
#include <bits/stdc++.h>
using namespace std;


int partition(vector <int> &A, int p , int r){
    int x = A[r];
    int y;
    y = p-1;

    for(int i = p; i < r ; i++){
        if(A[i] <= x){
            y++;
            swap(A[y],A[i]);
        }
    }
    swap(A[r],A[y+1]);
    return y+1;

}
        
int main(){
    



    return 0;
}