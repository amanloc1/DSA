#include <bits/stdc++.h>
using namespace std;

        //     i
        //    / \
        // 2i+1  2i+2

        //     0
        //    / \
        //   1   2



/*find left node index*/
int left(int parent){
    return parent*2+1;
}
/*find right node index*/
int right(int parent){
    return parent*2 + 2;
}
/*find parent node index*/
int parent(int child){
    return (child-1)/2;    
}
/*find mid intex*/
int mid(int start, int end){
    return start+(end-start)/2 ;  
}
/*print a vector*/
void print_vector(std::vector<int> v){
    for(int i : v)
        cout<<i<<" ";
    cout<<endl;
}



/*
st_index    : current node index dealing with
st_start    : segment tree starting index (arg in helper function)
st_end      : segment tree last index      (arg in helper function)    
u_index     : index to be updated and subsequnet sum (arg in helper function)
start       : staring index (arg in main funciton {sum})
end         : ending index (arg in main funciton {sum})
v           : vector used for making segement tree (arg in constructor)
v_arr       : array vector in segment tree (attribute in st class)
st          : vector in segment tree used for intialization (attribute in st class)
middle      : mid of st_start and st_end
st_last     : last index of v_arr (attribute in st class)
sum_start   : from where to sum used for single node to check (used in helper function)
sum_end     : to where to sum used for single node to check (used in helper function)
index       : index to be updated (arg in main function {update})
key         : key to be updated (arg in main function {update})
*/

/*SEGMENT TREE CLASS*/
class segment_tree
{
private:   
    std::vector<int> st;        //segment tree array
    std::vector<int> v_arr;     //vector used for segemnt tree initialization
    int st_last = 0;            //last index of segement tree

    /*helper function for constructor returns sum from start to end*/
    int st_construct(vector<int> v, int start, int end, int st_index);
    /*helper function for update returns sum from sum_start to sum_end*/
    int calculate_sum(int st_start, int st_end, int sum_start, int sum_end, int st_index);
    /*helper function for update */
    void calculate_update(int st_start, int st_end, int u_index,int st_index,int diff );
public:
    /*main constructor*/
    segment_tree(vector<int> v);
    /*sum function returns sum from start to end*/
    int sum(int start, int end);
    /*update fucntion updates index to key and in range too*/
    void update(int index, int key);
    
};


/*creating segemnt tree with vector v*/
segment_tree :: segment_tree(std::vector<int> v){
    //update array in st
    this->v_arr = v;
    int size_of_given_vector = v.size();
    //last index = size-1
    st_last = size_of_given_vector - 1;
    //calcute height H and max number of nodes in that to skip overflow error
    int power_of_2 = ceil(log2(size_of_given_vector)); 
    int size_of_st = 2 * pow(2, power_of_2) - 1;
    st.resize(size_of_st,0);
    st_construct(v,0,st_last,0);
}

/*  constructing segment tree
    returns value at st_index
*/
int segment_tree ::  st_construct(vector<int> v, int start, int end, int st_index){
    //leaf node
    if(start == end){
        st[st_index] = v[start];
        return st[st_index];
    }
    //if not leaf then recursively
    int middle = mid(start,end);

    //node value  = left node value + right node value
    st[st_index] = st_construct(v,start, middle,left(st_index)) + 
                   st_construct(v,middle+1, end,right(st_index));
    //return current node value used for recursion                   
    return st[st_index];
}


/*sum function returns sum from start to end*/
int segment_tree ::  sum(int start, int end){
    // return sum from 0 to last index of array
    return calculate_sum(0,st_last,start,end,0);
}

/*helper function for update returns sum from sum_start to sum_end*/
int segment_tree  :: calculate_sum(int st_start, int st_end, int sum_start, int sum_end, int st_index){
    
    int middle = mid(st_start,st_end);

    //node = required sum
    if(st_start == sum_start && st_end == sum_end)
        return st[st_index];
    //if sum range is not in node
    else if(sum_end < st_start || sum_start > st_end)
        return 0;


    //if sum range is in right child node
    else if(middle < sum_start)
        return calculate_sum(middle+1, st_end, sum_start, sum_end, right(st_index));
    //if sum range is in left child node
    
    else if(sum_end <= middle)
        return calculate_sum(st_start, middle, sum_start, sum_end, left(st_index));

    //middle of node  is in between sum range
    else if(middle >= sum_start && sum_end > middle)
        return calculate_sum(middle+1, st_end, middle + 1, sum_end, right(st_index)) +
                calculate_sum(st_start, middle, sum_start, middle, left(st_index));  
    return 0;
}

/*int segment_tree  :: calculate_sum(int st_start, int st_end, int sum_start, int sum_end, int st_index){
    //node = required sum
    if(st_start >= sum_start && st_end <= sum_end)
        return st[st_index];
    //if sum range is not in node
    else if(sum_end < st_start || sum_start > st_end)
        return 0;
    int middle = mid(st_start,st_end);
    return calculate_sum(middle+1, st_end, sum_start, sum_end, right(st_index)) +
                calculate_sum(st_start, middle, sum_start, sum_end, left(st_index));  
}*/


/*Used to update key at index and in range too*/
void segment_tree ::  update(int index, int key){

    //index out of range then return
    if(index < 0 || index > st_last)
    {
        cout<<"error in updating "<<endl;
        return;
    }

    //differnce to be added
    int diff = key - v_arr[index];
    //if no difference simply return
    if(diff == 0)
        return ;

    //update in array 
    v_arr[index] = key;
    //update in segment tree
    calculate_update(0,st_last,index,0,diff);

}


/*update helper function*/
void segment_tree ::  calculate_update(int st_start, int st_end, int u_index, int st_index,int diff){

    //if update index out of range simply return
    if(u_index <  st_start || u_index > st_end)
        return;

    //else add the difference to update
    st[st_index] += diff;

    //if node is leaf no need to recurse further
    if(st_start != st_end)
    {
    calculate_update(st_start,mid(st_start,st_end),u_index,left(st_index),diff);
    calculate_update(mid(st_start,st_end)+1,st_end,u_index,right(st_index),diff);
    }
}




int main(int argc, char const *argv[])
{
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    segment_tree s(v);
    cout<<s.sum(2,5)<<endl;
    s.update(3,10);


    return 0;
}