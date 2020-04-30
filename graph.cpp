#include <bits/stdc++.h>
#include "header.h"
using namespace std;



//consider 1 to size
/* Graph with vertices 1 to n */
Graph::Graph(int size){
    this->n = size;
    this->adj = new list <int> [size + 1];
}

void Graph::addEdge(int u , int v){
    adj[u].emplace_back(v);
}


void Graph::draw(){
    cout<<"-----------------------------\nGraph is : "<<endl;
    for (int i = 1; i <= n ; i++ ){
        cout << i << " : ";
        for(auto it = adj[i].begin() ; it != adj[i].end() ; it++  ){
            cout << *it << " ";
        }
        cout<<"\n"; 
    }
    cout<<"\n"; 

}

Graph transpose(Graph G){
    Graph g(G.n);
    for(int i = 1 ; i < G.n ; i++){
        for(auto it = G.adj[i].begin() ; it!= G.adj[i].end(); it++){
            g.addEdge(*it, i);
        }
    }
    cout<<"Transpose of Graph is : \n";
    g.draw();
    return g;

}

/* 
@return : topologically sorted vertices inc finishing time
@opposite 
 */
vector <int> DFS (Graph G)
{
    int n = G.n;
    //Initially it is set white and parent is NIL and some other properties
    vector <Vertex> V(n+1);
    vector <int> top_sort;

    // cout<<"running dfs"<<endl;
    for ( int i = 1 ; i <= n ; i++){
        if(V[i].color == WHITE)
            DFS_Util(G, V, i,top_sort);
    }
    return top_sort;

}
/* Helper function for DFS */
void DFS_Util (Graph G, vector <Vertex> &V,int v,vector <int> &top_sort){
    //each time dfs is called increase the time
    t++;
    //discovered when DFS is called on it
    V[v].discovered = t;
    // whenever DFS is called on a vertex mark it Grey
    V[v].color      = GREY;

    for (auto it = G.adj[v].begin(); it != G.adj[v].end() ; it++){
        if(V[*it].color == WHITE){
            V[*it].pi = v;
            
            DFS_Util(G,V,*it,top_sort);
        }
    }
    t++;
    V[v].finshed = t;
    top_sort.emplace_back(v);
    V[v].color = BLACK;

}








