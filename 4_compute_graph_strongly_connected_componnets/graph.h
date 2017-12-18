#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

class Graph
{
public:
    struct Vertex;
    struct Edge;
      Graph();
      Graph copy();
      Graph(const Graph& graph);
//      void copyGraphToInitialState();
      Graph& operator=( const Graph& graph );
      void addNewVertex(unsigned int vertex_number);
      void addNewVectorOfVertices(std::vector<unsigned int>& edge_vertices);
      void removeVertexFromGraph(const Graph::Vertex& vertex);
      void attachVerticesToVertexOfIndex(const std::vector<unsigned int>& vertices_to_attach, unsigned int vertex_index);
      std::vector<unsigned int>  getVerticesConnectedToVertexOfIndex(unsigned int vertex_index);
      unsigned int getNumberOfEdgesFromVertex(unsigned int vertex_index);
      unsigned int getVertexNumber(unsigned int row_index, unsigned int column_index);
      unsigned int getVertexNumber(unsigned int vertices_list_index);
      unsigned int getNumberOfEdges();
      unsigned int getNumberOfVertices();
      unsigned int getMinimumCutOneIteration();
      void setVertexNumber(unsigned int row_index, unsigned int column_index, unsigned int new_value);
      void printEdges();
      void printVertices();
      void destroySelfLoops();
      // new:
      Graph(int _number_of_vertices);
      Graph(string file_name, int _number_of_vertices);
      void addEdge(int v, int w);

      // The main function that finds and prints strongly connected
      // components
      void printSCCs();

      // Function that returns reverse (or transpose) of this graph
      Graph getTranspose();
      vector<int> *adj;    // An array of adjacency lists
    private:
      std::vector<unsigned int> N; //vertices
      std::vector<std::vector<unsigned int> > M;//edges
      void printVector(std::vector<unsigned int> vector);

      // new:
      int _number_of_vertices;


      // Fills Stack with vertices (in increasing order of finishing
      // times). The top element of stack has the maximum finishing time
      void fillOrder(int v, bool visited[], stack<int> &Stack);

      // A recursive function to print DFS starting from v
      unsigned int DFS(int v, bool visited[], unsigned int scc);
      void parseInputLine(std::string& line);
      void getVerticesInLine(unsigned int&, unsigned int&, std::string);
};

struct Graph::Vertex{
    unsigned int index;
    unsigned int number;
};

struct Graph::Edge{
    Graph::Vertex vertex1;
    Graph::Vertex vertex2;
};



#endif // GRAPH_H
