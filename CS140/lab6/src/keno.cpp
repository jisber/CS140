//Jacob Isber
//Lab6 pt 2 Keno 
//10/21/19
#include "fraction.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdlib.h>
#include <cstdio>

using namespace std;

int main() {
	
	Fraction yy;
	stringstream ss;
	string line;
	double a2b = 0;
	int nob = 0;
	double c4tch, payout, pow, er,  erpb, ertt = 0;

//Reads in the bet and number of balls.
	cin >> a2b >> nob;	

//Prints the correct format
	printf("Bet: %.2f\n", a2b);
	printf("Balls Picked: %d\n",nob);

//Reads in and calls functions from header file
	while(getline(cin, line)) { 
		ss.str(line);
		while(ss >> c4tch >> payout) { 
		yy.Clear();

		yy.Multiply_Binom(80 - nob, 20 - c4tch);
		yy.Multiply_Binom(nob, c4tch);
		yy.Divide_Binom(80, 20);
		pow = yy.Calculate_Product();

		er = pow * payout;
		ertt += er;
		erpb += pow;
//Prints out correct format
		cout << "  Probability of catching " << c4tch << " of " << nob << ": " << pow << " -- Expected return: " << er << endl;
		}
		ss.clear();
	}
	ertt -= a2b;
//Prints out correct format
	printf("Your return per bet: %.2f\n", ertt);
	printf("Normalized: %.2f\n", ertt / a2b);
	
	return 0;
}
