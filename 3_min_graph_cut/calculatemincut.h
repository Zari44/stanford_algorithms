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
    static void attachVerticesOfDestroyedVertexToSavedVertex(Graph& graph, Graph::Vertex& vertex_to_destroy, Graph::Vertex& vertex_to_save);
    static void destroyVertex(Graph& graph, Graph::Vertex& vertex_to_destory);
    static void destroySelfLoops(Graph& graph);
    static Graph::Vertex getRandomVertex(Graph& graph);
    static Graph::Vertex getRandomVertexConnectedToVertex(Graph& graph, const Graph::Vertex& adjecent_vertex);
    static void createEdgeWithCorrectVerticesOrder(Graph::Edge& edge, const Graph::Vertex& vertex1, const Graph::Vertex& vertex2);
    static void reatechEdgesFromDestroyedVertexToTheVertexThatIsLeft(Graph& graph, const Graph::Vertex& vertex_to_destroy, const Graph::Vertex& vertex_that_is_left);

public:
//    CalculateMinCut();
    static unsigned int calculate_min_cut(Graph& graph, unsigned int iterations);
};

#endif // CALCULATEMINCUT_H
