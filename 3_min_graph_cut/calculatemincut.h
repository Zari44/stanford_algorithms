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
    static Graph::Vertex getRandomVertex(Graph& graph);
    static Graph::Vertex getRandomVertexConnectedToVertex(Graph& graph, const Graph::Vertex& adjecent_vertex);
    static void createEdgeWithCorrectVerticesOrder(Graph::Edge& edge, const Graph::Vertex& vertex1, const Graph::Vertex& vertex2);
    static void reatechEdgesFromDestroyedVertexToTheVertexThatIsLeft(Graph& graph, unsigned int vertex_number_to_destroy, unsigned int vertex_number_that_is_left);
public:
//    CalculateMinCut();
    static unsigned int calculate_min_cut(Graph& graph, unsigned int iterations);
};

#endif // CALCULATEMINCUT_H
