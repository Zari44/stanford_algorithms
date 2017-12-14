#include "graph.h"

Graph::Graph()
{

}

//unsigned int Graph::getMinimumCut(unsigned int iterations)
//{
//    unsigned int min_cut = getNumberOfEdges();

//    for (unsigned int i = 0; i < iterations; i++)
//    {
//        copyGraphToInitialState();
//        const unsigned int number_of_cut_edges = this->getMinimumCutOneIteration();

//        if (number_of_cut_edges < min_cut)
//            min_cut = number_of_cut_edges;
//    }

//    return min_cut;
//}

//uint Graph::getMinimumCutOneIteration()
//{
//    while (ifThereAreMoreThanTwoVertices())
//    {

//        contractEdge();
//    }


//    return getNumberOfEdges();
//}


uint Graph::getNumberOfEdges()
{
    unsigned int number_of_edges = 0;
    for (auto const &edges_container : this->M)
        number_of_edges += edges_container.size();

    // each edge was counted twice
    return number_of_edges / 2;
}

//void Graph::contractEdge()
//{
//    this->getRandomEdge();
//    this->concatinateEdges();
//    this->destroyVertex();
//    this->destroySelfLoop();
//}

Graph Graph::copy()
{

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

void Graph::printVectorInt(vint data)
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

//void Graph::getRandomEdge()
//{
//    const uint vert1_index = rand() % this->getNumberOfVertices();
//    const uint vert1_number = vert1_index;

//    const uint vert2_index = rand() % this->M.at(vert1_index).size();
//    const uint vert2_number = this->M.at(vert1_index).at(vert2_index);

//    // for convenience it is assumed that ni1 is smaller

//    if ( vert1_number < vert2_number ){
//        this->edge.ni1 = vert1_number;
//        this->edge.ni2 = vert2_number;
//    }
//    else{
//        this->edge.ni1 = vert2_number;
//        this->edge.ni2 = vert1_number;
//    }
//}

//void Graph::concatinateEdges()
//{
//    const vint edges_n2(this->M.at(this->edge.ni2));
//    this->M.at(this->edge.ni1).insert(this->M.at(this->edge.ni1).end(), edges_n2.begin(), edges_n2.end() );
//}

//void Graph::destroyVertex()
//{

//    const uint vertex_number_that_is_left = this->N.at(this->edge.ni1);
//    const uint vertex_number_to_destroy = this->N.at(this->edge.ni2);

//    // if edge points to destroyed vertex, change the pointing to the combined vertex
//    for (uint i = 0; i < this->M.size(); i++){
//        for (uint j = 0; j < this->M[i].size(); j++){
//            if (this->M[i].at(j) == vertex_number_to_destroy)
//                this->M[i].at(j) = vertex_number_that_is_left;
//        }
//    }

//    // change the number of the vertex in M
//    for (uint i = 0; i < this->M.size(); i++){
//        for (uint j = 0; j < this->M[i].size(); j++){
//            if (this->M[i].at(j) > vertex_number_to_destroy)
//                this->M[i].at(j) = this->M[i].at(j) - 1;
//        }
//    }

//    // change the number of the vertex in N
//    for (uint i = vertex_number_to_destroy+1; i < this->N.size(); i++){
//        this->N.at(i) = this->N.at(i) - 1;
//    }

//    // erase from N and M vectors
//    this->N.erase(this->N.begin() + this->edge.ni2);
//    this->M.erase(this->M.begin() + this->edge.ni2);
//}

//void Graph::destroySelfLoop()
//{
//    for (uint i = 0; i < this->M.size(); i++){
//        for (uint j = 0; j < this->M[i].size(); j++){
//            const vint::iterator iterators_to_remove = remove(this->M.at(i).begin(), this->M.at(i).end(), this->N.at(i));
//            this->M.at(i).erase(iterators_to_remove, this->M.at(i).end());
//        }
//    }
//}






