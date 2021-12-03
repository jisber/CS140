//Jacob Isber
//Lab 9(A) Enum.cpp
//11/5/19
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

void do_enumeration(string &s, int index, int n_ones) {

//Base case
	if(index == s.length()) {
		cout << s << endl;
		return;
	}

//If the remaining number of ones is > the n_ones
	if(s.size() - index  >  n_ones) {
		s[index] = '0';
		do_enumeration(s, index + 1, n_ones);
	}
//Fill the reaming spots with 1's
	if(n_ones != 0) { 
		s[index] = '1';
		do_enumeration(s, index + 1 , n_ones - 1);
		}
		
}

int main(int argc, char *argv[]) {
	
	if(argc != 3) 
		return -1;

	stringstream ss;
	stringstream kk;
	int a, b;
	string str;
	ss.str(argv[1]);
	kk.str(argv[2]);
	
	ss >> a;
	kk >> b;

	str = "";
	for(int i = 0; i < a; i++) {
		 str += '-';
	}
	do_enumeration(str, 0, b);
	return 0;
}
