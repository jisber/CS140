//Jacob Isber
//Lab2::Bigwhite.cpp
//9/7/19
//Just creats a blank picture
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) {

//Makes sure user doesn't input more that 3 inputs
	if(argc != 3) { 
		cerr << "usage: bigwhite rows cols" << endl;
		return -1;
	}

//White pixel count
	int input = 255;

//x,y which is the row and column. atoi converts char into int.
	int x = atoi (argv[1]);
	int y = atoi (argv[2]); 

//Error checks to make sure x or y are not <= 0.
	if(x <= 0 || y <= 0) {
		cerr << "usage: bigwhite rows cols" << endl;
		return -1;
	}

//Makes sure input is an int.
	if(!((x) || (y))) {
		cerr << "usage: bigwhite rows cols" << endl;
		return -1;
	}

//Initiliazes a 2d array
	int a[x][y];

//Couts formating
	cout << "P2" << endl;
	cout << y << " " << x << endl;
	cout << input << endl;

//Lines 47 -60, outputs the array in a row/column format.
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
		 a[i][j] = input;
		}
	}


	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
		cout <<  a[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
