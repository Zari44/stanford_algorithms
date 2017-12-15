#include "calculatedijkstrashortestpath.h"
#include "graph.h"
#include <algorithm>
using namespace std;

unsigned int CalculateDijkstraShortestPath::get_shortest_path_vertex(const std::vector<unsigned int>& dist, const std::vector<unsigned int>& unvisited)
{
    unsigned int shortest_path_value = _PATH_INITIAL_VALUE;
    unsigned int shortest_vertex_index = 0;

    for (unsigned int i = 0; i < unvisited.size(); ++i)
    {
        unsigned int vertex_index = unvisited[i];
        if (dist[vertex_index] < shortest_path_value)
        {
            shortest_path_value = dist[vertex_index];
            shortest_vertex_index = vertex_index;
        }
    }

    return shortest_vertex_index;
}


unsigned int CalculateDijkstraShortestPath::compute_shortest_path_value(Graph& graph, unsigned int star_vertex_index, unsigned int end_vertex_index)
{
    vector<unsigned int> unvisited(graph.getNumberOfVertices());
    vector<unsigned int> dist(graph.getNumberOfVertices());

    for (unsigned int i = 0; i < graph.getNumberOfVertices(); ++i)
    {
        unvisited[i] = i;
        dist[i] = _PATH_INITIAL_VALUE;
    }

    // starting vertex
    dist[star_vertex_index] = 0;

    while (unvisited.size() != 0)
    {
        unsigned int vertex_index = get_shortest_path_vertex(dist, unvisited);
//        vector<Graph::Edge> adjecent_vertices( _edges->at(vertex_index) );
        vector<Graph::Edge> adjecent_vertices = graph.getVerticesAdjecentToVertexOfIndex(vertex_index);

        unsigned int index_to_delete = find(unvisited.begin(), unvisited.end(), vertex_index) - unvisited.begin();
        unvisited.erase(unvisited.begin() + index_to_delete);

        for (unsigned int i = 0; i < adjecent_vertices.size(); ++i)
        {
            Graph::Edge edge = adjecent_vertices[i];
            if (dist[edge.m_head] > dist[vertex_index] + edge.m_cost)
                dist[edge.m_head] = dist[vertex_index] + edge.m_cost;
        }
    }

    return dist[end_vertex_index];

}
