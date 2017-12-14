#include "quicksort.h"
#include <iostream>

Quicksort::Quicksort(const std::vector<int>& input_data)
    : _data(input_data),
      _number_of_comparisons(0)
{

}

void Quicksort::setData(const std::vector<int>& input_data)
{
    _data = input_data;
}

std::vector<int> Quicksort::getData()
{
    return _data;
}

unsigned int Quicksort::getNumberOfComparisons()
{
    return _number_of_comparisons;
}

void Quicksort::sort(unsigned int starting_index, unsigned int ending_index)
{
    if ( starting_index > ending_index )
        return;

//    unsigned int pivot_index = choose_pivot_index(_data, starting_index, ending_index);
    unsigned int pivot_index = chooseFirstElementPivot(starting_index);
//    unsigned int pivot_index = chooseLastElementPivot(ending_index);

    unsigned int boundary_index = partitionArray(_data, starting_index, pivot_index, ending_index);

    _number_of_comparisons = ending_index - starting_index - 1;
    _number_of_comparisons += recursiveSort(_data, starting_index, boundary_index);
    _number_of_comparisons += recursiveSort(_data, boundary_index+1, ending_index);
}


unsigned int Quicksort::recursiveSort(std::vector<int>& input_data, unsigned int low, unsigned int high)
{
    if ( low < high )
    {
//        unsigned int pivot_index = choose_pivot_index(input_data, low, high);
        unsigned int pivot_index = chooseFirstElementPivot(low);
//        unsigned int pivot_index = chooseLastElementPivot(high);

        unsigned int boundary_index = partitionArray(input_data, low, pivot_index, high);

        unsigned int no_of_comparisons = high - low - 1;
        no_of_comparisons += recursiveSort(input_data, low, boundary_index);
        no_of_comparisons += recursiveSort(input_data, boundary_index+1, high);

        return no_of_comparisons;
    }
    else
        return 0;
}

unsigned int Quicksort::chooseMedianPivot(std::vector<int>& data_in, unsigned int low, unsigned int high)
{
    unsigned int lowest = low;
    unsigned int highest = high - 1;
    unsigned int middle = (low + highest)/2;

    if (high - low > 2)
        return findIndexofMedianValue(data_in, lowest, middle, highest);
    else if (high - low == 2)
        return findIndexofMedianValue(data_in, lowest, highest);
    else
        return findIndexofMedianValue(data_in, lowest);
}

unsigned int Quicksort::findIndexofMedianValue(std::vector<int>& data_in, unsigned int index1, unsigned int index2, unsigned int index3 )
{
    unsigned int value1 = data_in[index1];
    unsigned int value2 = data_in[index2];
    unsigned int value3 = data_in[index3];

    if ( value1 < value2)
    {
        if ( value3 < value1)
            return index1;
        else if (value3 > value2)
            return index2;
        else
            return index3;
    }
    else
    {
        if ( value3 < value2)
            return index2;
        else if (value3 > value1)
            return index1;
        else
            return index3;
    }

}

unsigned int Quicksort::findIndexofMedianValue(std::vector<int>& data_in, unsigned int index1, unsigned int index2 )
{
    if (data_in[index1] < data_in[index2])
        return index1;
    else
        return index2;
}

unsigned int Quicksort::findIndexofMedianValue(std::vector<int>& data_in, unsigned int index1 )
{
    return index1;
}


unsigned int Quicksort::partitionArray(std::vector<int>& data_in, unsigned int low, unsigned int pivot_index, unsigned int high)
{

    // swap pivot to first element
    swap(data_in, pivot_index, low);
    pivot_index = low;

    unsigned int pivot_value = data_in[pivot_index];
    unsigned int i = pivot_index;   // end of smaller than
    unsigned int j = pivot_index;   // end of greater than

    for (; j<high; ++j)
    {
        if (data_in[j] < pivot_value)
            swap(data_in, j, ++i);
    }

    swap(data_in, pivot_index, i);
    // return the boundary index
    return i;
}

void Quicksort::swap(std::vector<int>& data_in, unsigned i, unsigned j)
{
    unsigned int temp = data_in[i];
    data_in[i] = data_in[j];
    data_in[j] = temp;
}

void Quicksort::print(std::vector<int>& data_in)
{
    for (const auto& element : data_in)
        std::cout << element << " ";
    std::cout << std::endl;
}


