#ifndef CALCULATEDIJKSTRASHORTESTPATH_H
#define CALCULATEDIJKSTRASHORTESTPATH_H

#include "graph.h"
#include <vector>

class CalculateDijkstraShortestPath
{
    static const unsigned int _PATH_INITIAL_VALUE = 1000000;
    static unsigned int get_shortest_path_vertex(const std::vector<unsigned int>& dist, const std::vector<unsigned int>& unvisited);
public:
    static unsigned int compute_shortest_path_value(Graph& graph, unsigned int star_vertex_index, unsigned int end_vertex_index);
};

#endif // CALCULATEDIJKSTRASHORTESTPATH_H
