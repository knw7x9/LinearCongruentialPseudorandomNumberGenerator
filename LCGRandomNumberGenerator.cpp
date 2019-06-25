// LCGRandomNumberGenerator.cpp
// CS 4499
// Written By: Katherine Wilsdon
// 2 February 2019
// Dr. Kerby
// Description - Creates a linear congruential pseudorandom number generator(LCG) of random numbers between 0 and 1.
// The mean, period, and bins were determined for 1 hundred, 10 thousand, 1 million, and 100 million random numbers.
// Cited: Normalize data between 0 and 1: https://stats.stackexchange.com/questions/380276/how-to-normalize-data-between-0-and-1
// Precision: http://umich.edu/~eecs381/handouts/formatting.pdf
// Arrays: http://www.cplusplus.com/doc/tutorial/arrays/
// Vector push_back: http://www.cplusplus.com/reference/vector/vector/push_back/
// Find the index of an element in vector: https://www.techiedelight.com/find-index-element-vector-cpp/

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

// Global variables
int _numIterations;
double _minimum;
double _maximum;
long s = 100001;	// seed 0
vector<long> randomNumVector(_numIterations);
vector<double> normalizedVector(_numIterations);
long binArray[100];

// Linear congruential pseudorandom number generator that returns seed + 1
long int RandLCG(int multiplier, long seed, int adder, long modulus) {
	return (multiplier * seed + adder) % modulus;
}

// Populates the vector with the LCG random number generator
void PopulateVector() {
	for (int i = 0; i < _numIterations; i++) {
		// Stores the random number
		randomNumVector.push_back(RandLCG(61, s, 1, pow(2, 24)));

		// Change the seed to the next random number
		s = randomNumVector.at(i);
	}
}

// Finds the minumum and maxiumum numbers in the random numbers vector
void FindMinAndMax() {
	// set the minimum and maxiumum to the first entry in the random numbers vector
	_minimum = randomNumVector.at(0);
	_maximum = randomNumVector.at(0);
	for (int i = 0; i < randomNumVector.size(); i++) {
		// Finds the minimum number from all the random numbers generated
		if (randomNumVector.at(i) < _minimum) {
			_minimum = randomNumVector.at(i);
		}
		// Finds the maximum number from all the random numbers generated
		if (randomNumVector.at(i) > _maximum) {
			_maximum = randomNumVector.at(i);
		}
	}
}

// Normalize a number between 0 and 1 using the minimum and maximum in the random numbers vector
double Normalize(long num) {
	return ((double)num - _minimum) / (_maximum - _minimum + 1.0);
}

// Instantiates the normalize vector by normalizing the random number vector values
void NormalizeVector() {
	for (int i = 0; i < randomNumVector.size(); i++) {
		normalizedVector.push_back(Normalize(randomNumVector.at(i)));
	}
}

// Returns the mean of the normalize vector values
double Mean() {
	double total = 0;
	for (int i = 0; i < normalizedVector.size(); i++) {
		// Add all the normalize vector values
		total += normalizedVector.at(i);
	}
	return total / normalizedVector.size();
}

// Instantiates a bin array by multiplying the normalized vector values by 100, casting the value to an int for the index, and adding 1 to value
void Bins() {
	for (int i = 0; i < normalizedVector.size(); i++) {
		binArray[static_cast<int> (normalizedVector.at(i) * 100)]++;
	}
}

// Determines the total numbers the random number generator produces before repeating itself
void Period(){
	long period;
	bool isFound = false;
	for (int i = 1; i < randomNumVector.size(); i++) {
		// When a random number equals the first random number in random number vector, the period equals the position i + 1 (account for the 0 index)
		if(randomNumVector[i] == randomNumVector[0]) {
			period = i;
			isFound = true;
			break;
		}
	}
	// If the period is found, print the period on the screen. Else print that the period was not found
	if (isFound){
		cout << "The period is: " << period << endl;
	} else if (!isFound) {
		cout << "The period was not found" << endl;
	}
}

int main() {
	// Store the number of times the random number generator will be called
	cout << "Enter the amount random numbers that will be printed to the screen: " << endl;
	cin >> _numIterations;

	PopulateVector();
	FindMinAndMax();
	NormalizeVector();
	// Output the mean
	double mean = Mean();
	cout << "The mean of " << randomNumVector.size() << " is: " << mean << endl;
	// Output the period
	Period();
	//Output the bins
	Bins();
	for (int i = 0; i < 100; i++) {
		cout << "Bin " << i << ": " << binArray[i] << endl;
		//cout << binArray[i] << endl;
	}

	return 0;
}
