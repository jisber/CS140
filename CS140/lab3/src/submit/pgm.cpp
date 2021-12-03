//Jacob Isber
//Lab3
//9-13-19
#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool Pgm::Read(const std::string &file)
{
  ifstream fin;
  string s;
  size_t i, j, r, c, v;

  fin.open(file.c_str());
  if (fin.fail()) return false;
  
  if (!(fin >> s)) return false;
  if (s != "P2") return false;
  if (!(fin >> c) || c <= 0) return false;
  if (!(fin >> r) || r <= 0) return false;
  if (!(fin >> i) || i != 255) return false;

  Pixels.resize(r);
  for (i = 0; i < r; i++) {
    Pixels[i].clear();
    for (j = 0; j < c; j++) {
      if (!(fin >> v) || v > 255) return false;
      Pixels[i].push_back(v);
    }
  }
  if (fin >> s) return false;
  fin.close();
  return true;
}

bool Pgm::Write(const std::string &file) const {

//Opens the file
	ofstream fout;
	fout.open(file.c_str());

//Counter
	int l = 0;

//Error checks to make sure vector is filled
	if((Pixels.empty())) {
		return false;
	}

//Prints out P2 at the start
	fout << "P2" <<	endl;

//Assignes row with the number of rows within the vector
	int row = Pixels.size();

//Assignes col with the number of columns within the vector
	int col = Pixels[row - 1].size();

//Gets total # of pixels
	int totalPix = row * col;

	fout << col << " " << row << endl;

	
	fout << "255" << endl;	

//Outputs to a file the image
	for(size_t i = 0; i < Pixels.size(); i++) {
		for(size_t j = 0; j < Pixels[i].size(); j++) { 
			l++;
			fout << Pixels[i][j];
			if(l % 20 == 0) {
				fout << endl;
			}
			else 
				if(l != totalPix) {
					fout << " ";
				}
		}	
		
	}
	if(!(l % 20 == 0)) {
			fout << endl;
			}


	return true;
}
bool Pgm::Create(size_t r, size_t c, size_t pv) {

//Clears the pixel
	Pixels.clear();

	if(pv > 255) {
		return false;
	}

	if(!(r) || r <= 0) {
		return false;
	}
	if(!(c) || c <= 0) {
		return false;
	}

//Resizes the vector to r
	Pixels.resize(r);

//Resizes to the number of columns
	for(size_t i = 0; i < Pixels.size(); i++) 	{
		Pixels[i].resize(c);
	}	

//Sets pixels equal to pv
	for(size_t i = 0; i < Pixels.size(); i++) {
		for(size_t j = 0; j < Pixels[i].size(); j++) {
			Pixels[i][j] = pv; 
		}
	}

	return true;
}
bool Pgm::Clockwise() {
//Temporary vector to pushback rows	
	vector <int> temp;
//Temporary 2d vector to store row and cols
	vector< vector<int> > tem;
//Inilizes the number of rows.
	int row = Pixels.size();

//This is the forumal I used to rotate cw
	for(size_t i = 0; i < Pixels[0].size(); i++) {
		temp.clear();
		for(size_t j = 0; j < Pixels.size(); j++){
			temp.push_back( Pixels[row - 1 - j][i]);
		}
		tem.push_back(temp);
	}
	Pixels.clear();
	Pixels = tem;
	

	return true;
}
bool Pgm::Cclockwise() {
//Temporary vector to puchback rows	
	vector <int> temp;
//Temporary 2d vector to store row and cols
	vector< vector<int> > tem;
//Initilizes the rows
	int row = Pixels.size();
//Initilizes the columns
	int col = Pixels[row - 1].size();

//Rotates CCW
	for(size_t i = 0; i < Pixels[0].size(); i++) {
		temp.clear();
		for(size_t j = 0; j < Pixels.size(); j++){
			temp.push_back( Pixels[j][col - 1 -i]);
		}
		tem.push_back(temp);
	}
	Pixels.clear();
	Pixels = tem;
	
	return true;
}
bool Pgm::Pad(size_t w, size_t pv) {

	if(!(pv) || pv > 255) {
		return false;
	}
	if(!(w) || w <= 0) {
		return false;
	}

//Initilizes the rows and columns
	size_t row = Pixels.size();
	size_t col = Pixels[row -1].size();

//Resizes to make room for the new rows and cols
	Pixels.resize(Pixels.size() + (w * 2));
	for(size_t i = 0; i < Pixels.size(); i++) {
		Pixels[i].resize(col + (w * 2));
	}

//Moves the image to the middle.
	for(int i = row; i >= 0; i--) {
		for(int j = col; j >= 0; j--) {
			Pixels[i + w][j + w] = Pixels[i][j];
		}
	}

//Lines 197 - 220 just fills in the pixels.
	for(size_t i = row + w; i < Pixels.size(); i++) {
		for(size_t j = 0; j < Pixels[i].size(); j++) {
			Pixels[i][j] = pv;
		}
	}

	for(size_t i = 0; i < w; i++) {
		for(size_t j = 0; j < Pixels[i].size(); j++) {
			Pixels[i][j] = pv;	
		}
	}

	for(size_t i = 0; i < Pixels.size(); i++) {
		for(size_t j = col + w; j < Pixels[i].size(); j++) {
			Pixels[i][j] = pv;
		}
	}

	for(size_t i = 0; i < Pixels.size(); i++) {
		for(size_t j = 0; j < w; j++) {
			Pixels[i][j] = pv;
		}
	}

	return true;
}
bool Pgm::Panel(size_t r, size_t c) {
	if(!(r) || r <=0) {
		return false;
	}
	if(!(c) || c <= 0) {
		return false;
	}
//Initilies the row
	int row = Pixels.size();
//Inlitlzes the columns
	int col = Pixels[row -1].size();

//Resizes the vector to the deal with rows and cols
	Pixels.resize(Pixels.size() * r );
	for(size_t i = 0; i < Pixels.size(); i++) {
		Pixels[i].resize(col * c);
	}

//Fills in the rows
	for(size_t i = row; i < Pixels.size(); i++) {
		for(int j = 0; j < col; j++) {
			Pixels[i][j] = Pixels[i - row][j];	
		}
	}
//Fills in the cols
	for(size_t i = 0; i < Pixels.size(); i++) {
		for(size_t j = col; j < Pixels[i].size(); j++) {
			Pixels[i][j] = Pixels[i][j - col];
		}
	}


	return true;
}
bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols) {
	
	if(!(r) || r <= 0) {
		return false;
	}
	if(!(c) || c <= 0) {
		return false;
	}
	if(!(rows) || rows <= 0) {
		return false;
	}
	if(!(cols) || cols <= 0) {
		return false;
	}
	if(c + cols > Pixels[0].size() || r + rows> Pixels.size()) { 
		return false;
	}
//Creats 2 vectors 
	vector < vector <int> > tem;
	vector <int> temp;

//grabs the necessary pixels needed to crop stores it into the vector then back out.
	for(size_t i = r; i < (r + rows); i++) {
		temp.clear();
		for(size_t j = c; j < (c + cols); j++) {
			temp.push_back(Pixels[i][j]);
		}
		tem.push_back(temp);
	}
	Pixels.clear();
	Pixels = tem;


	return true;
}

