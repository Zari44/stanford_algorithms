////============================================================================
//// Name        : MinCut.cpp
//// Author      : Zari
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned int uint;
typedef std::vector<unsigned int> vint;
typedef std::vector<vint> vvector;
typedef std::vector<std::string> vstring;

class Graph {
	  void parse_input_line(string);
	  void print_vector_int(vint);
	  void get_random_edge();
	  void edge_contraction();
	  void concatinate_edges();
	  void destroy_vertex();
	  void destroy_self_loop();
	  uint one_run_get_minimum_cut();
	  void copy_graph_to_initial_state();
	  vint N;
	  vvector M;
	  vint N_init;
	  vvector M_init;
	  struct Edge{
	  	  uint ni1;
	  	  uint ni2;
	  } edge;

	public:
	  Graph(string file_name);
	  uint get_minimum_cut(uint number_of_runs);
	  void print_edges();
	  void print_vertices();
	  uint get_number_of_edges();
	  uint get_number_of_vertices();
};

Graph::Graph(string file_name){

	srand(time(0));

	ifstream myfile(file_name, std::ifstream::in);

	if (myfile.is_open()){
		//std::cout << "File Opened.\n";
		std::string line;
		while ( getline(myfile,line) ){
			parse_input_line(line);
		}
		myfile.close();
	}
	else{
		perror("Unable to open file. Error");
	}
}


void Graph::parse_input_line(std::string line){

	const  std::string delimiter = "\t";
	// first element is vertex number
	size_t pos = line.find(delimiter);
	{
		const std::string str_int = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		const uint integer = atoi(str_int.c_str());
		// count vertices from zero
		this->N_init.push_back(integer-1);
	}

	vint edges;
	while ( (pos = line.find(delimiter)) != std::string::npos){
		const std::string str_int = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		const uint integer = atoi(str_int.c_str());
		// index vertices from zero
		edges.push_back(integer-1);
	}
	this->M_init.push_back(edges);

	this->copy_graph_to_initial_state();
}

void Graph::copy_graph_to_initial_state(){
	this->N = this->N_init;
	this->M = this->M_init;
}

void Graph::print_vector_int(vint V){
	for(auto const& i : V) {
		std::cout << i << " ";
	}
}

void Graph::print_edges(){
	cout << "Edges :\n";
	for(auto const& vint : this->M) {
		print_vector_int(vint),	cout << '\n';
	}
}

void Graph::print_vertices(){
	cout << "Vertices :\n";
	for(auto const& n : this->N) {
		std::cout << n << " ";
	}
	cout << "\n";
}

uint Graph::get_number_of_edges(){
	uint m = 0;
	for (auto const &Vm : this->M){
		m = m + Vm.size();
	}
	return m/2;
}

uint Graph::get_number_of_vertices(){
	return this->N.size();
}

void Graph::get_random_edge(){

	const uint vert1_index = rand() % this->get_number_of_vertices();
	const uint vert1_number = vert1_index;

	const uint vert2_index = rand() % this->M.at(vert1_index).size();
	const uint vert2_number = this->M.at(vert1_index).at(vert2_index);


	// for convenience it is assumed that ni1 is smaller

	if ( vert1_number < vert2_number ){
		this->edge.ni1 = vert1_number;
		this->edge.ni2 = vert2_number;
	}
	else{
		this->edge.ni1 = vert2_number;
		this->edge.ni2 = vert1_number;
	}
}

void Graph::concatinate_edges(){

	const vint edges_n2(this->M.at(this->edge.ni2));
	this->M.at(this->edge.ni1).insert(this->M.at(this->edge.ni1).end(), edges_n2.begin(), edges_n2.end() );
}

void Graph::destroy_vertex(){

	const uint vertex_number_that_is_left = this->N.at(this->edge.ni1);
	const uint vertex_number_to_destroy = this->N.at(this->edge.ni2);

	// if edge points to destroyed vertex, change the pointing to the combined vertex
	for (uint i = 0; i < this->M.size(); i++){
		for (uint j = 0; j < this->M[i].size(); j++){
			if (this->M[i].at(j) == vertex_number_to_destroy)
				this->M[i].at(j) = vertex_number_that_is_left;
		}
	}

	// change the number of the vertex in M
	for (uint i = 0; i < this->M.size(); i++){
		for (uint j = 0; j < this->M[i].size(); j++){
			if (this->M[i].at(j) > vertex_number_to_destroy)
				this->M[i].at(j) = this->M[i].at(j) - 1;
		}
	}

	// change the number of the vertex in N
	for (uint i = vertex_number_to_destroy+1; i < this->N.size(); i++){
		this->N.at(i) = this->N.at(i) - 1;
	}

	// erase from N and M vectors
	this->N.erase(this->N.begin() + this->edge.ni2);
	this->M.erase(this->M.begin() + this->edge.ni2);
}

void Graph::destroy_self_loop(){

	for (uint i = 0; i < this->M.size(); i++){
		for (uint j = 0; j < this->M[i].size(); j++){
			const vint::iterator iterators_to_remove = remove(this->M.at(i).begin(), this->M.at(i).end(), this->N.at(i));
			this->M.at(i).erase(iterators_to_remove, this->M.at(i).end());
		}
	}
}

void Graph::edge_contraction(){
	this->get_random_edge();
	this->concatinate_edges();
	this->destroy_vertex();
	this->destroy_self_loop();
}

uint Graph::one_run_get_minimum_cut(){

	while (this->get_number_of_vertices() > 2){
		this->edge_contraction();
	}

	return this->get_number_of_edges();
}

uint Graph::get_minimum_cut(uint number_of_runs){

	uint min_cut = this->get_number_of_edges();

	for (uint i = 0; i < number_of_runs; i++){
		this->copy_graph_to_initial_state();
		const uint cut_number = this->one_run_get_minimum_cut();
		if (cut_number < min_cut)
			min_cut = cut_number;
	}

	return min_cut;
}

int main() {

	Graph G("kargerMinCut.txt");
	cout << "Minimum cut is: " << G.get_minimum_cut(10);

	return 0;
}

