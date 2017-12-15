#include "medianmaintenance.h"
#include <iostream>
#include <algorithm>

using namespace std;

MedianMaintenance::MedianMaintenance()
{

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
    push_heap(H_low.begin(), H_low.end());
}

void MedianMaintenance::pushToHigh(int element)
{
    H_high.push_back(-element);
    push_heap(H_high.begin(), H_high.end());
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
}

void MedianMaintenance::popHighPushLow()
{
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
