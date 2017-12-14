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
      unsigned int getMinimumCut(unsigned int number_of_runs);
      unsigned int getNumberOfEdges();
      unsigned int getNumberOfVertices();
      unsigned int getMinimumCutOneIteration();
      std::vector<unsigned int> N; //vertices
      std::vector<std::vector<unsigned int> > M;//edges
      struct Edge;/*{
          unsigned int ni1;
          unsigned int ni2;
      };*/
    private:
      void printVectorInt(std::vector<unsigned int>);
      void contractEdge();
      void concatinateEdges();
      void destroyVertex();
      void destroySelfLoop();
      void getRandomEdge();

};

struct Graph::Edge{
    unsigned int ni1;
    unsigned int ni2;
};

#endif // GRAPH_H
