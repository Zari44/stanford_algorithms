///*
// * main.cpp
// *
// *  Created on: 13.05.2017
// *      Author: Zari
// */
//
//
//#include <string>
//#include <fstream>
//#include <iostream>
//#include <set>
//#include <stdlib.h>     /* atoi */
//#include <algorithm>
//#include <map>
//
//using namespace std;
//
//int main(){
//
//	const char* file_name = "algo1-programming_prob-2sum.txt";
//	fstream myfile;
//	myfile.open(file_name);
//
//	string line;
//
//	set<long> mySet;
//
//	while ( getline(myfile,line) ){
//		long integer = atoi(line.c_str());
//		mySet.insert(integer);
//	}
//
//	cout << "File read\n";
////	sort (vect.begin(), vect.end());
//
//	cout << "File sorted\n";
//
////	map<int, int> myMap;
//
//	unsigned int count = 0;
//	for (long t = -10000; t <= 10000; ++t){
//
//		if (t % 1000 == 0) cout << "t is: " << t << endl;
//
//		for (set<long>::iterator x = mySet.begin(); x != mySet.end(); ++x){
//			long y = t - *x;
//			if (mySet.find(y) != mySet.end()){
//				++count;
//				break;
//			}
//		}
//	}
//
//	cout << "Count is: " << count;
//
//	return 0;
//}
//
//// Previously wrong answers:
//// 18617
//// 18618
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <sstream>
#include <set>

using namespace std;


bool Sum2(set<long> &inputs, int target)
{
	set<long>::iterator itBeg;
	set<long>::iterator itEnd;

	itBeg = inputs.begin();
	itEnd = inputs.end();
	itEnd--;

	long sum;
	bool result = false;
	while(itBeg != itEnd)
	{
		sum = *itBeg + *itEnd;
		if (sum == target)
		{
			result = true;
			break;
		}
		else if (sum < target)
		{
			itBeg++;
		}else{
			itEnd--;
		}
	}


	return result;
}


int main()
{
	ifstream infile;
	infile.open("algo1-programming_prob-2sum.txt");

	set<long> inputSet;
	long input;
	while(!infile.eof())
	{
		infile >> input;
		inputSet.insert(input);
	}

	int sum =0;
	for (int i=-10000; i<10001; i++)
	{
		if (i % 1000 == 0) cout << "i = " << i << endl;

		if (Sum2(inputSet, i))
		{
			sum++;
		}
	}

	cout << "The number is " << sum << endl;
	infile.close();
	return 0;
}
