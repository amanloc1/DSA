#include <bits/stdc++.h>
#include "header.h"
using namespace std;
/* 
@functions : 

                Graph::Graph(int size);
void            Graph::addEdge(int u , int v);
void            Graph::draw();
Graph           transpose(Graph G);
pair <vv, vi >  DFS (Graph G);
void            DFS_Util (Graph G, vv &V,int v,vi &top_sort);
vv              BFS(Graph G,int s);
void            print_path(int s, int v,int dest, vector<Vertex> &V);
vi              strongly_connected_components(Graph G);
void            DFS_ssc(Graph G, vector <bool> &visited,int v,vi& ans);
pair <bool,vv>  Bellman_Ford(Graph G, int s, mimii Weight);
vv              Dag_Shortest_Paths(Graph G, int s, mimii Weight);
struct cmp;
vv              Dijkstra(Graph G, int s, mimii Weight);
void            Relax_Vertex(Vertex &U, Vertex &V, int w);
vv              Initialize_Single_Source(Graph G, int s);   

 */

/* @conventions : 
    1> vertices from 1 to n
    2> size of adj = n+1
 */

/* 
@definitions
mimii   = map<int, map <int, int>
vv      = vector <Vertex>
s       = source vertex
d       = distance from source verytex
mpq     = min priority queue
G       - Graph
Weight  - map<int, map<int, int>>

    stores weight u--->v
 */

// GRAPH INTERNAL MEMBER FUNCTIONS


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

//----------------------------------------------------------------------------------------


// ELEMENTARY GRAPH OPERATIONS 
/* Get Transpose of graph */
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
@return : vertex vector and topologically sorted vertices inc finishing time 
@opposite 
 */
pair <vv, vi >
DFS (Graph G)
{
    int n = G.n;
    //Initially it is set white and parent is NIL and some other properties
    vv V(n+1);
    vi top_sort;

    // cout<<"running dfs"<<endl;
    for ( int i = 1 ; i <= n ; i++){
        if(V[i].color == WHITE)
            DFS_Util(G, V, i,top_sort);
    }
    return {V, top_sort};

}
/* Helper function for DFS */
void DFS_Util (Graph G, vv &V,int v,vi &top_sort){
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

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------


// GRAPH BASIC ALGORITHMS

/* Breadth First Search BFS */
vv
BFS(Graph G,int s){
    int n = G.n;
    // initialize a vector of vertices and set distance of source = 0 and color Grey
    vv V(n+1, {INT_MAX, NIL, WHITE});
    V[s] = {0, NIL, GREY};
    
    queue <int> q;
    q.emplace(s);

    while( !q.empty()){
        // take out one vertex from queue and then traverse to all its neighbours first
        int out = q.front();
        // cout << out << " :  distance = " << V[out].d << " : parent " << V[out].pi << endl;
        q.pop();
        //discovering all its neighbours of [out]
        for(auto it = G.adj[out].begin() ; it != G.adj[out].end() ; it++)
        {
            // if vertex is not visited yet
            if(V[*it].color == WHITE){
                // mark it visted and set distance and parent
                V[*it] = {V[out].d + 1, out, GREY};
                // V[*it].color  = GREY;
                // V[*it].d      = V[out].d + 1;
                // V[*it].pi     = out;

                //insert unvisted vertices
                q.emplace(*it);
            } 
        }
        // after fully discovering its neighbours mark it fully discovered
        V[out].color = BLACK; 
    } 
    return V; 
}


/* print path 
@param : s-source; v - vertex, dest-destination (used for pretty print), V-vertex vector
@working - 
 */
void print_path(int s, int v,int dest, vector<Vertex> &V){
    // @working - v1(dest), v2 ,v3 ......... s
    // print_path for  v2, v3 .....s and then print v1
    //first vertex to be printed will be s ....V3, v2, v1

    //until v becomes s recurse
    if(v == s)
        cout<< v << " :: ";
    else if(V[v].pi == NIL)
        cout << "no path exists"<<endl;
    else{
        print_path(s,V[v].pi,dest,V);
        //if v reaches destination no need to print ::
        if(v==dest)
            cout << v <<endl;
        else         
            cout<< v << " :: ";
    }
}

//----------------------------------------------------------------------------------------


/* stronly connected components in directed graphs
@working
 - call DFS(G) to get topsorted vertices and compute G transpose
 - call DFS(Gt) but in decreasing finishing time order

 Note - started firsts ends last that we have again called DFS(gt) from the same source
 @return vertices separated by zeros
 */
vi strongly_connected_components(Graph G){
    int n = G.n;
    //Get transpose of G
    Graph gt = transpose(G);
    //Topologically sorted vertices 
    //get finishing times of G
    vi finishing_time_inc = DFS(G).second;
    vector <bool> visited(n+1,false);
    vi ssc;
    //Again calling DFS to get zeros separated vertices in decreasing finishing time
    for(auto it = finishing_time_inc.rbegin(); it!= finishing_time_inc.rend(); it++){
        if(!visited[*it]){
            DFS_ssc(gt, visited,*it,ssc);
            //used to distinguish
            ssc.emplace_back(0);
        }
    }
    // for(int i : ssc){
    //     if(i != 0)
    //         cout<<i<<" ";
    //     else cout<<endl;
    // }

    //ssc separated by zeros
    return ssc;
}

/* Helper DFS for ssc */
void DFS_ssc(Graph G, vector <bool> &visited,int v,vi& ans){
    visited[v] = true;
    ans.emplace_back(v);
    for(auto it = G.adj[v].begin(); it!=G.adj[v].end();it++){
        if(!visited[*it]){
            DFS_ssc(G,visited,*it,ans);
        }
    }



}




//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

//BELLMAN FORD ALGORITHM

//we have considered having vertices 1 to n

/* Bellman Ford Algorithm
@Edge type : both +ve and -ve
@working: n -1 rounds of relaxation of each vertex 
@caution : no negative edge cycle should be reachable
@complexity O(VE)
 */
pair <bool, vv  > 
Bellman_Ford(Graph G, int s, mimii Weight){
    //set source vertex distance zero and others INT_MAX
    vv  V = Initialize_Single_Source(G,s);
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
vv  
Dag_Shortest_Paths(Graph G, int s, mimii Weight){
    //find the vertices in topological sort
    //our DFS returned reversed top sorted so using rbegin and rend to relax in reverse order
    vector <int> top_sorted_reverse = DFS(G).second;
    // print_vector(top_sorted_reverse);
    //set source destination zero and other INT_MAX and parent NIL
    vv  V =  Initialize_Single_Source(G,s);
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
vv 
Dijkstra(Graph G, int s, mimii Weight){
    //set source vertex distance zero and others INT_MAX
    vv  V =  Initialize_Single_Source(G,s);
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

vv  Initialize_Single_Source(Graph G, int s){
    
    vv  V(G.n+1, {INT_MAX,NIL});
    V[s].d = 0;
    return V;

}









