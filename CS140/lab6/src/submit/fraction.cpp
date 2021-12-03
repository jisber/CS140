//#pragma once
//Jacob Isber
//Lab6 part 1
//10/20/19
#include <iostream>
#include <set>
#include "fraction.hpp"

using namespace std;

//Clears the multisets
void Fraction::Clear() {
	numerator.clear();
	denominator.clear();
}

//Inserts it into the numerator
bool Fraction::Multiply_Number(int n) {
	
	multiset <int>::const_iterator nit;
	if(n <= 0) {
		return false;
	}
	if(n == 1) {
		return true;
	}
	numerator.insert(n);
	nit = denominator.find(n);
	if(nit != denominator.end()) {

		denominator.erase(nit);
		nit = numerator.find(n);
		numerator.erase(nit);
	}

	return true;
}
//Inserts into denominator
bool Fraction::Divide_Number(int n) {
	
	if(n <= 0) {
		return false;
	}
	if(n == 1) {
		return true;
	}
	multiset <int>::const_iterator nit;
	denominator.insert(n);
	nit = numerator.find(n);

	if(nit != numerator.end()) {
		numerator.erase(nit);
		nit = denominator.find(n);
		denominator.erase(nit);
	}
	return true;
}
//Inserts factorial into numerator
bool Fraction::Multiply_Factorial(int n) {
	
	if(n <= 0) {
		return false;
	}

	for(int i = 2; i <= n; i++) {
		Multiply_Number(i);
	}

	return true;
}
//Inserts factorial into denominator
bool Fraction::Divide_Factorial(int n) {
	if(n <= 0) {
		return false;
	}
	
	for(int i = 2; i <= n; i++) {
		Divide_Number(i);
	}
	
	return true;
}
//Impliments the binom function
bool Fraction::Multiply_Binom(int n, int k) {

	if(n <= 0) {
		return false;
	}
	else if(k < 0) {
		return false;
	}
	int temp = n - k;
	Multiply_Factorial(n);
	Divide_Factorial(k);
	Divide_Factorial(temp);	

	return true;
}
//Impliments the binom function
bool Fraction::Divide_Binom(int n, int k) {
	if(n <= 0) {
		return false;
	}
	else if(k < 0) {
		return false;
	}
	int temp = n - k;
	Divide_Factorial(n);
	Multiply_Factorial(k);
	Multiply_Factorial(temp);

	return true;	
}
//Inverts the multiset
void Fraction::Invert() {

	multiset <int> temp;
	multiset <int>::const_iterator nit;

	for(nit = numerator.begin(); nit != numerator.end(); nit++) {
		temp.insert(*nit);	
	}
	numerator.clear();
	for(nit = denominator.begin(); nit != denominator.end(); nit++) {
		numerator.insert(*nit);
	}
	denominator.clear();
	for(nit = temp.begin(); nit != temp.end(); nit++) {
		denominator.insert(*nit);
	}
}
//Prints everything
void Fraction::Print()  const {
	
	multiset <int>::const_iterator nit;
	multiset <int>::const_iterator nip;
	multiset <int>::const_iterator s2l;
	multiset <int>::const_iterator s3l;

	 s2l = numerator.end();
	 s3l = denominator.end();	

	if(numerator.size() == 0 && denominator.size() == 0) {
		cout << "1" << endl;
	}
	
	else {

		if(numerator.size() > 0) {
		 if(!numerator.empty()) {
			 s2l--;
		 }
	
			for(nit = numerator.begin(); nit != numerator.end(); ++nit) {
				cout << *nit;
					if(nit != s2l) {
						cout << " * ";
					}
			}
		}
	
		else {
			cout << "1";
		}

		if(denominator.size() > 0) {
			cout <<  " / ";
			if(!denominator.empty()) {
				 s3l--;
			 }
		for(nip = denominator.begin(); nip != denominator.end(); ++nip) {
			cout << *nip;
			if(nip != s3l) {
				cout << " / ";
			}
		}
		cout << endl;
		}
	
		else {
		cout << endl;
		}
	}

}
//Calculates 
double Fraction::Calculate_Product() const {
	
	double temp = 1;

	multiset <int>::iterator nit;
	multiset <int>::iterator nip;

	for(nit = numerator.begin(); nit != numerator.end(); nit++) {
		temp *= *nit;
	}
	for(nip = denominator.begin(); nip != denominator.end(); nip++) {
		temp /= *nip;
	}

	return temp;
}
