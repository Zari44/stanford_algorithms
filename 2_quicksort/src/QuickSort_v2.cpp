//============================================================================
// Name        : Quicksort.cpp
// Author      : Zari
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

typedef unsigned int uint;
typedef vector<unsigned int> vint;


void read_txt(vint& V){
	string line;
	ifstream myfile;
	myfile.open("QuickSortTest.txt");
	if (myfile.is_open()){
		cout << "File Opened." << endl;
		while ( getline(myfile,line) ){
			int integer = atoi( line.c_str() );
			V.push_back( integer );
		}

		myfile.close();
	}
	else{
		cout << "Unable to open file." << endl;
		exit(0);
	}
}

void vector_print(vint &V){

	for ( vint::iterator it = V.begin(); it != V.end(); it++)
		cout << *it << " ";
	//cout << endl;
}

unsigned int Partition(const vint& V){
	return 0;
}

uint find_median(uint a_v, uint b_v, uint c_v, uint a_i, uint b_i, uint c_i ){

	if ( a_v < b_v){
		if ( c_v < a_v)
			return a_i;
		else if (c_v > b_v)
			return b_i;
		else
			return c_i;
	}
	else{
		if ( c_v < b_v)
			return b_i;
		else if (c_v > a_v)
			return a_i;
		else
			return c_i;
	}

}



void quicksort_swap(vint& V, unsigned i, unsigned j){
	unsigned int var = V[i];
	V[i] = V[j];
	V[j] = var;
}

unsigned int quicksort_partition(vint& V, unsigned int p, unsigned int q, unsigned int r){

	// swap pivot to first element
	quicksort_swap(V, q, p);
	q = p;

	unsigned int pivot_value = V[q];
	unsigned int i = q;   // end of smaller than
	unsigned int j = q;   // end of greater than

	while (j < r){
		if (V[j] < pivot_value){
			quicksort_swap(V, j, ++i);
		}
		j++;
	}
	quicksort_swap(V, q, i);
	// return the boundary index
	return i;
}

uint ChosePivotIndex(vint& V, unsigned int p, unsigned int r){

	if (r - p > 2){


		unsigned int a_i = p;
		unsigned int c_i = r-1;
		unsigned int b_i = (p+c_i)/2;

//		if ((r % 2) == 1){
//			b_i = (p+r)/2;
//		}
//		else{
//			b_i = (p+r)/2-1;
//		}

		unsigned int a_v = V[a_i];
		unsigned int b_v = V[b_i];
		unsigned int c_v = V[c_i];

		//vector_print(V);
		//cout << "p: " << p << " r: " << r << " q: " << b_i << endl;
		return find_median(a_v, b_v, c_v, a_i, b_i, c_i);
	}
	else if (r - p == 2){
		//vector_print(V);
		//cout << "p: " << p << " r: " << r;
		if (V[p] < V[r-1]){
			//cout << " returned: " << p << endl;
			return p;
		}
		else{
			//cout << " returned: " << r-1 << endl;
			return r-1;
		}


	}
	else{
		//vector_print(V);
		//cout << "p: " << p << endl;
		return p;
	}

}

unsigned int QuickSort(vint& V, unsigned int p, unsigned int r){

	if (r > p){

		unsigned int no_of_comp = r-p-1;

		// Chose a pivot point
		unsigned int q = ChosePivotIndex(V, p ,r);
//		q = p;
		// Partition the list
		q = quicksort_partition(V, p, q, r);

		// Break the list into two smaller lists
		// Recursively sort the lists
		no_of_comp = no_of_comp + QuickSort(V, p, q);
		no_of_comp = no_of_comp + QuickSort(V, q+1, r);

		return no_of_comp;
	}
	else
		return 0;
}


int main() {

	vint V;
	read_txt(V);
	vector_print(V), cout << endl;
	unsigned int no_of_comp = QuickSort(V, 0, V.size());
	vector_print(V);
	cout << "\nFinished with NOC = " << no_of_comp << endl;

//	cout << find_median(1,2,3,1,2,3) << endl;
//	cout << find_median(1,3,2,1,2,3) << endl;
//	cout << find_median(2,1,3,1,2,3) << endl;
//	cout << find_median(2,3,1,1,2,3) << endl;
//	cout << find_median(3,1,2,1,2,3) << endl;
//	cout << find_median(3,2,1,1,2,3) << endl;

	return 0;
}
