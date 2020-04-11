#include <bits/stdc++.h>
using namespace std;

#define NIL -1

enum COLOR{
    WHITE,GREY,BLACK
};

COLOR getColor(COLOR c){
    if(c == WHITE)
        return BLACK;
    else return WHITE;
}

class Graph{
    int n;
    list <int> *adj;
    
    public:
        Graph(int);
        void addEdge(int , int);
        void draw();  
        void BFS(int) ;

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
/* path to print fromsource to vertex  */
void print_path(int s, int v, vector<int> &pi){
    if(v == s)
        cout<< v << " :: ";
    else if(pi[v] == NIL)
        cout << "no path exists"<<endl;
    else{
        print_path(s,pi[v],pi);
        cout<< v << " :: ";
    }
}



void Graph :: BFS(int s){
    vector <COLOR > color(n,WHITE);
    vector <int > d(n,INT_MAX);
    vector <int > pi(n,-1);
    color[s]    = GREY;
    d[s]        = 0;

    queue <int> q;
    q.emplace(s);
    while( !q.empty()){
        int out = q.front();
        cout << out << " :  distance = " << d[out] << " : parent " << pi[out] << endl;;
        q.pop();
        for(auto it = adj[out].begin() ; it != adj[out].end() ; it++)
        {
            if(color[*it] == WHITE){
                color[*it]  = GREY;
                d[*it]      = d[out] + 1;
                pi[*it]     = out;
                q.emplace(*it);
            } 
        }
        color[out] = BLACK;
        




}  
print_path(1,6,pi);   


    

}






int main(){

    Graph g(6);
    g.addEdge(1,2) ;
    g.addEdge(1,3) ;
    g.addEdge(1,4) ;
    g.addEdge(5,4) ;
    g.addEdge(3,5) ;
    g.addEdge(5,6) ;
    g.addEdge(3,6) ;
    g.addEdge(6,2) ;

    g.draw();

    g.BFS(1);






    return 0;
}