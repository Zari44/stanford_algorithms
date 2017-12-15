#include "inputfilereader.h"
#include "graph.h"
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void InputFileReader::generate_random_data(unsigned int size, unsigned int range, vector<int>& data_out)
{
    srand(time(0));
    for (unsigned int i; i < size; i++)
    {
        int random_item = rand() % range;
        data_out.push_back(random_item);
    }
}

bool InputFileReader::open_input_data_file(const string& input_file_name, ifstream& data_file)
{
    data_file.open(input_file_name.c_str());
    return data_file.is_open();
}


void InputFileReader::read_input_file_line_by_line(ifstream& input_file, Graph& graph_out)
{
    string input_file_line;
    while ( getline(input_file,input_file_line) )
        parse_input_line(input_file_line, graph_out);
}

void InputFileReader::parse_input_line(std::string line, Graph& graph_out)
{
    string delimiter1 = "\t";

    // tail
    size_t pos = line.find(delimiter1);
    string str_tail = line.substr(0, pos);
    line.erase(0, pos + delimiter1.length());
    unsigned int tail = atoi(str_tail.c_str())-1;

    // head,cost
    string delimiter2 = ",";
    while ((pos = line.find(delimiter1)) != string::npos )
    {

        pos = line.find(delimiter1);

        // save interesting chars
        string str_head_cost = line.substr(0, pos);
        line.erase(0, pos + delimiter1.length());

        //find head of the edge
        pos = str_head_cost.find(delimiter2);
        string str_head = str_head_cost.substr(0, pos);

        //find cost of the edge
        str_head_cost.erase(0, pos + delimiter2.length());
        string str_cost = str_head_cost;

        //convert strings to ints

        Graph::Edge edge;// = new Graph::Edge;

        edge.m_head = atoi(str_head.c_str())-1;
        edge.m_cost = atoi(str_cost.c_str());

        graph_out._edges->at(tail).push_back(edge);

    }
}

void InputFileReader::open_and_read_input_data_file(const string& input_file_name, Graph& graph_out)
{
    ifstream input_file;

    if (open_input_data_file(input_file_name, input_file))
    {
        cout << "Input data file successfully opened." << endl;
        cout << "------------------------------------" << endl;
        read_input_file_line_by_line(input_file, graph_out);
        input_file.close();
    }
    else
    {
        cout << "Unable to open input data file.\n"
                "Check input data file path." << endl;
        exit(1);
    }
}
