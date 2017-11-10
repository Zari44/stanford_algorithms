/*
 * main.cpp
 *
 *  Created on: 11.02.2017
 *      Author: Zari
 */
#ifndef _VECTOR_H
#define	_VECTOR_H


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

typedef vector<int> vint;

class InversionArray : public std::vector<int>{
	  //unsigned int _range;
	  //unsigned int _size;
	  unsigned int count_recursive(vector<int>& Vector);
  public:
	  InversionArray(unsigned int Size, unsigned int Range);
	  InversionArray(string);
	  void print();
	  unsigned int count_inversions_brute_force();
	  unsigned int count_inversions();
	  unsigned int merge_and_count_split_inv(vint &vect, vint &A, vint &B);
};

InversionArray::InversionArray(unsigned int Size, unsigned int Range){
	//this->_range = Range;
	//this->_size  = Size;
	srand(time(0));
	for (unsigned int i; i < Size; i++){
		this->push_back(rand() % Range + 0);
	}
}

InversionArray::InversionArray(string file_name){
	string line;
	ifstream myfile;
	myfile.open(file_name.c_str());
	if (myfile.is_open()){
		cout << "File Opened." << endl;
		while ( getline(myfile,line) ){
			int integer = atoi( line.c_str() );
			//cout << integer << endl;
			this->push_back( integer );
		}

		myfile.close();
	}
	else{
		cout << "Unable to open file." << endl;
		exit(0);
	}
}

void InversionArray::print(){
	cout << "The array is: ";
	for (unsigned i=0; i < this->size(); i++){
		cout << this->at(i) << " ";
	}
	cout << endl;
}

unsigned int InversionArray::count_inversions_brute_force(){
	unsigned int n = this->size();
	unsigned int res = 0;
	for (unsigned i = 0; i < n; i ++){
		for (unsigned j = i + 1; j < n; j++ ){
			if (this->at(i) > this->at(j))
				res++;
		}
	}
	return res;
}

unsigned int InversionArray::merge_and_count_split_inv(vint &vect, vint &L, vint &R){

	unsigned i = 0;
	unsigned j = 0;
	unsigned k = 0;
	unsigned res = 0;

	while ((i < L.size()) && (j < R.size())){
		if (L[i] <= R[j])
			vect[k++] = L[i++];
		else{
			vect[k++] = R[j++];
			res = res + L.size() - i;
		}
	}

	while (i < L.size()){
		vect[k++] = L[i++];
	}

	while (j < R.size())
		vect[k++] = R[j++];

	return res;
}

unsigned int InversionArray::count_recursive(vector<int>& Vector){
	unsigned int n = Vector.size();
	if (n == 1)
		return 0;
	else{

		vector<int>::iterator iter;

		vector<int> Left(Vector.begin(), Vector.begin() + n / 2);
		vector<int> Right(Vector.begin() + n / 2, Vector.end() );

		unsigned int x = count_recursive(Left);
		unsigned int y = count_recursive(Right);
//
//		cout << "\nSorted Left: ";
//		for(iter = Left.begin(); iter != Left.end(); iter++)
//			cout<<*iter<<" ";
//		cout << Left.size();
//		cout << "\nSorted Right: ";
//		for(iter = Right.begin(); iter != Right.end(); iter++)
//			cout<<*iter<<" ";
//		cout << Right.size();

		unsigned int z = merge_and_count_split_inv(Vector, Left, Right);

//		cout << "\nVector: ";
//		for(iter = Vector.begin(); iter != Vector.end(); iter++)
//			cout<<*iter<<" ";

		return x+y+z;
	}
}

unsigned int InversionArray::count_inversions()
{
	vector<int> Vector(this->begin(), this->end());

	unsigned int res = count_recursive(Vector);

	for (unsigned int i = 0; i < Vector.size(); i++)
		this->at(i) = Vector[i];

	return res;
}

int main(){
//	const unsigned int range = 10;
//	const unsigned int size = 8;
	//InversionArray list(size, range);
	//char name[] = "IntegerArray.txt";
	string file = "IntegerArray.txt";
	InversionArray list(file);
	//list.print();
	//cout << "Number of inversions by brute force is : " << list.count_inversions_brute_force() << endl;
	cout << "Number of inversions by algorithm is : "   << list.count_inversions() << endl;
	//list.print();
	return 0;
}

#endif	/* _VECTOR_H */


