#include "inputfilereader.h"
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

void InputFileReader::read_input_file_line_by_line(ifstream& input_file, vector<int>& data_out)
{
    string input_file_ling;
    while ( getline(input_file,input_file_ling) )
    {
        int integer = atoi( input_file_ling.c_str() );
        data_out.push_back( integer );
    }
}

void InputFileReader::open_and_read_input_data_file(const string& input_file_name, vector<int>& data_out)
{
    ifstream input_file;
    if (open_input_data_file(input_file_name, input_file))
    {
        cout << "Input data file successfully opened." << endl;
        read_input_file_line_by_line(input_file, data_out);
        input_file.close();
    }
    else
    {
        cout << "Unable to open input data file.\n"
                "Check input data file path." << endl;
        exit(1);
    }
}
