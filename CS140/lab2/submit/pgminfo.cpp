//Jacob Isber
//Lab2::pgminfo
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
//The average
	double average = 0;
//Type of file
	string fileType;
//Vector of ints
	vector <int > numPixles;

//Error checks if correct file is input.
	cin >> fileType; 
	if(fileType != "P2") {
		cerr << "Bad PGM file -- first word is not P2" << endl;
		fileType.clear();
		return -1;
	}

//Inputs the y, x, and the the max intensity 
	cin >> height >> width >> colorMax;

//Error checks to make sure height and or width is not <= 0
		if(height <= 0 || width <= 0) {
			cerr << "Bad PGM file -- No row specification" << endl;
			return -1;
		}

//Error checks to make sure max intenisty is != 255
		if(colorMax != 255) {
			cerr << "error statement: intense" << endl;
			return -1;
		}

//Counts the number of pixles. 
	while (cin >> temp) {

		numPixles.push_back(temp);
	} 

//Error checks to make sure the right amount of pixles are present.
		if(numPixles.size() != (width * height)) {
			cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
			return -1;
		}
//Error checks to make sure pixles are in range
		for(int i =0; i < numPixles.size();i++) {
			if(numPixles.at(i) < 0 || numPixles.at(i) > 255) {
				cerr << "Bad PGM file -- pixel " << i << " is not a number between 0 and 255" << endl;
					return -1;
			}
		}

//Computes the needed average
	for(int i = 0; i < numPixles.size(); i++) {
		average += numPixles.at(i);
	}

//Computes the average
	average =  average / numPixles.size();

//Outputs needed information.
	printf("%-10s %8d\n", "# Rows:", width);
	printf("%-10s %8d\n", "# Columns:", height);
	printf("%-10s %8d\n" ,"# Pixels:", numPixles.size());
	printf("%-10s %8.3lf\n", "Avg Pixel:", average);




	return 0;
}
