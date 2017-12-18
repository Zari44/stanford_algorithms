#include "graph.h"

Graph::Graph(int number_of_verices)
    :   _number_of_vertices(number_of_verices)
{
    adjacency = new vector<int>[_number_of_vertices];
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

// new:



// A recursive function to print DFS starting from v
unsigned int Graph::DFS(int starting_vertex_index, bool visited[], unsigned int scc)
{
    // Mark the current node as visited and print it
    visited[starting_vertex_index] = true;
    cout << starting_vertex_index << " ";
    ++scc;

    // Recur for all the vertices adjacent to this vertex
    for (vector<int>::iterator vertex_index = adjacency[starting_vertex_index].begin(); vertex_index != adjacency[starting_vertex_index].end(); ++vertex_index)
        if (!visited[*vertex_index])
            scc = DFS(*vertex_index, visited, scc);

    return scc;
}

Graph Graph::getTranspose()
{
    Graph graph(_number_of_vertices);
    for (int vertex_index = 0; vertex_index < _number_of_vertices; ++vertex_index){
        // Recur for all the vertices adjacent to this vertex
        for(vector<int>::iterator i = adjacency[vertex_index].begin(); i != adjacency[vertex_index].end(); ++i){
            graph.adjacency[*i].push_back(vertex_index);
        }
    }
    return graph;
}

void Graph::addEdge(int tail, int head)
{
    adjacency[tail].push_back(head);
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    vector<int>::iterator i;
    for(i = adjacency[v].begin(); i != adjacency[v].end(); ++i)
        if(!visited[*i])
            fillOrder(*i, visited, Stack);

    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}

// The main function that finds and prints all strongly connected
// components
void Graph::printSCCs()
{
    stack<int> Stack;
    ofstream outputfile;
    outputfile.open("output.txt");

    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[_number_of_vertices];
    for(int i = 0; i < _number_of_vertices; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < _number_of_vertices; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);

    // Create a reversed graph
    Graph gr = getTranspose();

    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < _number_of_vertices; i++)
        visited[i] = false;

    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            unsigned int scc = 0;
            scc = gr.DFS(v, visited, scc);
            cout << endl;
            outputfile << scc << endl;
        }
    }
    outputfile.close();
    cout << "Output file closed\n";
}


