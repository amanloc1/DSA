#include <bits/stdc++.h>
#include "header.h"
#define vi vector <int>
#define NIL -1
using namespace std;


/* 
@definitions



s = source vertex
d = distance from source verytex
mpq = min priority queue
G - Graph
Weight - map<int, map<int, int>>
    stores weight u--->v
 */




//----------------------------------------------------------------------------------------

//BELLMAN FORD ALGORITHM

//we have considered having vertices 1 to n


/* Bellman Ford Algorithm
@Edge type : both +ve and -ve
@working: n -1 rounds of relaxation of each vertex 
@caution : no negative edge cycle should be reachable
@complexity O(VE)
 */
pair <bool, vector <Vertex> > 
Bellman_Ford(Graph G, int s, map <int, map <int, int> > Weight){
    //set source vertex distance zero and others INT_MAX
    vector <Vertex> V = Initialize_Single_Source(G,s);
    //looping for n-1 times
    for(int j = 1 ; j < G.n ; j++){
        //relaxing on  all 1 to n vertices one by one
        for(int i = 1 ; i <= G.n ; i++){
            // relax all aj=djacent vertex
            for(auto it = G.adj[i].begin(); it != G.adj[i].end(); it++){
                //relaxing i with all its neighboring vertices
                Relax_Vertex(V[i], V[*it], Weight[i][*it]);
            }               
        }
    }
    // checking if result is true otherwise it contains negative edge cycle
    for(int i = 1 ; i <= G.n ; i++){
        for(auto it = G.adj[i].begin(); it != G.adj[i].end(); it++){
            //checking vertices if relaxed or not 
            //if not return false else return true
            if(V[i].d + Weight[i][*it] < V[*it].d)
                return {false, V};
        }               
    }
    return {true, V};

}

//---------------------------------------------------------------------------------------

//DIRECTED ACYCLIC GRAPH SHORTEST PATH

/* Dag shortest Path 
@Edge type : both +ve and -ve
@caution : negative edge cycle should not be reachable
@working : first topologically sort the vertices and then relax in order from up to down as in top-sorted vertices
*/
vector <Vertex> 
Dag_Shortest_Paths(Graph G, int s, map <int, map <int, int> > Weight){
    //find the vertices in topological sort
    //our DFS returned reversed top sorted so using rbegin and rend to relax in reverse order
    vector <int> top_sorted_reverse = DFS(G);
    // print_vector(top_sorted_reverse);
    //set source destination zero and other INT_MAX and parent NIL
    vector <Vertex> V =  Initialize_Single_Source(G,s);
    //relaxing vertices in topological order
    for (auto source = top_sorted_reverse.rbegin(); source != top_sorted_reverse.rend(); source++){
        for (auto destination = G.adj[*source].begin(); destination != G.adj[*source].end(); destination++){
            Relax_Vertex(V[*source], V[*destination], Weight[*source][*destination]);
        }
    }
    return V;   
}

//---------------------------------------------------------------------------------------

//DIJKSTRA'S ALGORITHM


/* comparator function for Dijksta's min priority queue */
struct cmp{
    bool operator()(pair <int, Vertex* > X, pair <int, Vertex* >  Y){
        return X.second->d > Y.second->d;
    }

};


/* Dijkstra's Algorithm 
@Edge Type : non negative edges
@working - selects vertex u with least weight in V-S
    where S is the set of used vertices and then relaxes 
    all edges leaving u

@lower than Bellman ford
 */
vector <Vertex>
Dijkstra(Graph G, int s, map <int, map<int, int> > Weight){
    //set source vertex distance zero and others INT_MAX
    vector <Vertex> V =  Initialize_Single_Source(G,s);
    //storing all vertexes with index value in minimum priority queue
    priority_queue <pair <int, Vertex* > , vector <pair <int, Vertex* >  >, cmp  > mpq;

    // push index and pointer to vertex in priority queue
    //pointer to vertex will allow us to change d value of vertex
    for (int index = 1 ; index < V.size() ; index++){
        mpq.push({index,&V[index]});       
    }
    // print_vertex_vector(V); 

    // until min priority queue becomes empty
    while(!mpq.empty()){
        //index is stored in first and then vertex pointer
        //why pointer : becz we can change d value 
        int index = mpq.top().first; 
        //pop top element and relax all edges leaving popped vertex 
        mpq.pop();
        for(auto it = G.adj[index].begin(); it != G.adj[index].end(); it++){
            // cout<<"\nRelaxing :: source : "<<index<<" destination : "<<*it<<" weight : "<<Weight[index][*it] <<endl;
            Relax_Vertex(V[index], V[*it], Weight[index][*it]);
            // print_verteex_vector(V);
        }
    }
    return V;
}





























//-----------------------------------------------------------------------------------------------------

//Utility functions


//Going from u to v
//U = source
//V = destination
void Relax_Vertex(Vertex &U, Vertex &V, int w){
    // cout<<"Before relaxing : "<<U.d <<" "<<V.d<<endl;
    if(U.d + w < V.d)
        V.d = U.d + w;
    // cout<<"After relaxing : "<<U.d <<" "<<V.d<<endl;
}

//s is the source vertex

vector <Vertex> Initialize_Single_Source(Graph G, int s){
    
    vector <Vertex> V(G.n+1, {INT_MAX,NIL});
    V[s].d = 0;
    return V;

}

