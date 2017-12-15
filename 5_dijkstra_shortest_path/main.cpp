#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>     /* atoi */
#include <algorithm>

#include "inputfilereader.h"
#include "graph.h"
#include "calculatedijkstrashortestpath.h"

using namespace std;

int main()
{
    string file_name = "dijkstraData.txt";
    unsigned int number_of_vertices = 200;

    Graph graph(number_of_vertices);
    InputFileReader::open_and_read_input_data_file(file_name, graph);

//    graph.print();
    unsigned int start_vertex = 1;
    vector<unsigned int> end_vertices = {7,37,59,82,99,115,133,165,188,197};

    cout << "Shortest path from: " << endl;
    for (const auto& end_vertex : end_vertices)
    {
         cout << "- " << start_vertex << " to " << end_vertex <<
                " is equal to: " << CalculateDijkstraShortestPath::compute_shortest_path_value(graph, start_vertex-1, end_vertex-1) << endl;
    }

    return 0;
}



