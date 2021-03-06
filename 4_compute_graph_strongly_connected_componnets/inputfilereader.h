#ifndef INPUTFILEREADER_H
#define INPUTFILEREADER_H

#include <fstream>
#include <string>
#include <vector>

class Graph;

class InputFileReader
{
    static bool open_input_data_file(const std::string& input_file_name, std::ifstream& data_file);
    static void read_input_file_line_by_line(std::ifstream& input_file, Graph& graph_out);
    static void parse_input_line(std::string line, Graph& graph_out);
public:
    static void generate_random_data(unsigned int size, unsigned int range, std::vector<int>& data_out);
    static void open_and_read_input_data_file(const std::string& input_file_name, Graph& graph_out);
};



#endif // INPUTFILEREADER_H
