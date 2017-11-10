/*
 * main.cpp
 *
 *  Created on: 16.05.2017
 *      Author: Zari
 */

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace std;


int get_median(vector<int>& Hlow, vector<int>& Hhigh, int new_element)
{
	int max = Hlow.front();
	int min = -Hhigh.front();

	int median = 0;

	// Add new element

	if (new_element > min){
		Hhigh.push_back(-new_element);
		push_heap(Hhigh.begin(), Hhigh.end());

		if ( Hhigh.size() > Hlow.size() + 1){
			Hlow.push_back(-Hhigh.front());
			push_heap(Hlow.begin(), Hlow.end());
			pop_heap(Hhigh.begin(), Hhigh.end()), Hhigh.pop_back();
		}
	}
	else{
		Hlow.push_back(new_element);
		push_heap(Hlow.begin(), Hlow.end());

		if ( Hlow.size() > Hhigh.size() + 1){
			Hhigh.push_back(-Hlow.front());
			push_heap(Hhigh.begin(), Hhigh.end());
			pop_heap(Hlow.begin(), Hlow.end()), Hlow.pop_back();
		}
	}


	// Extract median

	if (Hlow.size() == Hhigh.size()){
		median = Hlow.front();
	}
	else if (Hlow.size() == Hhigh.size() + 1){
		median = Hlow.front();
	}
	else if (Hhigh.size() == Hlow.size() + 1){
		median = -Hhigh.front();
	}
	else{
		cout<<"Warning: Unbalanced heaps! Heap Low: " << Hlow.size() << " Heap High: " <<Hhigh.size()<<endl;
	}

	cout << "Heap Low: " << Hlow.size() << " Heap High: " << Hhigh.size() << endl;

	return median;
}


int main()
{
	ifstream infile;
	infile.open("Median.txt");

	vector<int> inputVect;
	int input;
	while(!infile.eof())
	{
		infile >> input;
		inputVect.push_back(input);
	}
	infile.close();

	vector<int> H_low;
	vector<int> H_high;

	if (inputVect[0] < inputVect[1]){
		H_low.push_back(inputVect[0]);
		H_high.push_back(-inputVect[1]);
	}
	else{
		H_low.push_back(inputVect[1]);
		H_high.push_back(-inputVect[0]);
	}

	// heap returns maximum number
	make_heap(H_low.begin(), H_low.end());
	make_heap(H_high.begin(), H_high.end());

	long sum = inputVect[0];
	sum += H_low.front();

	for (int k=2; k<10000; k++)
	{
		sum += get_median(H_low, H_high, inputVect[k]);
	}

	cout << "The number is " << sum << endl;

	return 0;
}

//7124
//8260
//6214
//1213

