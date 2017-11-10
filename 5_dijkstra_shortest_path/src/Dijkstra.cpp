/*
 * Dijkstra.cpp
 *
 *  Created on: 11.05.2017
 *      Author: Zari
 */

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>     /* atoi */
#include <algorithm>

using namespace std;



class Graph{

	struct Edge{
		unsigned int m_head;
		unsigned int m_cost;
	};

	private:
		void parse_input_line(string);
		unsigned int V;
		unsigned int get_shortest_path_vertex(const vector<unsigned int>& dist, const vector<unsigned int>& unvisited);
	public:
		vector<vector<Edge> > *m_edges;
		Graph(const char*, unsigned int);
		void print_graph();
		unsigned int get_shortest_path(unsigned int s, unsigned int e);
};

Graph::Graph(const char* file_name, unsigned int V){

	ifstream myfile;
	myfile.open(file_name);

	if (myfile.is_open()){
		string line;

		this->V = V;
		m_edges = new vector<vector<Edge> >(V, vector<Edge>(0));

		while ( getline(myfile,line) ){
			parse_input_line(line);
		}
		cout << "Finished reading file" << endl;
		myfile.close();
		cout << "File closed" << endl;
	}
	else{
		perror("Error: Unable to open file.");
	}
}

void Graph::parse_input_line(string line){

	string delimiter1 = "\t";

	// tail
	size_t pos = line.find(delimiter1);
	string str_tail = line.substr(0, pos);
	line.erase(0, pos + delimiter1.length());
	const unsigned int tail = atoi(str_tail.c_str())-1;


	// head,cost
	string delimiter2 = ",";
	while ((pos = line.find(delimiter1)) != string::npos ){

		pos = line.find(delimiter1);

//		unsigned int next_pos = pos+1;


		// save interesting chars
		string str_head_cost = line.substr(0, pos);
		line.erase(0, pos + delimiter1.length());

		//find head of the edge
		pos = str_head_cost.find(delimiter2);
		string str_head = str_head_cost.substr(0, pos);

		//find cost of the edge
		str_head_cost.erase(0, pos + delimiter2.length());
		string str_cost = str_head_cost;

		//convert strings to ints

		Graph::Edge edge;// = new Graph::Edge;

		edge.m_head = atoi(str_head.c_str())-1;
		edge.m_cost = atoi(str_cost.c_str());

//		m_edges[tail].push_back(edge);
		(*m_edges).at(tail).push_back(edge);

//		if (line[next_pos] == 0x0D)
//			break;
	}
}

void Graph::print_graph(){
	cout << "Edges :\n";

	for (unsigned int i = 0; i<V; ++i){
		unsigned int len = ((*m_edges).at(i)).size();
		for (unsigned int j = 0; j<len; ++j){
			cout << (((*m_edges).at(i)).at(j)).m_head << "," << (((*m_edges).at(i)).at(j)).m_cost << " ";
		}
		cout << endl;
	}
}

unsigned int Graph::get_shortest_path_vertex(const vector<unsigned int>& dist, const vector<unsigned int>& unvisited){

	unsigned int shortest_path = 1000000;
	unsigned int shortest_index = 0;

	for (unsigned int i = 0; i < unvisited.size(); ++i){
		unsigned int j = unvisited[i];
		if (dist[j] < shortest_path){
			shortest_path = dist[j];
			shortest_index = j;
		}
	}

	return shortest_index;
}

unsigned int Graph::get_shortest_path(unsigned int s, unsigned int e){

	vector<unsigned int> unvisited(V);// = new vector<unsigned int>[V];
	vector<unsigned int> dist(V);// = new vector<unsigned int>[V];

	for (unsigned int i = 0; i < V; ++i){
		unvisited[i] = i;
		dist[i] = 1000000;
	}

	// starting vertex
	dist[s] = 0;

	while (unvisited.size() != 0){
		unsigned int u = get_shortest_path_vertex(dist, unvisited);
//		cout << "Shortest path vertex is : " << u << endl;
		vector<Edge> adjecent ( (*m_edges).at(u) );

//		cout << "Unvisited size: " << unvisited.size() << endl;
		unsigned int index_to_delete = find(unvisited.begin(), unvisited.end(), u) - unvisited.begin();
		unvisited.erase(unvisited.begin() + index_to_delete);
//		cout << "Delete element of unvisited\nUnvisited size: " << unvisited.size() << endl;

		for (unsigned int i = 0; i < adjecent.size(); ++i){
			Edge edge = adjecent[i];
			if (dist[edge.m_head] > dist[u] + edge.m_cost){
				dist[edge.m_head] = dist[u] + edge.m_cost;
			}
		}
	}

	return dist[e];

}

int main(){

	cout << "Program Start\n";
//	Graph G("dijkstraTest.txt", 4);
	Graph G("dijkstraData.txt", 200);

	G.print_graph();
//	unsigned int start = 1;
//	unsigned int end = 4;
//	cout << "Shortest path from: " << start << " to " << end << " is equal to: " << G.get_shortest_path(start-1, end-1) << endl;
	unsigned int vertices[] = {7,37,59,82,99,115,133,165,188,197};
	 vector<unsigned int> end_vertices (vertices, vertices + sizeof(vertices) / sizeof(unsigned int) );

	unsigned int start_vertex = 1;
	for (unsigned int i = 0; i < end_vertices.size(); ++i){
		cout << "Start vertex: " << end_vertices[i] << endl;
		cout << "Shortest path from: " << start_vertex << " to " << end_vertices[i] <<
				" is equal to: " << G.get_shortest_path(start_vertex-1, end_vertices[i]-1) << endl;
	}

	cout << "Program End\n";

	return 0;
}



