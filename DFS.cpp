
// DFS
//strongly connected components
//topological sort
//transpose of a graph



#include <bits/stdc++.h>
using namespace std;

#define NIL -1

#define vvi vector <vector <int> > 
static int t = 0;

enum COLOR{
    WHITE,GREY,BLACK
};

class Graph{
    int n;
    list <int> *adj;
    // vector <int > DFS_Util(int, vector <int>&, vector <int>& , vector <int> &, vector <COLOR> &,vector <int> &);

    
    public:
        
        Graph(int);
        void strongly_connected_components(void);
        Graph transpose(void);
        void addEdge(int , int);
        void draw();  
        vector <int> DFS() ;
        void DFS_Util(COLOR*,int*,int*,int*,int,vector <int> &) ;
        void DFS_ssc(vector <bool> & ,int ,vector <int>&);



};

Graph::Graph(int size){
    this->n = size + 1;
    this->adj = new list <int> [size + 1];
}

void Graph::addEdge(int u , int v){
    adj[u].emplace_back(v);
}

void Graph::draw(){
    for (int i = 1; i < n ; i++ ){
        cout << i << " : ";
        for(auto it = adj[i].begin() ; it != adj[i].end() ; it++  ){
            cout << *it << " ";
        }
        cout<<"\n"; 
    }
    cout<<"\n"; 

}


//returning topologically sorted vector
vector <int> Graph :: DFS (void)
{
    int* discovered = new int [this->n]; 
    int* finished = new int [this->n];
    int* pi = new int [this->n];
    COLOR *color = new COLOR [this->n];
    vector <int> top_sort;
    for (int i = 1 ; i < this-> n ; i++)
    {
        color[i] = WHITE;
        pi[i] = -1;
    }
    // cout<<"running dfs"<<endl;
    for ( int i = 1 ; i < this->n ; i++){
        if(color[i] == WHITE)
            DFS_Util(color,discovered,finished,pi,i,top_sort);
    }
    return top_sort;

}

void Graph :: DFS_Util (COLOR* color,int* discovered,int* finished,int* pi,int v,vector <int> &top_sort){
    
    t++;
    // cout<<"running dfs for "<<v<<endl;
    // cout<<"v "<<v<<endl;
    discovered[v] = t;
    color[v] = GREY;
    // cout<<t<<" disc time for vertex "<<v<<endl;
    for (auto it = adj[v].begin(); it != adj[v].end() ; it++){
        if(color[*it] == WHITE){
            pi[*it] = v;
            
            
            DFS_Util(color,discovered,finished,pi,*it,top_sort);
        }
    }
    t++;
    finished[v] = t;
    // cout<<t<<" finishing time for vertex "<<v<<endl;
    top_sort.emplace_back(v);
    color[v] = BLACK;

}

Graph Graph :: transpose(){
    Graph g(this->n-1);
    for(int i = 1 ; i < n ; i++){
        for(auto it = adj[i].begin() ; it!= adj[i].end(); it++){
            g.addEdge(*it, i);
        }
    }
    g.draw();
    return g;

}

void Graph :: strongly_connected_components(void){
    Graph gt = this->transpose();
    vector <int> finishing_time_inc = this->DFS();
    vector <bool> visited(this->n,false);
    vector <int> ssc;
    for(auto it = finishing_time_inc.rbegin(); it!= finishing_time_inc.rend(); it++){
        if(!visited[*it]){
            gt.DFS_ssc(visited,*it,ssc);
            ssc.emplace_back(0);

        }

    }
    for(int i : ssc){
        if(i != 0)
            cout<<i<<" ";
        else cout<<endl;
    }


}

void Graph :: DFS_ssc(vector <bool> & visited,int v,vector <int>& ans){
    visited[v] = true;
    ans.emplace_back(v);

    for(auto it = adj[v].begin(); it!=adj[v].end();it++){
        if(!visited[*it]){
            DFS_ssc(visited,*it,ans);
        }
    }



}







int main(){

    int n;
    cin>>n;
    int e;
    cin>>e;
    int u,v;
    
    Graph g(n);
    while(e--){
        cin>>u>>v;
        g.addEdge(u,v);
    }
    
    g.draw();

    g.strongly_connected_components();



    // vector <int> a = g.DFS();
    // for (int i:a)
    //     cout<<i<<" ";
    // cout<<endl;






    return 0;
}