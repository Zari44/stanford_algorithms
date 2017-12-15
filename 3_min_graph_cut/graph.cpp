#include "graph.h"

Graph::Graph()
{

}

Graph Graph::copy()
{
//    Graph graph_copy;

//    for
}

Graph& Graph::operator=( const Graph& graph )
{
//    x = other.x;
//    c = other.c;
//    s = other.s;

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

void Graph::copyGraphToInitialState()
{
    this->N = this->N_init;
    this->M = this->M_init;
}

void Graph::printVectorInt(std::vector<unsigned int> data)
{
    for(auto const& element : data) {
        std::cout << element << " ";
    }
}

void Graph::printEdges()
{
    cout << "Edges :\n";
    for(auto const& vint : this->M) {
        printVectorInt(vint),	cout << '\n';
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
