#include "calculatemincut.h"
#include "graph.h"

#include <iostream>
#include <algorithm>

unsigned int CalculateMinCut::calculate_min_cut(Graph& graph, unsigned int iterations)
{
    srand(time(0));
    unsigned int min_cut = graph.getNumberOfEdges();

    for (unsigned int i = 0; i < iterations; i++)
    {
        graph.copyGraphToInitialState();
        const unsigned int number_of_cut_edges = getMinimumCutOneIteration(graph);

        if (number_of_cut_edges < min_cut)
            min_cut = number_of_cut_edges;
    }

    std::cout << "Vertices numbers: " << graph.getVertexNumber(0) << ", " << graph.getVertexNumber(1) << std::endl;

    return min_cut;
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

    Graph::Vertex vertex1 = CalculateMinCut::getRandomVertex(graph);
    Graph::Vertex vertex2 = CalculateMinCut::getRandomVertexConnectedToVertex(graph, vertex1);

    Graph::Edge edge;
    createEdgeWithCorrectVerticesOrder(edge, vertex1, vertex2);

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
    for (unsigned int i = 0; i < graph.N.size(); ++i)
    {
        if (graph.N.at(i) == vertex_number_in_graph)
        {
            vertex.index = i;
            break;
        }
    }
    vertex.number = vertex_number_in_graph;

    return vertex;
}

void CalculateMinCut::createEdgeWithCorrectVerticesOrder(Graph::Edge &edge, const Graph::Vertex& vertex1, const Graph::Vertex& vertex2)
{
    // for convenience it is assumed that ni1 is smaller than ni2

    if ( vertex1.number < vertex2.number )
    {
        edge.ni1 = vertex1.index;
        edge.ni2 = vertex2.index;
    }
    else
    {
        edge.ni1 = vertex2.index;
        edge.ni2 = vertex1.index;
    }
}

void CalculateMinCut::contractEdge(Graph& graph, Graph::Edge& edge)
{
    concatinateEdges(graph, edge);
    destroyVertex(graph, edge);
    destroySelfLoop(graph);
}

void CalculateMinCut::concatinateEdges(Graph& graph, Graph::Edge& edge)
{
    const std::vector<unsigned int> edges_n2(graph.M.at(edge.ni2));
    graph.M.at(edge.ni1).insert(graph.M.at(edge.ni1).end(), edges_n2.begin(), edges_n2.end() );
}

void CalculateMinCut::destroyVertex(Graph& graph, Graph::Edge& edge)
{
    const unsigned int vertex_number_that_is_left = graph.getVertexNumber(edge.ni1);
    const unsigned int vertex_number_to_destroy   = graph.getVertexNumber(edge.ni2);

    // if edge points to destroyed vertex, change the pointing to the combined vertex
    reatechEdgesFromDestroyedVertexToTheVertexThatIsLeft(graph, vertex_number_to_destroy, vertex_number_that_is_left);

//    // change the number of the vertex in M
//    for (unsigned int i = 0; i < graph.M.size(); i++)
//    {
//        for (unsigned int j = 0; j < graph.M.at(i).size(); j++)
//        {
//            if (graph.M[i].at(j) > vertex_number_to_destroy)
//                graph.M[i].at(j) = graph.M.at(i).at(j) - 1;
//        }
//    }

//    // change the number of the vertex in N
//    for (unsigned int i = vertex_number_to_destroy + 1; i < graph.N.size(); i++)
//        graph.N.at(i) = graph.N.at(i) - 1;


    // erase from N and M vectors
    graph.N.erase(graph.N.begin() + edge.ni2);
    graph.M.erase(graph.M.begin() + edge.ni2);
}

void CalculateMinCut::reatechEdgesFromDestroyedVertexToTheVertexThatIsLeft(Graph& graph, unsigned int vertex_number_to_destroy, unsigned int vertex_number_that_is_left)
{
    for (unsigned int i = 0; i < graph.getNumberOfVertices(); i++)
    {
        for (unsigned int j = 0; j < graph.getNumberOfEdgesFromVertex(i); j++)
        {
            if (graph.getVertexNumber(i,j) == vertex_number_to_destroy)
                graph.setVertexNumber(i,j,vertex_number_that_is_left);
        }
    }
}


void CalculateMinCut::destroySelfLoop(Graph& graph)
{
    for (unsigned int i = 0; i < graph.M.size(); i++)
    {
        for (unsigned int j = 0; j < graph.M.at(i).size(); j++)
        {
            const std::vector<unsigned int>::iterator iterators_to_remove = remove(graph.M.at(i).begin(), graph.M.at(i).end(), graph.N.at(i));
            graph.M.at(i).erase(iterators_to_remove, graph.M.at(i).end());
        }
    }
}
