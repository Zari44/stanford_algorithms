// C++ Implementation of Kosaraju's algorithm to print all SCCs
#include <iostream>
#include <list>
#include <stack>


#include <vector>
#include <fstream>
#include <string>
#include <algorithm> //find()
#include <stdio.h>

#include "inputfilereader.h"
#include "graph.h"

using namespace std;

//class Graph
//{
//    int _number_of_vertices;
//    list<int> *adj;    // An array of adjacency lists

//    // Fills Stack with vertices (in increasing order of finishing
//    // times). The top element of stack has the maximum finishing time
//    void fillOrder(int v, bool visited[], stack<int> &Stack);

//    // A recursive function to print DFS starting from v
//    unsigned int DFS(int v, bool visited[], unsigned int scc);
//    void parseInputLine(std::string& line);
//    void getVerticesInLine(unsigned int&, unsigned int&, std::string);
//public:
//    Graph(int _number_of_vertices);
//    Graph(string file_name, int _number_of_vertices);
//    void addEdge(int v, int w);

//    // The main function that finds and prints strongly connected
//    // components
//    void printSCCs();

//    // Function that returns reverse (or transpose) of this graph
//    Graph getTranspose();
//};

//Graph::Graph(int number_of_verices)
//    :   _number_of_vertices(number_of_verices)
//{
//    adj = new list<int>[_number_of_vertices];
//}

//Graph::Graph(string file_name, int V)
//{
//	ifstream myfile(file_name, std::ifstream::in);

//    if (myfile.is_open())
//    {
//		string line;
//        this->_number_of_vertices = V;
//		adj = new list<int>[V];

//        while ( getline(myfile,line) )
//            parseInputLine(line);

//        cout << "Finished reading file" << endl;
//		myfile.close();
//		cout << "File closed" << endl;
//	}
//    else
//		perror("Error: Unable to open file.");
//}

//void Graph::getVerticesInLine(unsigned int& out_a, unsigned int& out_b, std::string line)
//{
//	const string delimiter = " ";
//	size_t pos = line.find(delimiter);

//	string str_int = line.substr(0, pos);
//	out_a = atoi(str_int.c_str());
//	line.erase(0, pos + delimiter.length());

//	pos = line.find(delimiter);
//	str_int = line.substr(0, pos);
//	out_b = atoi(str_int.c_str());
//}

//void Graph::parseInputLine(std::string& line)
//{

//	const string delimiter = " ";
//	size_t pos = line.find(delimiter);

//	string str_int = line.substr(0, pos);
//	const unsigned int tail = atoi(str_int.c_str())-1;
//	line.erase(0, pos + delimiter.length());

//	pos = line.find(delimiter);
//	str_int = line.substr(0, pos);
//	const unsigned int head = atoi(str_int.c_str())-1;

//    adj[tail].push_back(head); // Add head to tails’s list.

//    if (tail % 100000 == 0)
//    	cout << "tail: " << tail << endl;
////	while (this->M.size() <= tail){
////		vector<unsigned int> empty_vector;
//////		this->M.push_back(empty_vector);
////		adj.push_back(empty_vector);
////	}
////	this->M.at(tail).push_back(head);
////
////	while (this->M.size() <= head){
////		vector<unsigned int> empty_vector;
////		this->M.push_back(empty_vector);
////	}
//}

//// A recursive function to print DFS starting from v
//unsigned int Graph::DFS(int v, bool visited[], unsigned int scc)
//{
//    // Mark the current node as visited and print it
//    visited[v] = true;
//    cout << v << " ";
//    scc++;
////    cout << adj[v] << endl;
//    // Recur for all the vertices adjacent to this vertex
//    list<int>::iterator i;
//    for (i = adj[v].begin(); i != adj[v].end(); ++i)
//        if (!visited[*i])
//            scc = DFS(*i, visited, scc);

//    return scc;
//}

//Graph Graph::getTranspose()
//{
//    Graph g(_number_of_vertices);
//    for (int v = 0; v < _number_of_vertices; v++){
//        // Recur for all the vertices adjacent to this vertex
//        list<int>::iterator i;
//        for(i = adj[v].begin(); i != adj[v].end(); ++i){
//            g.adj[*i].push_back(v);
//        }
//    }
//    return g;
//}

//void Graph::addEdge(int v, int w)
//{
//    adj[v].push_back(w); // Add w to v’s list.
//}

//void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
//{
//    // Mark the current node as visited and print it
//    visited[v] = true;

//    // Recur for all the vertices adjacent to this vertex
//    list<int>::iterator i;
//    for(i = adj[v].begin(); i != adj[v].end(); ++i)
//        if(!visited[*i])
//            fillOrder(*i, visited, Stack);

//    // All vertices reachable from v are processed by now, push v
//    Stack.push(v);
//}

//// The main function that finds and prints all strongly connected
//// components
//void Graph::printSCCs()
//{
//    stack<int> Stack;
//    ofstream outputfile;
//    outputfile.open("output.txt");

//    // Mark all the vertices as not visited (For first DFS)
//    bool *visited = new bool[_number_of_vertices];
//    for(int i = 0; i < _number_of_vertices; i++)
//        visited[i] = false;

//    // Fill vertices in stack according to their finishing times
//    for(int i = 0; i < _number_of_vertices; i++)
//        if(visited[i] == false)
//            fillOrder(i, visited, Stack);

//    // Create a reversed graph
//    Graph gr = getTranspose();

//    // Mark all the vertices as not visited (For second DFS)
//    for(int i = 0; i < _number_of_vertices; i++)
//        visited[i] = false;

//    // Now process all vertices in order defined by Stack
//    while (Stack.empty() == false)
//    {
//        // Pop a vertex from stack
//        int v = Stack.top();
//        Stack.pop();

//        // Print Strongly connected component of the popped vertex
//        if (visited[v] == false)
//        {
//        	unsigned int scc = 0;
//            scc = gr.DFS(v, visited, scc);
//            cout << endl;
//            outputfile << scc << endl;
//        }
//    }
//    outputfile.close();
//    cout << "Output file closed\n";
//}

void sort_output()
{
	ifstream inputfile("output.txt");

	string line;

	list<unsigned int> num_list;

	unsigned int num;
    while (inputfile >> num)
    {
        if (num > 1)
			num_list.push_back(num);
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
    Graph graph(5);
    InputFileReader::open_and_read_input_data_file("SCCtest.txt", graph);
//    Graph graph("SCCtest.txt", 5);

    cout << "Following are strongly connected components in "
            "given graph \n";

    graph.printSCCs();

	cout << "sorting started\n";
    sort_output();
	cout << "sorting finished\n";

    return 0;
}


