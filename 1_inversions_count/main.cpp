#include <iostream>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//#include <fstream>
#include <string>

#include "inversionscount.h"

using namespace std;

int main()
{
    string input_file_name = "inverions_count_input.txt";
    vector<int> data;
    InversionsCount::open_and_read_input_data_file(input_file_name, data);
//    InversionsCount::print(data);
    unsigned int number_of_inversions = InversionsCount::count_inversions(data);
    cout << "Number of inversions by algorithm is : "   << number_of_inversions << endl;

    return 0;
}



