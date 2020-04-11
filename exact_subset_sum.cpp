#include <bits/stdc++.h> 
using namespace std;
#define check(x) cout<<"value of "<<#x << " is "<<x<<endl;
#define line(x) cout<<"this is line number "<<x<<endl;
#define c(a) cout<<a<<endl;


vector <int> merge_list (vector <int> A, vector <int> B, int x);
void print_vector(vector <int> A);
void remove_greater(vector <int> &A, int target);

int main (){
    
    vector <int> A = {5 , 9 ,14 ,7,8,10,16};
    int n = A.size();
    vector <int> temp = {0};
    int target = 200;
    print_vector(temp);
    for(int i = 0; i < n; i++){
        temp = merge_list(temp,temp,A[i]);
        // print_vector(temp);
        remove_greater(temp,target);
    }
    sort(temp.begin(),temp.end());
    auto it2 = unique(temp.begin(),temp.end());
    temp.resize(distance(temp.begin(),it2));
        print_vector(temp);
    // cout<<*max_element(temp.begin(),temp.end())<<endl;;
    cout<<temp.size()<<endl;
    

   




    return 0;
}


vector <int> merge_list (vector <int> A, vector <int> B, int x){

    vector <int> C;
    for (int &i : B)
        i += x;
    C.insert(C.end(),A.begin(), A.end());
    C.insert(C.end(),B.begin(), B.end());
    
    return C;
}

void print_vector(vector <int> A){
    for(int i : A)
        cout<<i<<" ";
    cout<<endl;
}

void remove_greater(vector <int> &A, int target){

    for(auto it = A.begin() ; it!= A.end() ; it++)
        if((*it) > target)
            {
                A.erase(it);
                it--;   
            }  
            
        
        

}
