#include <bits/stdc++.h>
#include "header.h"
#define vi vector <int>
#define NIL -1
using namespace std;







//----------------------------------------------------------------------------------------

//BELLMAN FORD ALGORITHM

//we have considered having vertices 1 to n
pair <bool, vector <Vertex> > 
Bellman_Ford(Graph G, int s, map <int, map <int, int> > Weight){
    vector <Vertex> V = Initialize_Single_Source(G,s);
    //looping for n-1 times
    for(int j = 1 ; j < G.n ; j++)
    {
        for(int i = 1 ; i <= G.n ; i++){
            for(auto it = G.adj[i].begin(); it != G.adj[i].end(); it++){
                //relaxing i with all its neighboring vertices
                Relax_Vertex(V[i], V[*it], Weight[i][*it]);
            }               
        }
    }

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

vector <Vertex> 
Dag_Shortest_Paths(Graph G, int s, map <int, map <int, int> > Weight){
    //find the vertices in topolof=gical short
    //our DFS return reversed top sorted so usinng rbegin and rend
    vector <int> top_sorted_reverse = DFS(G);
    print_vector(top_sorted_reverse);
    //set source destination zero and other INT_MAX and parent NIL
    vector <Vertex> V =  Initialize_Single_Source(G,s);
    for (auto source = top_sorted_reverse.rbegin(); source != top_sorted_reverse.rend(); source++){
        for (auto destination = G.adj[*source].begin(); destination != G.adj[*source].end(); destination++){
            Relax_Vertex(V[*source], V[*destination], Weight[*source][*destination]);
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
    if(U.d + w < V.d)
        V.d = U.d + w;
}

//s is the source vertex

vector <Vertex> Initialize_Single_Source(Graph G, int s){
    
    vector <Vertex> V(G.n+1, {INT_MAX,NIL});
    V[s].d = 0;
    return V;

}

