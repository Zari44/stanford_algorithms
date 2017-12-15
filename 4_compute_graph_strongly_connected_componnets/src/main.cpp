// C++ Implementation of Kosaraju's algorithm to print all SCCs
#include <iostream>
#include <list>
#include <stack>


#include <vector>
#include <fstream>
#include <string>
#include <algorithm> //find()
#include <stdio.h>



using namespace std;

class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // An array of adjacency lists

    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing
    // time
    void fillOrder(int v, bool visited[], stack<int> &Stack);

    // A recursive function to print DFS starting from v
    unsigned int DFSUtil(int v, bool visited[], unsigned int scc);
    void parse_input_line(std::string line);
    void get_vertices_in_line(unsigned int&, unsigned int&, std::string);
public:
    Graph(int V);
    Graph(string file_name, int V);
    void addEdge(int v, int w);

    // The main function that finds and prints strongly connected
    // components
    void printSCCs();

    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

Graph::Graph(string file_name, int V){

	ifstream myfile(file_name, std::ifstream::in);

	if (myfile.is_open()){
		string line;
	    this->V = V;
		adj = new list<int>[V];

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

void Graph::get_vertices_in_line(unsigned int& out_a, unsigned int& out_b, std::string line){
	const string delimiter = " ";
	size_t pos = line.find(delimiter);

	string str_int = line.substr(0, pos);
	out_a = atoi(str_int.c_str());
	line.erase(0, pos + delimiter.length());

	pos = line.find(delimiter);
	str_int = line.substr(0, pos);
	out_b = atoi(str_int.c_str());
}

void Graph::parse_input_line(std::string line){

	const string delimiter = " ";
	size_t pos = line.find(delimiter);

	string str_int = line.substr(0, pos);
	const unsigned int tail = atoi(str_int.c_str())-1;
	line.erase(0, pos + delimiter.length());

	pos = line.find(delimiter);
	str_int = line.substr(0, pos);
	const unsigned int head = atoi(str_int.c_str())-1;

    adj[tail].push_back(head); // Add head to tails’s list.

    if (tail % 100000 == 0)
    	cout << "tail: " << tail << endl;
//	while (this->M.size() <= tail){
//		vector<unsigned int> empty_vector;
////		this->M.push_back(empty_vector);
//		adj.push_back(empty_vector);
//	}
//	this->M.at(tail).push_back(head);
//
//	while (this->M.size() <= head){
//		vector<unsigned int> empty_vector;
//		this->M.push_back(empty_vector);
//	}
}

// A recursive function to print DFS starting from v
unsigned int Graph::DFSUtil(int v, bool visited[], unsigned int scc)
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";
    scc++;
//    cout << adj[v] << endl;
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
        	scc = DFSUtil(*i, visited, scc);

    return scc;
}

Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++){
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i){
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            fillOrder(*i, visited, Stack);

    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}

// The main function that finds and prints all strongly connected
// components
void Graph::printSCCs()
{
    stack<int> Stack;
    ofstream outputfile;
    outputfile.open("output.txt");

    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);

    // Create a reversed graph
    Graph gr = getTranspose();

    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
        	unsigned int scc = 0;
            scc = gr.DFSUtil(v, visited, scc);
            cout << endl;
            outputfile << scc << endl;
        }
    }
    outputfile.close();
    cout << "Output file closed\n";
}

void sort_output(){
	ifstream inputfile("output.txt");

	string line;

	list<unsigned int> num_list;

	unsigned int num;
	while (inputfile >> num){
		if (num > 1){
			num_list.push_back(num);
		}
	}

	inputfile.close();
	ofstream outputfile("output_sorted.txt");

	num_list.sort();

	for (list<unsigned int>::iterator it = num_list.end(); it != num_list.begin(); --it){
		outputfile << *it << endl;
	}

	outputfile.close();
}

// Driver program to test above functions
int main()
{

	cout << "Constructor graph\n";
    Graph g("SCC.txt", 875714);
//    Graph g("SCCtest.txt", 5);

    cout << "Following are strongly connected components in "
            "given graph \n";

    g.printSCCs();

	cout << "sorting started\n";
    sort_output();
	cout << "sorting finished\n";

    return 0;
}

////============================================================================
//// Name        : Stnfd_GraphSearch.cpp
//// Author      : Zari
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
///*
// * main.cpp
// *
// *  Created on: 03.04.2017
// *      Author: Zari
// */
//
//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <fstream>
//#include <string>
//#include <algorithm>
//#include <stack>
//
//using namespace std;
//
//typedef unsigned int uint;
//typedef std::vector<unsigned int> vint;
//typedef std::vector<bool> vbool;
//typedef std::vector<vint> vvector;
//typedef std::vector<std::string> vstring;
//class Graph {
//	  void parse_input_line(string);
//	  void print_vector_int(vint);
////	  void edge_contraction();
////	  void destroy_vertex();
////	  void destroy_self_loop();
//	  void get_finish_times();
//	  void visit_vertex(uint vertex_number);
//	  void copy_graph_to_initial_state();
//
////	  vint N;
//	  vvector M;
//	  vvector M_rev;
//	  vint fin_time;
//	  vbool visited;
//	  vvector adj;
//	  stack<uint> Stack;
//	public:
//	  Graph(string file_name);
//	  void print_edges();
//	  void print_edges_transposed();
//	  void print_vertices();
//	  void get_transpose();
//	  void get_stack();
//	  void DFS(uint vertex);
////	  uint get_number_of_edges();
////	  uint get_number_of_vertices();
//};
//
//Graph::Graph(string file_name){
//
//	ifstream myfile(file_name, std::ifstream::in);
//
//	if (myfile.is_open()){
//		string line;
//		while ( getline(myfile,line) )
//			parse_input_line(line);
//		myfile.close();
//	}
//	else{
//		perror("Error: Unable to open file.");
//	}
//}
//
//void Graph::parse_input_line(std::string line){
//
//	const string delimiter = " ";
//	size_t pos = line.find(delimiter);
//
//	std::string str_int = line.substr(0, pos);
//	const uint tail = atoi(str_int.c_str())-1;
//	line.erase(0, pos + delimiter.length());
//
//	pos = line.find(delimiter);
//	str_int = line.substr(0, pos);
//	const uint head = atoi(str_int.c_str())-1;
//
//	while (this->M.size() <= tail){
//		vint empty_vector;
//		this->M.push_back(empty_vector);
//	}
//	this->M.at(tail).push_back(head);
//
//	while (this->M.size() <= head){
//		vint empty_vector;
//		this->M.push_back(empty_vector);
//	}
//}
//
//void Graph::get_transpose(){
//
//	for (vvector::iterator it_vector = this->M.begin(); it_vector != this->M.end(); ++it_vector){
//		vint empty_vector;
//		this->M_rev.push_back(empty_vector);
//	}
//
//	for (uint i = 0; i < this->M.size(); ++i){
//		for ( uint j = 0; j < this->M.at(i).size(); ++j){
//			uint index = this->M.at(i).at(j);
//			this->M_rev.at(index).push_back(i);
//		}
//	}
//}
//
//void Graph::print_vector_int(vint V){
//	for(auto const& i : V) {
//		std::cout << i << " ";
//	}
//}
//
//void Graph::print_edges(){
//	cout << "Edges :\n";
//	for(auto const& vint : this->M) {
//		print_vector_int(vint),	cout << '\n';
//	}
//}
//
//void Graph::print_edges_transposed(){
//	cout << "Edges transposed:\n";
//	for(auto const& vint : this->M_rev) {
//		print_vector_int(vint),	cout << '\n';
//	}
//}
//
//void Graph::DFS(uint v){
//	this->visited[v] = true;
//	vint::iterator i;
//	for (i = this->adj[v].begin(); i != this->adj[v].end(); ++i){
//		if (!this->visited[*i])
//			this->DFS(*i);
//	}
//	this->Stack.push(v);
//}
//
//void Graph::get_finish_times(){
////	bool was_visited[this->M.size()];
////    for(uint i = 0; i < this->M.size(); i++)
////    	was_visited[i] = false;
//}
//
//void Graph::get_stack(){
//	cout << "Stack:\n";
//	stack<uint> Stack_copy(this->Stack);
//
//	while( !Stack_copy.empty() ){
//	    cout << Stack_copy.top() << '\n';
//	    Stack_copy.pop();
//	}
//}
//
//int main(){
//
//	Graph G("SCCtest.txt");
//	G.print_edges();
////	G.get_transpose();
////	G.print_edges_transposed();
////	G.DFS(0);
//	G.get_stack();
//
//
//	cout << "Finished.";
//	return 0;
//}
//
//
//////============================================================================
////// Name        : MinCut.cpp
////// Author      : Zari
////// Version     :
////// Copyright   : Your copyright notice
////// Description : Hello World in C++, Ansi-style
//////============================================================================
////
////#include <iostream>
////#include <vector>
////#include <ctime>
////#include <fstream>
////#include <string>
////#include <algorithm>
////
////using namespace std;
////
////typedef unsigned int uint;
////typedef std::vector<unsigned int> vint;
////typedef std::vector<vint> vvector;
////typedef std::vector<std::string> vstring;
////
////class Graph {
////	  void parse_input_line(string);
////	  void print_vector_int(vint);
////	  void get_random_edge();
////	  void edge_contraction();
////	  void concatinate_edges();
////	  void destroy_vertex();
////	  void destroy_self_loop();
////	  uint one_run_get_minimum_cut();
////	  void copy_graph_to_initial_state();
////	  vint N;
////	  vvector M;
////	  vint N_init;
////	  vvector M_init;
////	  struct Edge{
////	  	  uint ni1;
////	  	  uint ni2;
////	  } edge;
////
////	public:
////	  Graph(string file_name);
////	  uint get_minimum_cut(uint number_of_runs);
////	  void print_edges();
////	  void print_vertices();
////	  uint get_number_of_edges();
////	  uint get_number_of_vertices();
////};
////
////Graph::Graph(string file_name){
////
////	srand(time(0));
////
////	ifstream myfile(file_name, std::ifstream::in);
////
////	if (myfile.is_open()){
////		//std::cout << "File Opened.\n";
////		std::string line;
////		while ( getline(myfile,line) ){
////			parse_input_line(line);
////		}
////		myfile.close();
////	}
////	else{
////		perror("Unable to open file. Error");
////	}
////}
////
////
////void Graph::parse_input_line(std::string line){
////
////	const  std::string delimiter = "\t";
////	// first element is vertex number
////	size_t pos = line.find(delimiter);
////	{
////		const std::string str_int = line.substr(0, pos);
////		line.erase(0, pos + delimiter.length());
////		const uint integer = atoi(str_int.c_str());
////		// count vertices from zero
////		this->N_init.push_back(integer-1);
////	}
////
////	vint edges;
////	while ( (pos = line.find(delimiter)) != std::string::npos){
////		const std::string str_int = line.substr(0, pos);
////		line.erase(0, pos + delimiter.length());
////		const uint integer = atoi(str_int.c_str());
////		// index vertices from zero
////		edges.push_back(integer-1);
////	}
////	this->M_init.push_back(edges);
////
////	this->copy_graph_to_initial_state();
////}
////
////void Graph::copy_graph_to_initial_state(){
////	this->N = this->N_init;
////	this->M = this->M_init;
////}
//
////uint Graph::get_number_of_edges(){
////	uint m = 0;
////	for (auto const &Vm : this->M){
////		m = m + Vm.size();
////	}
////	return m/2;
////}
////
////uint Graph::get_number_of_vertices(){
////	return this->N.size();
////}
////
////void Graph::get_random_edge(){
////
////	const uint vert1_index = rand() % this->get_number_of_vertices();
////	const uint vert1_number = vert1_index;
////
////	const uint vert2_index = rand() % this->M.at(vert1_index).size();
////	const uint vert2_number = this->M.at(vert1_index).at(vert2_index);
////
////
////	// for convenience it is assumed that ni1 is smaller
////
////	if ( vert1_number < vert2_number ){
////		this->edge.ni1 = vert1_number;
////		this->edge.ni2 = vert2_number;
////	}
////	else{
////		this->edge.ni1 = vert2_number;
////		this->edge.ni2 = vert1_number;
////	}
////}
////
////void Graph::concatinate_edges(){
////
////	const vint edges_n2(this->M.at(this->edge.ni2));
////	this->M.at(this->edge.ni1).insert(this->M.at(this->edge.ni1).end(), edges_n2.begin(), edges_n2.end() );
////}
////
////void Graph::destroy_vertex(){
////
////	const uint vertex_number_that_is_left = this->N.at(this->edge.ni1);
////	const uint vertex_number_to_destroy = this->N.at(this->edge.ni2);
////
////	// if edge points to destroyed vertex, change the pointing to the combined vertex
////	for (uint i = 0; i < this->M.size(); i++){
////		for (uint j = 0; j < this->M[i].size(); j++){
////			if (this->M[i].at(j) == vertex_number_to_destroy)
////				this->M[i].at(j) = vertex_number_that_is_left;
////		}
////	}
////
////	// change the number of the vertex in M
////	for (uint i = 0; i < this->M.size(); i++){
////		for (uint j = 0; j < this->M[i].size(); j++){
////			if (this->M[i].at(j) > vertex_number_to_destroy)
////				this->M[i].at(j) = this->M[i].at(j) - 1;
////		}
////	}
////
////	// change the number of the vertex in N
////	for (uint i = vertex_number_to_destroy+1; i < this->N.size(); i++){
////		this->N.at(i) = this->N.at(i) - 1;
////	}
////
////	// erase from N and M vectors
////	this->N.erase(this->N.begin() + this->edge.ni2);
////	this->M.erase(this->M.begin() + this->edge.ni2);
////}
////
////void Graph::destroy_self_loop(){
////
////	for (uint i = 0; i < this->M.size(); i++){
////		for (uint j = 0; j < this->M[i].size(); j++){
////			const vint::iterator iterators_to_remove = remove(this->M.at(i).begin(), this->M.at(i).end(), this->N.at(i));
////			this->M.at(i).erase(iterators_to_remove, this->M.at(i).end());
////		}
////	}
////}
////
////void Graph::edge_contraction(){
////	this->get_random_edge();
////	this->concatinate_edges();
////	this->destroy_vertex();
////	this->destroy_self_loop();
////}
////
////uint Graph::one_run_get_minimum_cut(){
////
////	while (this->get_number_of_vertices() > 2){
////		this->edge_contraction();
////	}
////
////	return this->get_number_of_edges();
////}
////
////uint Graph::get_minimum_cut(uint number_of_runs){
////
////	uint min_cut = this->get_number_of_edges();
////
////	for (uint i = 0; i < number_of_runs; i++){
////		this->copy_graph_to_initial_state();
////		const uint cut_number = this->one_run_get_minimum_cut();
////		if (cut_number < min_cut)
////			min_cut = cut_number;
////	}
////
////	return min_cut;
////}
////
////int main() {
////
////	Graph G("kargerMinCut.txt");
////	cout << "Minimum cut is: " << G.get_minimum_cut(10);
////
////	return 0;
////}
//
//

