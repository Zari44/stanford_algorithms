#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

class Quicksort
{
    std::vector<int> _data;
    unsigned int _number_of_comparisons;
    static unsigned int recursiveSort(std::vector<int>& input_data, unsigned int low, unsigned int high);
    static unsigned int chooseMedianPivot(std::vector<int>& data_in, unsigned int low, unsigned int high);
    static unsigned int chooseFirstElementPivot(unsigned int low) {return low;}
    static unsigned int chooseLastElementPivot(unsigned int high) {return high-1;}
    static unsigned int findIndexofMedianValue(std::vector<int>& data_in, unsigned int index1, unsigned int index2, unsigned int index3 );
    static unsigned int findIndexofMedianValue(std::vector<int>& data_in, unsigned int index1, unsigned int index2);
    static unsigned int  findIndexofMedianValue(std::vector<int>& data_in, unsigned int index1);
    static unsigned int partitionArray(std::vector<int>& data_in, unsigned int low, unsigned int pivot_index, unsigned int high);
    static void swap(std::vector<int>& data_in, unsigned i, unsigned j);
public:
    Quicksort(const std::vector<int>& input_data);
    void setData(const std::vector<int>& input_data);
    std::vector<int> getData();
    void sort(unsigned int starting_index, unsigned int ending_index);
    unsigned int getNumberOfComparisons();
    static void print(std::vector<int>& data_in);
};

#endif // QUICKSORT_H
