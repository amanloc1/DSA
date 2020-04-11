
#include <bits/stdc++.h>
using namespace std;

struct Node{
    int i,data,parent;

};



int findSet(int i, vector <int>& parent){
    if(parent[i] != i)
        parent[i] = findSet(parent[i],parent); //using path compression
    return parent[i];
}

void unionSet(int i, int j, vector <int> &parent)
{
    int a = findSet(i,parent);
    int b = findSet(j, parent);

    parent[b] = a;
}

vector <int> makeSet()







        
int main(){




    return 0;
}