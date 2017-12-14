#include "graph.h"
#include "inputfilereader.h"

using namespace std;

int main()
{
    string file_name = "kargerMinCut.txt";
    Graph graph;
    InputFileReader::open_and_read_input_data_file(file_name, graph);
    cout << "Minimum cut is: " << graph.get_minimum_cut(10) << endl;

    return 0;
}

