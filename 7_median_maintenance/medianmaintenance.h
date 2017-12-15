#ifndef MEDIANMAINTENANCE_H
#define MEDIANMAINTENANCE_H

#include <vector>

class MedianMaintenance
{
    std::vector<int> H_low;
    std::vector<int> H_high;
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

#endif // MEDIANMAINTENANCE_H
