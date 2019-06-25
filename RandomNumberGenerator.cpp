// RandomNumberGenerator-LCG.cpp
// CS 4499
// Written By: Katherine Wilsdon
// 22 January 2019
// Dr. Kerby
// Description - Creates a linear congruential pseudorandom number generator(LCG) returning random numbers between 0 and 1
// Cited: Normalize data between 0 and 1: https://stats.stackexchange.com/questions/380276/how-to-normalize-data-between-0-and-1
// Precision: http://umich.edu/~eecs381/handouts/formatting.pdf

#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

double minimum;
double maximum;
long s = 100001;	// seed 0

// linear congruential pseudorandom number generator that returns seed + 1
long int RandLCG(int multiplier, long seed, int adder, long modulus) {
	return (multiplier * seed + adder) % modulus;
}
// Normalize a number between 0 and 1 using the minimum and maximum in a data set
double Normalize(long num) {
	return ( (double)num - minimum) / (maximum - minimum + 1.0);
}

void FindMinAndMax(int numIterations) {
	for (int i = 1; i <= numIterations; i++) {
		// Stores the random number
		long nextRandomNum = RandLCG(61, s, 1, pow(2, 24));
		// Set the minimum and maximum to the first random number
		if (i == 1) {
			minimum = nextRandomNum;
			maximum = nextRandomNum;
		}
		else {
			// Finds the minimum number from all the random numbers generated
			if (nextRandomNum < minimum) {
				minimum = nextRandomNum;
			}
			// Finds the maximum number from all the random numbers generated
			else if (nextRandomNum > maximum) {
				maximum = nextRandomNum;
			}
		}
		// Change the seed to the next random number
		s = nextRandomNum;
	}
}

int main()
{
	int amountOfRandomNum;

	// Store the number of times the random number generator will be called
	cout << "Enter the amount random numbers that will be printed to the screen: " << endl;
	cin >> amountOfRandomNum;

	// Find the minimum and maximum numbers
	FindMinAndMax(amountOfRandomNum);

	// Reset seed
	s = 100001;

	for (int i = 1; i <= amountOfRandomNum; i++) {
		// Stores the random number, normalizes the number between 0 and 1, and output to the user
		long nextRandomNum = RandLCG(61, s, 1, pow(2, 24));
		double normalized = Normalize(nextRandomNum);
		cout.precision(10);
		cout << "Random number " << i << " is: " << normalized << endl;
		// Reset the seed
		s = nextRandomNum;
	}
	return 0;
}
