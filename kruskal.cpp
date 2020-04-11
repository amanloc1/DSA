
#include <bits/stdc++.h>
using namespace std;

class Edge{
public:
    int s,d,w;
};


class Graph{
public:
    int V,E;
    Edge *edge;
};


Graph * createGraph(int v, int e){
    Graph *g = new Graph();
    g->E = e;
    g->V = v;
    g->edge = new Edge[e];
    return g;
}



        
int main(){




    return 0;
}