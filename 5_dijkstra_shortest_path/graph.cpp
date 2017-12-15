#include "graph.h"

using namespace std;

Graph::Graph(unsigned int number_of_vertices) :
    _number_of_vertices(number_of_vertices)
{
    _edges = new vector<vector<Graph::Edge> >( _number_of_vertices, vector<Edge>(0) );
}

void Graph::print()
{
    cout << "Edges :\n";
    for (unsigned int i = 0; i<_number_of_vertices; ++i){
        unsigned int len = (_edges->at(i)).size();
        for (unsigned int j = 0; j<len; ++j){
            cout << ((_edges->at(i)).at(j)).m_head << "," << ((_edges->at(i)).at(j)).m_cost << " ";
        }
        cout << endl;
    }
}

unsigned int Graph::getShortestPathVertex(const vector<unsigned int>& dist, const vector<unsigned int>& unvisited){

    unsigned int shortest_path = 1000000;
    unsigned int shortest_index = 0;

    for (unsigned int i = 0; i < unvisited.size(); ++i){
        unsigned int j = unvisited[i];
        if (dist[j] < shortest_path){
            shortest_path = dist[j];
            shortest_index = j;
        }
    }

    return shortest_index;
}

unsigned int Graph::get_shortest_path(unsigned int s, unsigned int e){

    vector<unsigned int> unvisited(_number_of_vertices);// = new vector<unsigned int>[V];
    vector<unsigned int> dist(_number_of_vertices);// = new vector<unsigned int>[V];

    for (unsigned int i = 0; i < _number_of_vertices; ++i){
        unvisited[i] = i;
        dist[i] = 1000000;
    }

    // starting vertex
    dist[s] = 0;

    while (unvisited.size() != 0){
        unsigned int u = getShortestPathVertex(dist, unvisited);
//		cout << "Shortest path vertex is : " << u << endl;
        vector<Edge> adjecent ( (*_edges).at(u) );

//		cout << "Unvisited size: " << unvisited.size() << endl;
        unsigned int index_to_delete = find(unvisited.begin(), unvisited.end(), u) - unvisited.begin();
        unvisited.erase(unvisited.begin() + index_to_delete);
//		cout << "Delete element of unvisited\nUnvisited size: " << unvisited.size() << endl;

        for (unsigned int i = 0; i < adjecent.size(); ++i){
            Edge edge = adjecent[i];
            if (dist[edge.m_head] > dist[u] + edge.m_cost){
                dist[edge.m_head] = dist[u] + edge.m_cost;
            }
        }
    }

    return dist[e];

}

//Graph::Graph()
//{

//}

//Graph::Graph(const Graph &graph)
//{
//    for (const auto& vertex : graph.N)
//        N.push_back(vertex);

//    for (const auto& vector_of_vertices : graph.M)
//        M.push_back(vector_of_vertices);
//}

//Graph& Graph::operator=( const Graph& graph )
//{
//    N.clear();
//    M.clear();

//    for (const auto& vertex : graph.N)
//        N.push_back(vertex);

//    for (const auto& vector_of_vertices : graph.M)
//        M.push_back(vector_of_vertices);

//    return *this;
//}

//uint Graph::getNumberOfEdges()
//{
//    unsigned int number_of_edges = 0;
//    for (auto const &edges_container : this->M)
//        number_of_edges += edges_container.size();

//    // each edge was counted twice
//    return number_of_edges / 2;
//}

//unsigned int Graph::getNumberOfVertices()
//{
//    return N.size();
//}

//void Graph::addNewVertex(unsigned int vertex_number)
//{
//    N.push_back(vertex_number);
//}

//void Graph::addNewVectorOfVertices(std::vector<unsigned int>& edge_vertices)
//{
//    M.push_back(edge_vertices);
//}

//void Graph::printVector(std::vector<unsigned int> data)
//{
//    for(auto const& element : data) {
//        std::cout << element << " ";
//    }
//}

//void Graph::printEdges()
//{
//    cout << "Edges :\n";
//    for(auto const& vint : this->M) {
//        printVector(vint),	cout << '\n';
//    }
//}

//void Graph::printVertices()
//{
//    cout << "Vertices :\n";
//    for(auto const& n : this->N) {
//        std::cout << n << " ";
//    }
//    cout << "\n";
//}

//unsigned int Graph::getNumberOfEdgesFromVertex(unsigned int vertex_index)
//{
//    return M.at(vertex_index).size();
//}

//unsigned int Graph::getVertexNumber(unsigned int row_index, unsigned int column_index)
//{
//    return M.at(row_index).at(column_index);
//}

//unsigned int Graph::getVertexNumber(unsigned int vertices_list_index)
//{
//    return N.at(vertices_list_index);
//}

//void Graph::setVertexNumber(unsigned int row_index, unsigned int column_index, unsigned int new_value)
//{
//    M.at(row_index).at(column_index) = new_value;
//}

//void Graph::removeVertexFromGraph(const Graph::Vertex& vertex)
//{
//    N.erase(N.begin() + vertex.index);
//    M.erase(M.begin() + vertex.index);
//}

//std::vector<unsigned int> Graph::getVerticesConnectedToVertexOfIndex(unsigned int vertex_index)
//{
//    return M.at(vertex_index);
//}

//void Graph::attachVerticesToVertexOfIndex(const std::vector<unsigned int>& vertices_to_attach, unsigned int vertex_index)
//{
//    M.at(vertex_index).insert(M.at(vertex_index).end(), vertices_to_attach.begin(), vertices_to_attach.end() );
//}

//void Graph::destroySelfLoops()
//{
//    for (unsigned int i = 0; i < getNumberOfVertices(); i++)
//    {
//        for (unsigned int j = 0; j < getNumberOfEdgesFromVertex(i); j++)
//        {
//            std::vector<unsigned int>::iterator iterators_to_remove = remove(M.at(i).begin(), M.at(i).end(), N.at(i));
//            M.at(i).erase(iterators_to_remove, M.at(i).end());
//        }
//    }
//}

