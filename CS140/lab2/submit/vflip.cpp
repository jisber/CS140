//Jacob Isber
//Lab2::vlip
//9/6/19

#include <iostream>
#include <string>
#include <cstdlib> 
#include <vector>
#include <stdio.h>
using namespace std;


int main() {

//Height = y, Width = x, colorMax = pixleintenisty, temp is just a temporary value
	int height, width, colorMax, temp; 
//Type of file
	string fileType;
//Vector of ints
	
	vector <int> ttemp;
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

//Error check the inputs the y, x, and the the max intensity 
	if(!(cin >> height)) {
			cerr << "Bad PGM file -- No column specification" << endl;
		return -1;
	}
	if(!(cin >> width)) {

			cerr << "Bad PGM file -- No row specification" << endl;
		return -1;
	}
	
	cin >> colorMax;
	


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
		

//Counts the number of pixles. 
	while (cin >> temp) {

		numPixles.push_back(temp);	

	} 

//Formating 
	cout << "P2" << endl;
	cout << height << " " << width << endl;
	cout << colorMax << endl;

//Takes my 1D vector with values and loads it into a 2D vector
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			ttemp.push_back(numPixles[counter]);
			counter++;
		}
		tPixle.push_back(ttemp);
		ttemp.clear();
	}

//This will flip the picture horizontally. I found this method 
	for(int i = width - 1; i >= 0; i--) {
		for(int j = 0; j < height; j++) {
			cout << tPixle[i][j] << endl;
		}
	}
	



//Error checks to make sure pixles are in range
		for(int i =0; i < numPixles.size();i++) {
			if(numPixles.at(i) < 0 || numPixles.at(i) > 255) {
				cerr << "Bad PGM file -- pixel " << i << " is not a number between 0 and 255" << endl;
					return -1;
			}
		}
		
		if(numPixles.size() < (width * height)) {
			cerr << "Bad PGM file -- pixel " << numPixles.size() << " is not a number between 0 and 255" << endl;
		}
	

	//Error checks to make sure the right amount of pixles are present.
		if(numPixles.size() > (width * height)) {
			cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
		}
	
	return 0;
}
