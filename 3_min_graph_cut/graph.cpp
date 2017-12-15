#include "graph.h"

Graph::Graph()
{

}

Graph::Graph(const Graph &graph)
{
    for (const auto& vertex : graph.N)
        N.push_back(vertex);

    for (const auto& vector_of_vertices : graph.M)
        M.push_back(vector_of_vertices);
}

Graph& Graph::operator=( const Graph& graph )
{
    N.clear();
    M.clear();

    for (const auto& vertex : graph.N)
        N.push_back(vertex);

    for (const auto& vector_of_vertices : graph.M)
        M.push_back(vector_of_vertices);

    return *this;
}

uint Graph::getNumberOfEdges()
{
    unsigned int number_of_edges = 0;
    for (auto const &edges_container : this->M)
        number_of_edges += edges_container.size();

    // each edge was counted twice
    return number_of_edges / 2;
}

unsigned int Graph::getNumberOfVertices()
{
    return N.size();
}

void Graph::addNewVertex(unsigned int vertex_number)
{
    N.push_back(vertex_number);
}

void Graph::addNewVectorOfVertices(std::vector<unsigned int>& edge_vertices)
{
    M.push_back(edge_vertices);
}

void Graph::printVector(std::vector<unsigned int> data)
{
    for(auto const& element : data) {
        std::cout << element << " ";
    }
}

void Graph::printEdges()
{
    cout << "Edges :\n";
    for(auto const& vint : this->M) {
        printVector(vint),	cout << '\n';
    }
}

void Graph::printVertices()
{
    cout << "Vertices :\n";
    for(auto const& n : this->N) {
        std::cout << n << " ";
    }
    cout << "\n";
}

unsigned int Graph::getNumberOfEdgesFromVertex(unsigned int vertex_index)
{
    return M.at(vertex_index).size();
}

unsigned int Graph::getVertexNumber(unsigned int row_index, unsigned int column_index)
{
    return M.at(row_index).at(column_index);
}

unsigned int Graph::getVertexNumber(unsigned int vertices_list_index)
{
    return N.at(vertices_list_index);
}

void Graph::setVertexNumber(unsigned int row_index, unsigned int column_index, unsigned int new_value)
{
    M.at(row_index).at(column_index) = new_value;
}

void Graph::removeVertexFromGraph(const Graph::Vertex& vertex)
{
    N.erase(N.begin() + vertex.index);
    M.erase(M.begin() + vertex.index);
}

std::vector<unsigned int> Graph::getVerticesConnectedToVertexOfIndex(unsigned int vertex_index)
{
    return M.at(vertex_index);
}

void Graph::attachVerticesToVertexOfIndex(const std::vector<unsigned int>& vertices_to_attach, unsigned int vertex_index)
{
    M.at(vertex_index).insert(M.at(vertex_index).end(), vertices_to_attach.begin(), vertices_to_attach.end() );
}

void Graph::destroySelfLoops()
{
    for (unsigned int i = 0; i < getNumberOfVertices(); i++)
    {
        for (unsigned int j = 0; j < getNumberOfEdgesFromVertex(i); j++)
        {
            std::vector<unsigned int>::iterator iterators_to_remove = remove(M.at(i).begin(), M.at(i).end(), N.at(i));
            M.at(i).erase(iterators_to_remove, M.at(i).end());
        }
    }
}

