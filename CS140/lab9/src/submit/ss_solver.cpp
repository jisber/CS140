//Jacob Isber
//Lab9 part B, Shape Shifter
//Thomas as well as another TA helped me with this lab. They hellped witt Applied_Shape function.
//Lab revision 1.5
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Shifter {

	public:

		bool Read_Grid_And_Shapes(int argc, const char *argv[]);

		bool Apply_Shape(int index, int r, int c);

		bool Find_Solution(int index);

		void Print_Solution() const;

		//	protected:

		vector <string> Grid;                   
		vector < vector <string> > Shapes;    
		vector <int> Solution_Rows;            
		vector <int> Solution_Cols;            

};


int main(int argc, const char *argv[]) {
	Shifter shifter;

	shifter.Read_Grid_And_Shapes(argc, argv);

	if(shifter.Find_Solution(0))
		shifter.Print_Solution();
	return 0;
}

//Loads the grid and shapes.
bool Shifter::Read_Grid_And_Shapes(int argc, const char *argv[]) {

	string line;

	for(int i = 1; i < argc; i++) {
		Grid.push_back(argv[i]);
	}
//This loads the shapes while ignoring the space. thats whas stringstream was for.
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

	return true;
}
//This will apply the shape and test if it fits in the grid or not. This will also invert the the number inside the grid where the shape is applied
bool Shifter::Apply_Shape(int index, int r, int c) {

	for(size_t i = 0; i < Shapes[index].size(); i++) {
		for(size_t j = 0; j < Shapes[index][i].size(); j++) {
			if(Shapes[index][i][j] == '1') {
				if(c + j > Grid[r].size() - 1) 
					return false;
				else if(r + i > Grid.size() - 1) 
					return false;
				else  if((Grid[r + i][c + j] == '1')) 
					Grid[r + i][c + j] = '0';
				else Grid[r + i][c + j] = '1';
			}
		}
	}

	return true;
}
//This is the find solution function. It will find a solution bases on apply shape.
bool Shifter::Find_Solution(int index) {

//Base case that checks if every shape has been used
	if((size_t) index == Shapes.size()) {
		for(size_t i = 0; i < Grid.size(); i++){
			for(size_t j = 0; j < Grid[i].size(); j++) {
				if(Grid[i][j] == '0') {
					return false;
				}
			}
		}
		return true;
	}
//This applies
	for(size_t i = 0; i < Grid.size(); i++){
		for(size_t j = 0; j < Grid[i].size(); j++) {
			if((Apply_Shape(index, i, j) == true)) {
				bool solved = Find_Solution(index + 1);
				if(solved == true) {
					Solution_Rows.push_back(i);
					Solution_Cols.push_back(j);
					return true;
				}
				else {
					Apply_Shape(index, i, j);
				}
			}
			else 
				Apply_Shape(index, i, j);
		}
	}

	return false;
}

//This is the print function that will print everything needed.
void Shifter::Print_Solution() const{
	int counter = 0;

	for(int i = Solution_Rows.size() - 1; i >= 0; i--) {
		for(size_t j = 0; j < Shapes[counter].size(); j++) {
			cout << Shapes[counter][j] << " ";
		
		}
			counter++;
			cout << Solution_Rows[i] << " " << Solution_Cols[i];
			cout << endl;
	}
}
		

