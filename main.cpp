#include <bits/stdc++.h>
#include "header.h"

using namespace std;
void BellmanFordRunner(void);
void Dag_Shortest_Path_Runner(void);



int main()
{
	Dag_Shortest_Path_Runner();

}

void BellmanFordRunner(){
	pair <Graph, map <int, map<int, int> > > Input = Weighted_Graph_Input();
	Graph G = Input.first;
	map <int, map<int, int> > Weight = Input.second;
	pair <bool, vector <Vertex>> Output =  Bellman_Ford(G,1, Weight);
	bool success = Output.first;
	vector <Vertex> V = Output.second;
	G.draw();
	cout<<success<<endl;
	print_verteex_vector(V);
}

void Dag_Shortest_Path_Runner(){
	pair <Graph, map <int, map<int, int> > > Input = Weighted_Graph_Input();
	Graph G = Input.first;
	map <int, map<int, int> > Weight = Input.second;
	vector <Vertex> Output =  Dag_Shortest_Paths(G,1, Weight);
	G.draw();
	print_verteex_vector(Output);
}