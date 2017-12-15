#include <iostream>
#include "inputfilereader.h"
#include "medianmaintenance.h"

using namespace std;

int main()
{
    string file_name = "Median.txt";
    vector<int> data_stream;
    InputFileReader::open_and_read_input_data_file(file_name, data_stream);

    MedianMaintenance medianMaintenance;

    long int sum = 0;

    for (int i = 0; i < data_stream.size(); ++i)
    {
        medianMaintenance.addElement(data_stream[i]);
        sum += medianMaintenance.getMedian();
    }

    cout << "The number is " << sum << endl;
    cout << "Last 4 digits are " << sum % 10000 << endl;

    return 0;
}

//7124
//8260
//6214
//1213
