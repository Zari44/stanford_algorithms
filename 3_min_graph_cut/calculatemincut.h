#ifndef CALCULATEMINCUT_H
#define CALCULATEMINCUT_H

#include "graph.h"
//class Graph;
//struct Graph::Edge;

class CalculateMinCut
{
    static unsigned int getMinimumCutOneIteration(Graph& graph);
    static bool ifThereAreMoreThanTwoVertices(unsigned int number_of_vertices);
    static Graph::Edge getRandomEdge(Graph& graph);
    static void contractEdge(Graph& graph, Graph::Edge& edge);
    static void concatinateEdges(Graph& graph, Graph::Edge& edge);
    static void destroyVertex(Graph& graph, Graph::Edge& edge);
    static void destroySelfLoop(Graph& graph);
public:
//    CalculateMinCut();
    static unsigned int calculate_min_cut(Graph& graph, unsigned int iterations);
};

#endif // CALCULATEMINCUT_H
