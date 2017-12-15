#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <queue>
#include <sstream>
#include <algorithm>
#include "inputfilereader.h"

using namespace std;

class MedianMaintenance
{
    vector<int> H_low;
    vector<int> H_high;
    void pushToLow(int element);
    void pushToHigh(int element);
    void decideWhereToAddInitialElement(int element);
    int getElementFrontFromLowHeap() { return H_low.front(); }
    int getElementFrontFromHighHeap() { return -H_high.front(); }
    void popLowPushHigh();
    void popHighPushLow();
    int popLowHeap();
    int popHighHeap();
    bool areFrontElementsInCorrectHeaps();
    bool areHeapsUnbalanced();
    void swapFrontElementsInHeaps();
public:
    MedianMaintenance();
    void addElement(int new_element);
    int getMedian();
};

MedianMaintenance::MedianMaintenance()
{
    // heap returns maximum number
    make_heap(H_low.begin(), H_low.end());
    make_heap(H_high.begin(), H_high.end());
}

void MedianMaintenance::addElement(int element)
{
    if (H_low.empty() || H_high.empty())
    {
        if (H_low.empty() && H_high.empty())
        {
            pushToLow(element);
        }
        else if (H_low.empty())
        {
            pushToLow(element);
            if (!areFrontElementsInCorrectHeaps())
                swapFrontElementsInHeaps();
        }
        else if (H_high.empty())
        {
            pushToHigh(element);
            if (!areFrontElementsInCorrectHeaps())
                swapFrontElementsInHeaps();
        }
    }
    else
    {
        int heaps_boundary_value = getElementFrontFromHighHeap();

        if (element > heaps_boundary_value)
            pushToHigh(element);
        else
            pushToLow(element);

        if (areHeapsUnbalanced())
        {
            if (H_low.size() > H_high.size())
                popLowPushHigh();
            else
                popHighPushLow();
        }
    }
}

void MedianMaintenance::pushToLow(int element)
{
    H_low.push_back(element);
    make_heap(H_low.begin(), H_low.end());
}

void MedianMaintenance::pushToHigh(int element)
{
    H_high.push_back(-element);
    make_heap(H_high.begin(), H_high.end());
}

bool MedianMaintenance::areFrontElementsInCorrectHeaps()
{
    int low_heap_front = getElementFrontFromLowHeap();
    int high_heap_front = getElementFrontFromHighHeap();

    return (low_heap_front < high_heap_front);
}

void MedianMaintenance::swapFrontElementsInHeaps()
{
    int low_heap_front = popLowHeap();
    int high_heap_front = popHighHeap();

    pushToLow(high_heap_front);
    pushToHigh(low_heap_front);
}

int MedianMaintenance::popLowHeap()
{
    int max_element = getElementFrontFromLowHeap(); //gets max element from heap
    std::pop_heap (H_low.begin(), H_low.end()); // move first element to last place in vector
    H_low.pop_back(); //remove the highest element that was moved back
    return max_element;
}

int MedianMaintenance::popHighHeap()
{
    int min_element = getElementFrontFromHighHeap(); //gets max element from heap
    std::pop_heap (H_high.begin(), H_high.end()); // move first element to last place in vector
    H_high.pop_back(); //remove the highest element that was moved back
    return min_element;
}

void MedianMaintenance::popLowPushHigh()
{
    int element = popLowHeap();
    pushToHigh(element);
//    pop_heap(H_low.begin(), H_low.end());
//    H_low.pop_back();
}

void MedianMaintenance::popHighPushLow()
{
//    H_low.push_back(-H_high.front());
//    push_heap(H_low.begin(), H_low.end());
//    pop_heap(H_high.begin(), H_high.end());
//    H_high.pop_back();
    int element = popHighHeap();
    pushToLow(element);
}

bool MedianMaintenance::areHeapsUnbalanced()
{
    int size_differemce = abs(static_cast<int>(H_low.size()) - static_cast<int>(H_high.size()));
    return (size_differemce > 1);
}

int MedianMaintenance::getMedian()
{
    int median = 0;

    if (H_low.size() == H_high.size())
        median = getElementFrontFromLowHeap();
    else if (H_low.size() == H_high.size() + 1)
        median = getElementFrontFromLowHeap();
    else if (H_high.size() == H_low.size() + 1)
        median = getElementFrontFromHighHeap();
    else
        cout<<"Warning: Unbalanced heaps! Heap Low: " << H_low.size() << " Heap High: " << H_high.size() << endl;

//    cout << "Heap Low: " << Hlow.size() << " Heap High: " << Hhigh.size() << endl;

    return median;
}



//int get_median(vector<int>& Hlow, vector<int>& Hhigh, int new_element)
//{
//    int max = Hlow.front();
//    int min = -Hhigh.front();


//    // Add new element

//    if (new_element > min)
//    {
//        Hhigh.push_back(-new_element);
//        push_heap(Hhigh.begin(), Hhigh.end());

//        if ( Hhigh.size() > Hlow.size() + 1)
//        {
//            Hlow.push_back(-Hhigh.front());
//            push_heap(Hlow.begin(), Hlow.end());
//            pop_heap(Hhigh.begin(), Hhigh.end()), Hhigh.pop_back();
//        }
//    }
//    else
//    {
//        Hlow.push_back(new_element);
//        push_heap(Hlow.begin(), Hlow.end());

//        if ( Hlow.size() > Hhigh.size() + 1)
//        {
//            Hhigh.push_back(-Hlow.front());
//            push_heap(Hhigh.begin(), Hhigh.end());
//            pop_heap(Hlow.begin(), Hlow.end()), Hlow.pop_back();
//        }
//    }


//    // Extract median

//    int median = 0;

//    if (Hlow.size() == Hhigh.size())
//        median = Hlow.front();
//    else if (Hlow.size() == Hhigh.size() + 1)
//        median = Hlow.front();
//    else if (Hhigh.size() == Hlow.size() + 1)
//        median = -Hhigh.front();
//    else
//        cout<<"Warning: Unbalanced heaps! Heap Low: " << Hlow.size() << " Heap High: " << Hhigh.size() << endl;

////    cout << "Heap Low: " << Hlow.size() << " Heap High: " << Hhigh.size() << endl;

//    return median;
//}


int main()
{
    string file_name = "Median.txt";
    vector<int> data_stream;
    InputFileReader::open_and_read_input_data_file(file_name, data_stream);

//    vector<int> H_low;
//    vector<int> H_high;

//    if (data_stream[0] < data_stream[1])
//    {
//        H_low.push_back(data_stream[0]);
//        H_high.push_back(-data_stream[1]);
//    }
//    else
//    {
//        H_low.push_back(data_stream[1]);
//        H_high.push_back(-data_stream[0]);
//    }



//    long int sum = data_stream[0];
//    sum += H_low.front();

//    for (int k = 2; k < data_stream.size(); k++)
//        sum += get_median(H_low, H_high, data_stream[k]);

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
