//Jacob Isber
//9/1/19
//Moonglow Lab 
//Sorts through a file and searches for certain key words and computes average / score.


#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	
	string entry, name1 ;	//string iputes for entry and the name of the student.
	double TotalScore = 0, TotalScore1 = 0;		//TotalScore is the total score and TotalScore1 is the average
	int counter = 0;	//Counter
	double temp = 0;	//Temporary value
	
	while(cin >> entry) {  
		if(entry == "AVERAGE") {	//Checks to see if the entry is average.
			do{ //Starts a do while to ensure you do not mess up when average is consecutive
				TotalScore1 = 0;	
				counter = 0;
				while(cin >> entry) { 
					if(entry[0] >= 48 && entry[0] <= 57 ) { //This is how I checked to see if my entry was a number. I Found this method on stack overflow.
					stringstream(entry) >> temp; //Converts my string to an int in c++98. I found this method on stack overflow.
					TotalScore1 = TotalScore1 + temp; //Average + current value.
					entry.clear(); 
					}

					else {
						break;
					}
							
				counter++;	//A counter that keeps count for the total numbers found within the file.
				}
			
				if(counter > 0) { //Ensures that you do not divide by 0.
					TotalScore1 = TotalScore1 / counter;
					TotalScore = TotalScore + TotalScore1;
				}	
				if(entry == "AVERAGE") {
					continue;
				}
			}while(entry == "AVERAGE"); 
			}
	

		if(entry == "NAME") { //Checks if entry is a string of characters to form a name.
			cin >> entry;
			name1 = entry;
			entry.clear();
		}
		
		if(entry[0] >= 48 && entry[0] <= 57 ) { 
			stringstream(entry) >> temp;
			TotalScore = TotalScore + temp; //Computes total score and NOT the average.
		}
		if(cin.eof()) {  //Checks the end of file
			break;
		}
	}

	cout << name1 << " " << TotalScore << endl; //Outputs the Name and Score.
return 0;
}
