#include <iostream>
#include <vector>

#include "inputfilereader.h"
#include "quicksort.h"

using namespace std;


/*****************************************************************/

int main()
{
    std::vector<int> data;
    std::string input_file_name("QuickSort.txt");
    InputFileReader::open_and_read_input_data_file(input_file_name, data);

    Quicksort quicksort(data);

    unsigned int starting_index = 0;
    unsigned int ending_index = data.size();

    quicksort.sort(starting_index, ending_index);

    cout << "Finished with number of comparisons = " << quicksort.getNumberOfComparisons() << endl;

    return 0;
}
