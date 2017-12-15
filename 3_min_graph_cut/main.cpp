#include "graph.h"
#include "inputfilereader.h"
#include "calculatemincut.h"

using namespace std;

int main()
{
    string file_name = "kargerMinCut.txt";
    Graph graph;
    InputFileReader::open_and_read_input_data_file(file_name, graph);

    unsigned int iteratons = 20;
    unsigned int min_cut = CalculateMinCut::calculate_min_cut(graph, iteratons);

    cout << "Minimum cut is: " << min_cut << endl;

    return 0;
}

