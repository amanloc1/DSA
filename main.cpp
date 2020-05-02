#include <bits/stdc++.h>
#include "header.h"

using namespace std;
void BellmanFordRunner(void);
void Dag_Shortest_Path_Runner(void);
void DijkstraRunner(void);



int main()
{
	// BellmanFordRunner();
	// DijkstraRunner();
	Dag_Shortest_Path_Runner();
}

void BellmanFordRunner(){
	cout<<"Runningg Bellman ford"<<endl;
	pair <Graph, mimii > Input = Weighted_Graph_Input();
	Graph G = Input.first;
	mimii Weight = Input.second;
	pair <bool, vv> Output =  Bellman_Ford(G,1, Weight);
	bool success = Output.first;
	vv V = Output.second;
	G.draw();
	cout<<success<<endl;
	print_verteex_vector(V);
}

void Dag_Shortest_Path_Runner(){
	cout<<"Runningg Dag shortest path"<<endl;
	pair <Graph, mimii > Input = Weighted_Graph_Input();
	Graph G = Input.first;
	mimii Weight = Input.second;
	vv Output =  Dag_Shortest_Paths(G,1, Weight);
	G.draw();
	print_verteex_vector(Output);
}

void DijkstraRunner(){
	cout<<"Runningg Dijkstra"<<endl;
	pair <Graph, mimii > Input = Weighted_Graph_Input();
	Graph G = Input.first;
	mimii Weight = Input.second;
	vv V = Dijkstra(G, 1, Weight);
	G.draw();
	print_verteex_vector(V);

}