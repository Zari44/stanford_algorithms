#include "inversionscount.h"
#include <iostream>

using namespace std;

void InversionsCount::generate_random_data(unsigned int size, unsigned int range, vector<int>& data_out)
{
    srand(time(0));
    for (unsigned int i; i < size; i++)
    {
        int random_item = rand() % range;
        data_out.push_back(random_item);
    }
}

bool InversionsCount::open_input_data_file(const string& input_file_name, ifstream& data_file)
{
    data_file.open(input_file_name.c_str());
    return data_file.is_open();
}

void InversionsCount::read_input_file_line_by_line(ifstream& input_file, vector<int>& data_out)
{
    string input_file_ling;
    while ( getline(input_file,input_file_ling) )
    {
        int integer = atoi( input_file_ling.c_str() );
        data_out.push_back( integer );
    }
}

void InversionsCount::open_and_read_input_data_file(const string& input_file_name, vector<int>& data_out)
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

void InversionsCount::print(const std::vector<int>& data)
{
    for (const auto& element : data)
        cout << element << " ";
    cout << endl;
}

unsigned int InversionsCount::count_inversions(std::vector<int>& data)
{
    vector<int> data_copy = data;

    unsigned int res = count_recursive(data_copy);

    for (unsigned int i = 0; i < data_copy.size(); i++)
        data.at(i) = data_copy[i];

    return res;
}

unsigned int InversionsCount::count_recursive(std::vector<int>& input_data)
{
    unsigned int in_data_size = input_data.size();
    if (in_data_size == 1)
        return 0;
    else
    {
        vector<int> input_data_left_hand_side(input_data.begin(), input_data.begin() + in_data_size / 2);
        vector<int> input_data_right_hand_size(input_data.begin() + in_data_size / 2, input_data.end() );

        unsigned int x = count_recursive(input_data_left_hand_side);
        unsigned int y = count_recursive(input_data_right_hand_size);
        unsigned int z = merge_and_count_split_inv(input_data, input_data_left_hand_side, input_data_right_hand_size);

        unsigned int number_of_inversions = x + y + z;

        return number_of_inversions;
    }
}

unsigned int InversionsCount::merge_and_count_split_inv(std::vector<int>& data_out, const std::vector<int>& LHS, const std::vector<int>& RHS)
{
    unsigned int index_left = 0;
    unsigned int index_right = 0;
    unsigned int index_output = 0;
    unsigned int number_of_inversions = 0;

    while ((index_left < LHS.size()) && (index_right < RHS.size()))
    {
        if (LHS[index_left] <= RHS[index_right])
            data_out[index_output++] = LHS[index_left++];
        else
        {
            data_out[index_output++] = RHS[index_right++];
            number_of_inversions += LHS.size() - index_left;
        }
    }

    while (index_left < LHS.size())
        data_out[index_output++] = LHS[index_left++];

    while (index_right < RHS.size())
        data_out[index_output++] = RHS[index_right++];

    return number_of_inversions;
}
