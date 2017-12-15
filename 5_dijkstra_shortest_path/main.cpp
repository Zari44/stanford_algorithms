#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>     /* atoi */
#include <algorithm>

#include "inputfilereader.h"
#include "graph.h"

using namespace std;

int main()
{
    string file_name = "dijkstraData.txt";
    unsigned int number_of_vertices = 200;
    Graph graph(number_of_vertices);
    InputFileReader::open_and_read_input_data_file(file_name, graph);
    graph.print();
    unsigned int vertices[] = {7,37,59,82,99,115,133,165,188,197};
    unsigned int start_vertex = 1;
    vector<unsigned int> end_vertices (vertices, vertices + sizeof(vertices) / sizeof(unsigned int) );

    for (unsigned int i = 0; i < end_vertices.size(); ++i)
    {
        cout << "Shortest path from: " << start_vertex << " to " << end_vertices[i] <<
                " is equal to: " << graph.get_shortest_path(start_vertex-1, end_vertices[i]-1) << endl;
    }

    return 0;
}



