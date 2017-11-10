/*
 * main.cpp
 *
 *  Created on: 22.04.2017
 *      Author: Zari
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

typedef unsigned int uint;
typedef std::vector<unsigned int> vint;
typedef std::vector<bool> vbool;
typedef std::vector<vint> vvector;
typedef std::vector<std::string> vstring;
class Graph {
	  void parse_input_line(string);
//	  void print_vector_int(vint);
////	  void edge_contraction();
////	  void destroy_vertex();
////	  void destroy_self_loop();
//	  void get_finish_times();
//	  void visit_vertex(uint vertex_number);
//	  void copy_graph_to_initial_state();

//	  vint N;
	  vvector M;
//	  vvector M_rev;
//	  vint fin_time;
//	  vbool visited;
//	  vvector adj;
//	  stack<uint> Stack;
	public:
	  Graph(string file_name);
//	  void print_edges();
//	  void print_edges_transposed();
//	  void print_vertices();
//	  void get_transpose();
//	  void get_stack();
//	  void DFS(uint vertex);
//	  uint get_number_of_edges();
//	  uint get_number_of_vertices();
};

Graph::Graph(string file_name){

	ifstream myfile(file_name, ifstream::in);

	if (myfile.is_open()){
		string line;
		while ( getline(myfile,line) )
			parse_input_line(line);
		myfile.close();
	}
	else{
		perror("Error: Unable to open file.");
	}
}

void Graph::parse_input_line(std::string line){

	const string delimiter = " ";
	size_t pos = line.find(delimiter);

	std::string str_int = line.substr(0, pos);
	const uint tail = atoi(str_int.c_str())-1;
	line.erase(0, pos + delimiter.length());

	pos = line.find(delimiter);
	str_int = line.substr(0, pos);
	const uint head = atoi(str_int.c_str())-1;

	while (this->M.size() <= tail){
		vint empty_vector;
		this->M.push_back(empty_vector);
	}
	this->M.at(tail).push_back(head);

	while (this->M.size() <= head){
		vint empty_vector;
		this->M.push_back(empty_vector);
	}
}

int main(){

	Graph graph("SCCtest.txt");
//	G.print_edges();
////	G.get_transpose();
////	G.print_edges_transposed();
////	G.DFS(0);
//	G.get_stack();


	cout << "Finished.";
	return 0;
}



