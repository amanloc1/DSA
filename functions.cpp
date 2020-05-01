#include <bits/stdc++.h>
#include "header.h"
using namespace std;

void print_vector(vector <int> A ){

	for(auto it : A)
		cout<<it<< " ";
	cout<<endl;
}

//size is n+1
void print_verteex_vector(vector <Vertex> A ){
	cout<<"---------------------------\nvertex vector is : \n";
	for(int i = 1; i < A.size(); i++){
		cout << " Vertex : " << i << "\tdistance : " << A[i].d <<  endl;
	}
}

pair <Graph, map <int, map <int, int> >  >
Weighted_Graph_Input(){
	cout<<"Running Weighted Graph Input"<<endl;

	int n; // no.of vertices
	int m; // no.of edges
	cout << "Enter no. of vertices\n"; cin >> n;
	cout << "Enter no. of edges\n"; cin >> m;

	//source destination weight
	int u, v, w;
	cout<<"Enter "<<m<<" triplets of integers u v w Edge(u,v) with weight w"<<endl;
	Graph G(n);
	map <int, map<int, int> > Weight;
	
	for(int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		G.addEdge(u,v);
		Weight[u][v] = w;
	}

	cout<<"exiting Weighted Graph Input"<<endl;

	return {G, Weight};
}


Graph 
Graph_Input(){
	cout<<"Running Graph Input"<<endl;

	int n; // no.of vertices
	int m; // no.of edges
	cout << "Enter no. of vertices\n"; cin >> n;
	cout << "Enter no. of edges\n"; cin >> m;

	//source destination weight
	int u, v;
	cout<<"Enter "<<m<<" pairs of integers u v Edge(u,v)"<<endl;
	Graph G(n);
	for(int i = 0; i < m; i++)
	{
		cin >> u >> v;
		G.addEdge(u,v);
	}
	cout<<"exiting Weighted Graph Input"<<endl;
	return G;
}









