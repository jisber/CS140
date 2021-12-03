//Jacob Isber
//Lab2::hflip
//9/6/19
//Daniel Nichols hellped me with this code for the error statements lines (39 - 54) and (113 - 116).

#include <iostream>
#include <string>
#include <cstdlib> 
#include <vector>
#include <stdio.h>
using namespace std;


int main() {

//Height = y, Width = x, colorMax = pixleintenisty, temp is just a temporary value
	int height, width, colorMax; 
	int temp; 
//Type of file
	string fileType;
//Vector of ints
	
	vector <int> ttemp;

//1D and 2D vecotrs 
	vector <int > numPixles;
	vector < vector < int > > tPixle;

	int counter = 0;

//Error checks if correct file is input.
	cin >> fileType; 
	if(fileType != "P2") {
		cerr << "Bad PGM file -- first word is not P2" << endl;
		fileType.clear();
		return -1;
	}

//Inputs and checks the y, x, and the the max intensity 
	if(!(cin >> height)) {
		 cerr << "Bad PGM file -- No column specification" << endl;
		 return -1;
	}

	if(!(cin >> width)) {
		cerr << "Bad PGM file -- No row specification" << endl;
		return -1;
	}

	if(!(cin >> colorMax)) {

		return -1;
		
	}




//Error checks to make sure height and or width is not <= 0
		if(height <= 0)  {
			cerr << "Bad PGM file -- No column specification" << endl;
			return -1;
		}
		if(width <= 0) {
			cerr << "Bad PGM file -- No row specification" << endl;
			return -1;

		}

//Error checks to make sure max intenisty is != 255
		if(colorMax != 255) {
			cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
			return -1;
		}
		

//Keeps count of pixels. 
	while (cin >> temp) {

		numPixles.push_back(temp);	

	} 

//Lines 82 - 99 is for formating 
	cout << "P2" << endl;
	cout << height << " " << width << endl;
	cout << colorMax << endl;

//This loads the current 1D vector into a 2D vector the counter is there to keep track of the amount of times it loops.
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			ttemp.push_back(numPixles[counter]);
			counter++;
		}
		tPixle.push_back(ttemp);
		ttemp.clear();
	}

//Outputs the correct format	
	for(int i = 0; i < width; i++) {
		for(int j = height - 1; j >= 0; j--) {
			cout << tPixle[i][j] << endl;
		}
	}

//Error checks to make sure pixles are in range
		for(unsigned int i =0; i < numPixles.size();i++) {
			if(numPixles.at(i) < 0 || numPixles.at(i) > 255) {
				cerr << "Bad PGM file -- pixel " << i << " is not a number between 0 and 255" << endl;
					return -1;
			}
		}
	//Error checks to make sure the right amount of pixles are present.
		if(numPixles.size() < (width * height)) {
			cerr << "Bad PGM file -- pixel " << numPixles.size() << " is not a number between 0 and 255" << endl;
		}
			if(numPixles.size() > (width * height)) {
			cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
		}
	
	return 0;
}
