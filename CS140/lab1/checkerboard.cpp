//Jacob Isber
//Checkerboard 
//8/28/19


#include <iostream>

using namespace std;

int main() {

	int R, C, CS, W; //R = Number of rows, C = Number of columns, SC = Starting Character, CS = The cycle size
	char SC;
	
	int temp = 0; //Temporary value
	char newVal; //Second temporary value
	int counter = 0; //Counter

	cin >> R >> C >> SC >> CS >> W; //Reads in the values and characters
	
	if(!cin) { //I got this error check from stack overflow. Not 100 percent sure how it works though. Im assuming it is saying if cin is empty error.
		cerr << "usage: checkerboard  - stdin should contain R, C, SC, CS and W" << endl;
		return -1;
	}

	int temp2 = SC + CS; //Converts SC + CS into an int

	if(R <= 0 || C <= 0 || CS <= 0 || W<= 0) { //Checks to see if any of the values inputed are less than or equal to zero
		return -1;
	}

	if(temp2 > 127) { //Checks to make sure SC + CS does not go over the ASCII value 127
		return -1;
	}
	
	for(int i = 0; i < R * W; i++) { //Controls the R row
		for(int j = 0; j < C; j++) { //Controls C column
			for(int k = 0; k < W; k++) { // Controls the width
				newVal = SC + (counter + j)% CS; //This is the given formula. 
				cout << newVal; //Outputs altered value.
			
				}
		}
		cout << endl;
			
		//Repeats the same row over and over to meet the conditions of the example.
		if(i % W == W - 1 ) {
			counter++;
		}
	}

return 0;
}
