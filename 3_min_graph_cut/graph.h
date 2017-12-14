#ifndef GRAPH_H
#define GRAPH_H

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

class Graph
{
public:
      Graph();
      Graph copy();
      vint N_init; //vertices
      vvector M_init; //edges
      void copyGraphToInitialState();
      void printEdges();
      void printVertices();
      unsigned int getMinimumCut(unsigned int number_of_runs);
      unsigned int getNumberOfEdges();
      unsigned int getNumberOfVertices();
      unsigned int getMinimumCutOneIteration();
      vint N; //vertices
      vvector M;//edges
      struct Edge;/*{
          uint ni1;
          uint ni2;
      };*/
    private:
      void printVectorInt(vint);
      void contractEdge();
      void concatinateEdges();
      void destroyVertex();
      void destroySelfLoop();
      void getRandomEdge();

};

struct Graph::Edge{
    uint ni1;
    uint ni2;
};

#endif // GRAPH_H
