// C++ Implementation of Kosaraju's algorithm to print all SCCs
#include <iostream>
#include <list>
#include <stack>


#include <vector>
#include <fstream>
#include <string>

#include "inputfilereader.h"
#include "graph.h"
#include "computestronglyconnectedcomponents.h"

using namespace std;

// Driver program to test above functions
int main()
{
    string filename = "SCC.txt";
    int number_of_vertices = 875714;
//    "SCC.txt", 875714
    Graph graph(number_of_vertices);
    InputFileReader::open_and_read_input_data_file(filename, graph);

    int number_of_sccs_to_print = 5;
    ComputeStronglyConnectedComponents::computeAndPrintSCCs(graph, number_of_sccs_to_print);

    return 0;
}


