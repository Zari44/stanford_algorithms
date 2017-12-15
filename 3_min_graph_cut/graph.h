#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Graph
{
public:
      Graph();
      Graph copy();
      void copyGraphToInitialState();
      Graph& operator=( const Graph& graph );
      struct Vertex;
      struct Edge;
      std::vector<unsigned int> N_init; //vertices
      std::vector<std::vector<unsigned int> > M_init; //edges
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

    private:
      std::vector<unsigned int> N; //vertices
      std::vector<std::vector<unsigned int> > M;//edges
      void printVector(std::vector<unsigned int> vector);


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
