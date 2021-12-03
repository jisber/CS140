//Jacob Isber
//Lab9 part B, Shape Shifter
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Shifter {

	public:

	bool Read_Grid_And_Shapes(int argc, const char *argv[]);

//Applies the shape test if it fits in grid boundry.

	bool Apply_Shape(int index, int r, int c);

	bool Find_Solution(int index);

	void Print_Solution() const;

	protected:
	
	vector <string> Grid;                   
	vector < vector <string> > Shapes;    
	//Push_back and print in reverse order
	vector <int> Solution_Rows;            
	vector <int> Solution_Cols;            

};



int main(int argc, const char *argv[]) {
	Shifter shifter;

		shifter.Read_Grid_And_Shapes(argc, argv);
		
		int index, row, col;
		while(1) {
			cout << "Index, row, col";
			cin >> index >> row >> col;

			if(!shifter.Apply_Shape(index, row, col)) {
				cout << "THIS DID NOT WORK!!!\n\n";
			}
	}
	return 0;
}

bool Shifter::Read_Grid_And_Shapes(int argc, const char *argv[]) {

	string line;
	
	for(int i = 1; i < argc; i++) {
		Grid.push_back(argv[i]);
	}
/*	
	for(size_t i = 0; i < Grid.size(); i++) {	
		if(Grid[0].size() != Grid[i].size()) {
			return false;
		}
	}

	for(size_t i = 0; i < Grid.size(); i++) {
		for(size_t j = 0; j < Grid[i].size(); j++) {
			if(Grid[i][j] != '0' && Grid[i][j] != '1') {
				return false;
			}
		}
	}
*/	
	vector <string> temp;
	stringstream ss;
	while(getline(cin, line)) {	
		if(!line.empty()) {
			ss.str(line);
			line.clear();
			while(ss >> line) {
				temp.push_back((line));
				line.clear();
			}
			Shapes.push_back(temp);
			temp.clear();
			ss.clear();
				
		}
		else {
			break;
		}
	}
	
/*
	cout << "The Grid: " << endl;
	cout << endl;
	for(size_t i = 0; i < Grid.size(); i++) {
		for(size_t j = 0; j < Grid[i].size(); j++) {
			cout << Grid[i][j];	
		}
		cout << endl;
	}
	*/
/*	cout << "Shapes: " << endl;
	for(size_t i = 0; i < Shapes.size(); i++) {
		for(size_t j = 0; j < Shapes[i].size(); j++) {
			cout << Shapes[i][j] << endl;
		}
		cout << endl;
	}
	
*/
	return true;
}
	bool Shifter::Apply_Shape(int index, int r, int c) {
	//	int rcounter= r; 
	//	int ccounter = c;
	
		for(size_t i = 0; i < Grid.size(); i++) {
		for(size_t j = 0; j < Grid[i].size(); j++) {
			cout << Grid[i][j];	
		}
		cout << endl;
	}

		if((size_t) r < 0 || (size_t) r > Grid.size() - 1) return false;
		if((size_t) c < 0 || (size_t) c > Grid[0].size() - 1) return false;
		if((size_t) index < 0 || (size_t) index > Shapes.size() - 1) return false;
		
		//if(r + Shapes[index].size() > Grid.size()) return false;
	//	if(c + Shapes[index][0].size() > Grid[0].size()) return false;

		for(size_t i = 0; i < Shapes[index].size(); i++) {
			for(size_t j = 0; j < Shapes[index][i].size(); j++) {
				if(Shapes[index][i][j] == '1') {
					if(c + j > Grid[r].size()) return false;
					else if(r + i > Grid.size()) return false;
					 if((Grid[r + i][c + j] == '1')) Grid[r + i][c + j] = '0';
					else Grid[r + i][c + j] = '1';
				}
			}
		}
		
	for(size_t i = 0; i < Grid.size(); i++) {
		for(size_t j = 0; j < Grid[i].size(); j++) {
			cout << Grid[i][j];	
		}
		cout << endl;
	}

		return true;
	}

	bool Shifter::Find_Solution(int index) {
	/*	
		if(index == Shapes.size()) {
			for(int i = 0; i < Grid.size(); i++){
				for(int j = 0; j < Grid[i].size(); j++) {
					if(Grid[i][j] == '0') {
						return false;
					}
					return true;
				}
			}
		}
		for(int i = 0; i < Grid.size(); i++){
			for(int j = 0; j < Grid[i].size(); j++) {
				if(Apply_Shape(index, i, j) {
						Find_so
				
    */
		return true;
	}
