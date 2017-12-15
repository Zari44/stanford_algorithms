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
      Graph& operator=( const Graph& graph );
      std::vector<unsigned int> N_init; //vertices
      std::vector<std::vector<unsigned int> > M_init; //edges
      void copyGraphToInitialState();
      void printEdges();
      void printVertices();
      unsigned int getNumberOfEdges();
      unsigned int getNumberOfVertices();
      unsigned int getMinimumCutOneIteration();
      std::vector<unsigned int> N; //vertices
      std::vector<std::vector<unsigned int> > M;//edges
      struct Edge;
      struct Vertex;
      unsigned int getNumberOfEdgesFromVertex(unsigned int vertex_index);
      unsigned int getVertexNumber(unsigned int row_index, unsigned int column_index);
      unsigned int getVertexNumber(unsigned int vertices_list_index);
      void setVertexNumber(unsigned int row_index, unsigned int column_index, unsigned int new_value);
    private:
      void printVectorInt(std::vector<unsigned int>);

};

struct Graph::Edge{
    unsigned int ni1;
    unsigned int ni2;
};

struct Graph::Vertex{
    unsigned int index;
    unsigned int number;
};

#endif // GRAPH_H
