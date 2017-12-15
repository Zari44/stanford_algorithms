#include "calculatemincut.h"
#include "graph.h"

#include <iostream>
#include <algorithm>

unsigned int CalculateMinCut::calculate_min_cut(Graph& graph, unsigned int iterations)
{
    srand(time(0));
    unsigned int min_cut = graph.getNumberOfEdges();

    Graph graph_copy;
    for (unsigned int i = 0; i < iterations; i++)
    {
        graph_copy = graph;
        findNewMinCut(min_cut, getMinimumCutOneIteration(graph_copy));
    }

    std::cout << "Vertices numbers: " << graph_copy.getVertexNumber(0) << ", " << graph_copy.getVertexNumber(1) << std::endl;

    return min_cut;
}

unsigned int CalculateMinCut::findNewMinCut(unsigned int& min_cut, unsigned int cut_number)
{
    if (cut_number < min_cut)
        min_cut = cut_number;
}

unsigned int CalculateMinCut::getMinimumCutOneIteration(Graph& graph)
{
    while ( ifThereAreMoreThanTwoVertices( graph.getNumberOfVertices() ) )
    {
        Graph::Edge edge = getRandomEdge(graph);
        contractEdge(graph, edge);
    }

    return graph.getNumberOfEdges();
}

bool CalculateMinCut::ifThereAreMoreThanTwoVertices(unsigned int number_of_vertices)
{
    return number_of_vertices > 2;
}

Graph::Edge CalculateMinCut::getRandomEdge(Graph& graph)
{
    Graph::Edge edge;
    edge.vertex1 = CalculateMinCut::getRandomVertex(graph);
    edge.vertex2 = CalculateMinCut::getRandomVertexConnectedToVertex(graph, edge.vertex1);

    return edge;
}

Graph::Vertex CalculateMinCut::getRandomVertex(Graph& graph)
{
    Graph::Vertex vertex;
    vertex.index = rand() % graph.getNumberOfVertices();
    vertex.number = graph.getVertexNumber(vertex.index);

    return vertex;
}

Graph::Vertex CalculateMinCut::getRandomVertexConnectedToVertex(Graph& graph, const Graph::Vertex& adjecent_vertex)
{
    unsigned int vertex_index_in_edge_array = rand() % graph.getNumberOfEdgesFromVertex(adjecent_vertex.index);
    unsigned int vertex_number_in_graph = graph.getVertexNumber(adjecent_vertex.index, vertex_index_in_edge_array);

    Graph::Vertex vertex;
    for (unsigned int i = 0; i < graph.getNumberOfVertices(); ++i)
    {
        if (graph.getVertexNumber(i) == vertex_number_in_graph)
        {
            vertex.index = i;
            break;
        }
    }
    vertex.number = vertex_number_in_graph;

    return vertex;
}

void CalculateMinCut::contractEdge(Graph& graph, Graph::Edge& edge)
{
    Graph::Vertex vertex_to_save = edge.vertex1;
    Graph::Vertex vertex_to_destroy = edge.vertex2;

    attachVerticesOfDestroyedVertexToSavedVertex(graph, vertex_to_destroy, vertex_to_save);
    reatechEdgesFromDestroyedVertexToTheVertexThatIsLeft(graph, vertex_to_destroy, vertex_to_save);
    destroyVertex(graph, vertex_to_destroy);
    destroySelfLoops(graph);
}

void CalculateMinCut::attachVerticesOfDestroyedVertexToSavedVertex(Graph& graph, Graph::Vertex& vertex_to_destroy, Graph::Vertex& vertex_to_save)
{
    std::vector<unsigned int> vertices_connected_to_destroyed_vertex = graph.getVerticesConnectedToVertexOfIndex(vertex_to_destroy.index);
    graph.attachVerticesToVertexOfIndex(vertices_connected_to_destroyed_vertex, vertex_to_save.index);
}

void CalculateMinCut::destroyVertex(Graph& graph, Graph::Vertex& vertex_to_destory)
{
    graph.removeVertexFromGraph(vertex_to_destory);
}

void CalculateMinCut::reatechEdgesFromDestroyedVertexToTheVertexThatIsLeft(Graph& graph, const Graph::Vertex& vertex_to_destroy, const Graph::Vertex& vertex_that_is_left)
{
    for (unsigned int i = 0; i < graph.getNumberOfVertices(); i++)
    {
        for (unsigned int j = 0; j < graph.getNumberOfEdgesFromVertex(i); j++)
        {
            if (graph.getVertexNumber(i,j) == vertex_to_destroy.number)
                graph.setVertexNumber(i,j, vertex_that_is_left.number);
        }
    }
}

void CalculateMinCut::destroySelfLoops(Graph& graph)
{
    graph.destroySelfLoops();
}
