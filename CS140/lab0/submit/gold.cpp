//Jacob Isber
//Gold.cpp

#include <iostream>
using namespace std;

int main() 
{
	
	char map;
	int count;

//Reads in the file until EOF
	while(cin >> map) 
	{
	
		if(map == '.' && map == '-') 
			continue;

//This checks the ASCII table to identify capital letter and gold value
		else if(map >= 65 && map <= 90)  
		{
			count += (map - 64);			
	
		}


	}

	cout << count << endl;
return 0;
}
