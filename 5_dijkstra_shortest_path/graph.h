#ifndef GRAPH_H
#define GRAPH_H

//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <fstream>
//#include <string>
//#include <algorithm>

//using namespace std;

//class Graph
//{
//public:
//    struct Vertex;
//    struct Edge;
//      Graph();
//      Graph copy();
//      Graph(const Graph& graph);
////      void copyGraphToInitialState();
//      Graph& operator=( const Graph& graph );
//      void addNewVertex(unsigned int vertex_number);
//      void addNewVectorOfVertices(std::vector<unsigned int>& edge_vertices);
//      void removeVertexFromGraph(const Graph::Vertex& vertex);
//      void attachVerticesToVertexOfIndex(const std::vector<unsigned int>& vertices_to_attach, unsigned int vertex_index);
//      std::vector<unsigned int>  getVerticesConnectedToVertexOfIndex(unsigned int vertex_index);
//      unsigned int getNumberOfEdgesFromVertex(unsigned int vertex_index);
//      unsigned int getVertexNumber(unsigned int row_index, unsigned int column_index);
//      unsigned int getVertexNumber(unsigned int vertices_list_index);
//      unsigned int getNumberOfEdges();
//      unsigned int getNumberOfVertices();
//      unsigned int getMinimumCutOneIteration();
//      void setVertexNumber(unsigned int row_index, unsigned int column_index, unsigned int new_value);
//      void printEdges();
//      void printVertices();
//      void destroySelfLoops();
//    private:
//      std::vector<unsigned int> N; //vertices
//      std::vector<std::vector<unsigned int> > M;//edges
//      void printVector(std::vector<unsigned int> vector);
//};

//struct Graph::Vertex{
//    unsigned int index;
//    unsigned int number;
//};

//struct Graph::Edge{
//    Graph::Vertex vertex1;
//    Graph::Vertex vertex2;
//};

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>     /* atoi */
#include <algorithm>

class Graph
{
    private:
        unsigned int _number_of_vertices;
        unsigned int getShortestPathVertex(const std::vector<unsigned int>& dist, const std::vector<unsigned int>& unvisited);
    public:
        struct Edge;
        Graph(unsigned int number_of_vertices);
        std::vector<std::vector<Edge> > *_edges;
        void print();
        unsigned int computeShortestPath(unsigned int start, unsigned int end);
        unsigned int getNumberOfVertices();// { return _number_of_vertices; }
        std::vector<Graph::Edge> getVerticesAdjecentToVertexOfIndex(unsigned int vertex_index);

};

struct Graph::Edge
{
    unsigned int m_head;
    unsigned int m_cost;
};


#endif // GRAPH_H
