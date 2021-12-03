//Jacob Isber
//Lab5 Bitmatrix
//A couple of TA's helped me with this lab, such as Bhaskar Gaur, Daniel Nicholes, Chaohui Zheng and one more I could not remember. 
//This lab is just having fun with bit matrixe's

#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.hpp"
using namespace std;


//This is the bitmatrix constructor
Bitmatrix::Bitmatrix(int rows, int cols)
{
	if(rows <= 0) {
		throw (string) "Bad rows";
	}

	if(cols <= 0) {
		throw (string) "Bad cols";
	}

	M.resize(rows);
	for(size_t i = 0; i < M.size(); i++) {
		for(int j = 0; j < cols; j++) {
			M[i] = M[i] + '0';			
		}
	}
}

//This opens the Bitmatrix gets rid of the spaces. 
Bitmatrix::Bitmatrix(const string &fn)
{
	ifstream fin;
	string line, temp;	
	fin.open(fn.c_str());
		
		if(fin.fail()) {
			throw (string) "Can't open file";
		}
	while(getline(fin, line)){
		temp = "";
		for(size_t i = 0; i < line.size(); i++) {
			if(line[i] == '0' || line[i] == '1') {
				temp += line[i];
			}
			else if (line[i] != ' ') {
				throw (string) "Bad file format";
			}
		}
		if(temp != "") {
			M.push_back(temp);
		}
	}
}

//This is the copy function that makes a copy of the matrix. Daniel hellped me with this.
Bitmatrix *Bitmatrix::Copy() const
{
	int row = M.size();
	int col = M[0].size();
	Bitmatrix *p;
	p = new Bitmatrix(row, col);

	for(size_t i = 0; i < M.size(); i++) {
		for(size_t j = 0; j < M[0].size(); j++) {
			p -> Set(i, j, M[i][j]);
		}
	}
	
	 return p;

}

//This Writes the bits to a file.
bool Bitmatrix::Write(const string &fn) const
{
	ofstream fout; 
	fout.open(fn.c_str());
	
	if(fout.fail()) {
			throw (string) "Can't open file";
		}
		
	for(size_t i = 0; i < M.size(); i++) {
		fout << M[i] << endl;
	}

  return true;
}

//This prints out the the rows and cols.
void Bitmatrix::Print(size_t w) const
{
	for(size_t i = 0; i < M.size(); i++) {
		if(w != 0) {
			if(i != 0 && i % w == 0 && i != M.size()) {
				printf("\n");
			}
		}
		for(size_t j = 0; j < M[i].size(); j++) {
			if(w != 0) {
				if( j % w == 0 && j != 0 && j != (M[i].size()) ) {
				printf(" ");
			}
		}
		printf("%c", M[i][j]); 
		}
		printf("\n");
	}
}

//This is the PGM function, Daniel also helped me with this lab, as well as two kids in office hours mentioned the nested nested for loop.
bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
	int row, col, pixnum;
	ofstream fout;
	vector <vector <int> > pixvec;

	fout.open(fn.c_str());
	
	if(fout.fail()) {
		return false;
	}
	if(p <= 0 || border < 0 || M.size() <= 0) {
		return false;
	}

	fout << "P2" << endl;
//These are the formulas that start me at the beginning of each matrix
	row = (M.size() * p + M.size() * border) + border;
	col = (M[0].size() * p + M[0].size() * border) + border;

	fout << col << " " << row << endl;
	fout << "255" << endl;

	pixvec.resize(row);
	for(size_t i = 0; i < pixvec.size(); i++) {
		for(int j = 0; j < col; j++) {
			pixvec[i].push_back(0);
		}
	}

	for(size_t i = 0; i < M.size(); i++) {
		for(size_t j = 0; j < M[i].size(); j++) {
			for(size_t k = 0; k < pixvec.size(); k++) {
				for(size_t t = 0; t < pixvec[k].size(); t++) {
					
					if(M[i][j] == '0') {
						pixnum = 255;
					}

					else {
						pixnum = 100;
					}
//This is the formula that finds where you need to start and end inside the border
					if(k >= (border * (i + 1) + (p * i)) && k < (border * (i + 1) + (p * i) +p) ) {
						if(t >= (border * (j + 1) + (p * j)) && t < (border * (j + 1) + (p * j) + p)) {
							pixvec[k][t] = pixnum;
						}	
					}					
				}
			}
		}
	}
	

	for(size_t i = 0; i < pixvec.size(); i++) {
		for(int j = 0; j < col; j++) {			
			fout << pixvec[i][j] << " ";
		}
		fout << endl;
	}

 return true;
}
//Number of rows
int Bitmatrix::Rows() const
{
  return M.size();
}
//Number of cols                           
int Bitmatrix::Cols() const
{
  return M[0].size();
}
 
//Returns val at a given point
char Bitmatrix::Val(int row, int col) const
{
	int i = M.size();
	int j = M[0].size();

	if(row < 0 || col < 0) {
		return 'x';
	}
	if(row > i || col > j) {
		return 'x';
	}

  return M[row][col];
}
//Sets the val at a given point           
bool Bitmatrix::Set(int row, int col, char val)
{ 
	int r1, c1;
	char num;
	r1 = M.size();
	c1 = M[0].size();
	if(row > r1 || row < 0 || col > c1 || col < 0) {
		return false;
	}
	if(val != 0 && val != 1 && val != '0' && val != '1') {
		return false;
	}

	if(val == 0) {
		num = '0';
		M[row][col] = num;
	}
	else if(val == 1) {
		num = '1';
		M[row][col] = num;
	}
	else {
		M[row][col] = val;
	}
	
	return true;
}
//Swaps the given rows         
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
	if((size_t)r1 > M.size() || (r1 < 0) || size_t(r2) > M.size() || r2 < 0) {
		return false;
	}
	string temp;

	temp = M[r1];
	M[r1] = M[r2];

	M[r2] = temp;


  return true;
}


//This plus equals function takes 2 rows and preforms an Xor on it. (I took this method straight from TA's note)
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{ 
	int row0, row1;
	stringstream str;
	string temp = "";

	if((size_t)r1 >=  M.size() || (r1 < 0) || (size_t)r2 >= M.size() || r2 < 0) {
		return false;
	}
	

//I had to employ this method to deal with base 10 to base 2;
//Character - '0' + 0 = num
	for(size_t i = 0; i < M[r1].size(); i++) {
		if(M[r1][i] == '0') {
			row0 = 0;
		}
		else if(M[r1][i] == '1') {
			row0 = 1;
		}
		if(M[r2][i] == '0') {
			row1 = 0;
		}
		else if(M[r2][i] == '1') {
			row1 = 1;
		}

		row0 = row0 ^ row1;
		
		if(row0 == 0) {
			temp += '0';
		}
		else if(row0 == 1) {
			temp += '1';
		}
	}		
		M[r1] = temp;
	
  return true;
}
      

//This will calculate the sum of two given matricies, Bhaskar Gaur helped me with this code.
Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
	Bitmatrix *temp;
	Bitmatrix *finalsum;

	if(a1 -> Rows() != a2 -> Rows() || a1 -> Cols() != a2 ->Cols()) {
		return NULL;
	}
	finalsum = new Bitmatrix(a1 -> Rows(), a1 -> Cols());
	temp = new Bitmatrix(2, a1 ->Cols());	 
	for(int i = 0; i < a1 ->Rows(); i++) {
		for(int j = 0; j < a1 -> Cols(); j++) {
			temp  -> Set(0, j, a1 -> Val(i, j));
			temp -> Set(1, j, a2 -> Val(i, j));
		}
		temp -> R1_Plus_Equals_R2(0,1);
		for(int j = 0; j < a1 -> Cols(); j++) {
			finalsum -> Set(i, j, temp ->Val(0,j));		
		}
	}


  return finalsum ;
}

//This will take the 2 matricies and multiply them together
Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{

	Bitmatrix *pm;
	int mult1, mult2, temp1, temp2;

	if(a1 -> Cols() != a2 -> Rows()) {
		return NULL;
	}
	pm = new Bitmatrix(a1 -> Rows(), a2 -> Cols());
	
	for(int i = 0; i < a1 -> Rows(); i++) {
		for(int j = 0; j < a2 -> Cols(); j++) {
			temp2 = 0;
//This is the same method to deal with base 2
			for(int k = 0; k < a1 -> Cols(); k++) {
				if(a1 -> Val(i, k) == '0') {
					mult1 = 0;
				}
				else if(a1 -> Val(i, k) == '1'){
					mult1 = 1;
				}
				if(a2 -> Val(k, j) == '0') {
					mult2 = 0;
				}
				else if( a2 -> Val(k, j) == '1') {
					mult2 = 1;
				}
				temp1 = mult1 * mult2;

				temp2 = temp2 + temp1;
				}
//This is the method that was told to use in notes.
				temp2 = temp2 % 2;
				char num;

				if(temp2 == 0) {
					num = '0';
				}
				else if (temp2 == 1) {
					num = '1';
				}
				pm->Set(i, j, num);
			}
		}

  return pm;
}

//This is the sub matrix. A ta helped me with the error checks.
Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
	Bitmatrix *pm;	
	pm = new Bitmatrix(rows.size(), a1 -> Cols());
	if(rows.size() <= 0) {
		return NULL;
	}
	
	for(size_t i = 0; i < rows.size(); i++) {
		if(rows[i] < 0 || rows[i] > (a1 ->Rows())) {
			return NULL;
		}
	}

	for(size_t i = 0; i < rows.size(); i++) {
		for(int j = 0; j < a1 -> Cols(); j++) {
			pm -> Set(i, j, a1 ->Val(rows[i],j)); 

		}
	}
	return pm;
}

//This preforms the inverse of a matrix. Daniel also helped me with this. 
Bitmatrix *Inverse(const Bitmatrix *m)
{
	Bitmatrix *pm;	
	Bitmatrix *c;
	c = m -> Copy();
	int temp = 0;
	bool found = false;
	if(m -> Rows() != m -> Cols()) {
		return NULL;
	}

	pm = new Bitmatrix(m -> Rows(), m -> Cols());
	
	while(temp < c -> Cols()) {
		pm -> Set(temp, temp, 1);
		temp++;
	}
	for(int i = 0; i < c -> Rows(); i++) {
		if(c -> Val(i, i) != '1') {
			found = false;
			for(int j = i + 1; j < c -> Rows(); j++) {
				if(c -> Val(j, i) == '1') {
					c -> Swap_Rows(i, j);
					pm -> Swap_Rows(i, j);
					found = true;
					break;
				}
			}
			
			if(found != true) {
				return NULL;
			}
		}
		for(int j = i + 1; j < c -> Rows(); j++) {	
			if(c -> Val(j, i) == '1') {
				c -> R1_Plus_Equals_R2(j, i);
				pm -> R1_Plus_Equals_R2(j, i);
			}
		}
	}
	for(int i = c -> Rows() - 1; i >= 0; i--) {
		for(int j = i + 1; j < c -> Rows(); j++) {
			if(c -> Val(i, j) == '1') {
				c -> R1_Plus_Equals_R2(i, j);
				pm -> R1_Plus_Equals_R2(i, j);
	
			}
		}
	}

  return pm;;
}


//This resizes the table to the right size
BM_Hash::BM_Hash(int size)
{
	if(size <= 0) {
		throw (string) "Bad size";
	}
	Table.resize(size);
}

//This is the hash function that assigns and store keys 
bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
	HTE curr;
	curr.key = key;
	curr.bm = bm;
	
	unsigned int h = 5381;
	for(size_t i = 0; i < key.size(); i++){
		h = (h << 5) + h + key[i];
	}
	h %= Table.size();
	if(Table[h].size() == 0) {
		Table[h].push_back(curr);
	}
	else if(Table[h].size() == 1){
		for(size_t i = 0; i < Table[h].size(); i++) {
			if(Table[h][i].key == curr.key) {
			return false;
			}
		}
			Table[h].push_back(curr);
		}
	

  return true;
}
//This recals the stored hashed key
Bitmatrix *BM_Hash::Recall(const string &key) const
{
	unsigned int h = 5381;
	for(size_t i = 0; i < key.size(); i++){
		h = (h << 5) + h + key[i];
	}
	h %= Table.size();
	if(Table[h].size() == 0) {
		return NULL;
	}
	else  {
		for(size_t i = 0; i < Table[h].size(); i++) {
			if(Table[h][i].key == key) {
				return Table[h][i].bm;	
			}
		}
	}
  return NULL;
}
//This will Pushback the table size to the vector of RV     
vector <HTE> BM_Hash::All() const
{

  vector <HTE> rv;

	for(size_t i = 0; i < Table.size(); i++) {
		for(size_t j = 0; j < Table[i].size(); j++) {
			rv.push_back(Table[i][j] );
		}
	}


 return rv;
}
