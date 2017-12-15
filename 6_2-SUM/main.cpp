#include <iostream>
#include <fstream>
#include <set>

using namespace std;

bool is2SumFound(set<long>& inputs, int target)
{
    set<long>::iterator it_begin;
    set<long>::iterator it_end;

    it_begin = inputs.begin();
    it_end = inputs.end();
    it_end--;

    long sum;
    bool result = false;
    while(it_begin != it_end)
    {
        sum = *it_begin + *it_end;
        if (sum == target)
        {
            result = true;
            break;
        }
        else if (sum < target)
            it_begin++;
        else
            it_end--;
    }


    return result;
}


int main()
{
    ifstream infile;
    infile.open("algo1-programming_prob-2sum.txt");
    if (!infile.is_open())
    {
        cout << "Unable to open file." << endl;
        exit(1);
    }

    set<long> inputSet;
    long input;
    while(!infile.eof())
    {
        infile >> input;
        inputSet.insert(input);
    }
    infile.close();

    int sum = 0;
    for (int i = -10000; i <= 10000; i++)
    {
        if (i % 1000 == 0)
            cout << "i = " << i << endl;

        if (is2SumFound(inputSet, i))
            sum++;
    }

    cout << "The number is " << sum << endl;

    return 0;
}
