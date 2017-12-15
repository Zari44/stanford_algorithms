#include "calculatemincut.h"
#include "graph.h"

unsigned int CalculateMinCut::calculate_min_cut(Graph& graph, unsigned int iterations)
{
    unsigned int min_cut = graph.getNumberOfEdges();

    for (unsigned int i = 0; i < iterations; i++)
    {
        graph.copyGraphToInitialState();
        const unsigned int number_of_cut_edges = getMinimumCutOneIteration(graph);

        if (number_of_cut_edges < min_cut)
            min_cut = number_of_cut_edges;
    }

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
    Graph::Edge edge;

    const unsigned int vert1_index = rand() % graph.getNumberOfVertices();
    const unsigned int vert1_number = vert1_index;

    const unsigned int vert2_index = rand() % graph.M.at(vert1_index).size();
    const unsigned int vert2_number = graph.M.at(vert1_index).at(vert2_index);

    // for convenience it is assumed that ni1 is smaller

    if ( vert1_number < vert2_number )
    {
        edge.ni1 = vert1_number;
        edge.ni2 = vert2_number;
    }
    else
    {
        edge.ni1 = vert2_number;
        edge.ni2 = vert1_number;
    }

    return edge;
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

    const uint vertex_number_that_is_left = graph.N.at(edge.ni1);
    const uint vertex_number_to_destroy = graph.N.at(edge.ni2);

    // if edge points to destroyed vertex, change the pointing to the combined vertex
    for (uint i = 0; i < graph.M.size(); i++){
        for (uint j = 0; j < graph.M[i].size(); j++){
            if (graph.M[i].at(j) == vertex_number_to_destroy)
                graph.M[i].at(j) = vertex_number_that_is_left;
        }
    }

    // change the number of the vertex in M
    for (uint i = 0; i < graph.M.size(); i++){
        for (uint j = 0; j < graph.M[i].size(); j++){
            if (graph.M[i].at(j) > vertex_number_to_destroy)
                graph.M[i].at(j) = graph.M[i].at(j) - 1;
        }
    }

    // change the number of the vertex in N
    for (uint i = vertex_number_to_destroy+1; i < graph.N.size(); i++){
        graph.N.at(i) = graph.N.at(i) - 1;
    }

    // erase from N and M vectors
    graph.N.erase(graph.N.begin() + edge.ni2);
    graph.M.erase(graph.M.begin() + edge.ni2);
}

void CalculateMinCut::destroySelfLoop(Graph& graph)
{
    for (uint i = 0; i < graph.M.size(); i++){
        for (uint j = 0; j < graph.M[i].size(); j++){
            const std::vector<unsigned int>::iterator iterators_to_remove = remove(graph.M.at(i).begin(), graph.M.at(i).end(), graph.N.at(i));
            graph.M.at(i).erase(iterators_to_remove, graph.M.at(i).end());
        }
    }
}
