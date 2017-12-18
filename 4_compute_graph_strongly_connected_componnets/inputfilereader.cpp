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
    const string delimiter = " ";
    size_t pos = line.find(delimiter);

    string str_int = line.substr(0, pos);
    unsigned int tail = atoi(str_int.c_str())-1;
    line.erase(0, pos + delimiter.length());

    pos = line.find(delimiter);
    str_int = line.substr(0, pos);
    unsigned int head = atoi(str_int.c_str())-1;

    graph_out.adj[tail].push_back(head); // Add head to tailss list.

    if (tail % 100000 == 0)
        cout << "tail: " << tail << endl;
//	while (this->M.size() <= tail){
//		vector<unsigned int> empty_vector;
////		this->M.push_back(empty_vector);
//		adj.push_back(empty_vector);
//	}
//	this->M.at(tail).push_back(head);
//
//	while (this->M.size() <= head){
//		vector<unsigned int> empty_vector;
//		this->M.push_back(empty_vector);
//	}
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
