#include "graph.h"
#include "inputfilereader.h"

using namespace std;

int main()
{
    string file_name = "SCCtest.txt";
    Graph graph;
    InputFileReader::open_and_read_input_data_file(file_name, graph);

    graph.printVertices();
    graph.printEdges();

    return 0;
}
