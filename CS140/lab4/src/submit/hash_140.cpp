//Jacob Isber
//Lab4
//9/23/19
//This utilizes hash functions and collisions.
//Chaohui Zheng helped with my collision and total probe function. 

#include "hash_140.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cstdio>
using namespace std;

//This will set up the hash table and prepare it for use.
string Hash_140::Set_Up(size_t table_size, const std::string &fxn, const std::string &collision)
{
	
	if(Keys.size() != 0) {
		return "Hash table already set up";
	}

	if(!(table_size)) {
		return  "Bad table size"; 
	}

	if(fxn != "Last7" && fxn != "XOR") {
		return "Bad hash function";
	}

	if(collision != "Linear" && collision != "Double") {
		return "Bad collision resolution strategy";
	}

	
	Keys.resize(table_size);
	Vals.resize(table_size);
	Nkeys = 0;
	
	if(fxn == "XOR") {
		Fxn = 'X';
	}
	if(fxn == "Last7") {
		Fxn = 'L';
	}	

	if(collision == "Linear") {
		Coll = 'L';
	}
	if(collision == "Double") {
		Coll = 'D';
	}

  return "";
}

//This will compute both hash functions and take both collisions and add it to hash table
string Hash_140::Add(const string &key, const string &val)
{
	if(Keys.size() <= 0) {
		return "Hash table not set up";
	}
	if(key == "") {
		return "Empty key";
	}
//Error checks to make sure key is a hex value
	for(size_t i = 0; i < key.size(); i++) {
		if((key[i] >= 48 && key[i] <= 57) || (key[i] >= 65 && key[i] <= 70) || (key[i] >= 97 && key[i] <= 102)) {
	
		}
		else{
			return "Bad key (not all hex digits)";
		}
	}
			

	if(val == "") {
		return "Empty val";
	}

	if(Nkeys >= Keys.size()) {
		return "Hash table full";
	}
	
	for(size_t i = 0; i < Keys.size(); i++) {
		if(key == Keys[i]) {
			return "Key already in the table";
		}
	}

	istringstream ss;
	string Last7numbers, Less7;
	int temp;
	int XOR1 = 0;
	vector <string> ksize;
	vector <int> Intpb;
	int testL, testX;
	istringstream ssd;

//Lines 100 - 114 is the hash function for the last 7 digits
		if(key.size() > 7) {
			Last7numbers = key.substr(key.size() - 7, key.size()); 
			ss.clear();
			ss.str(Last7numbers);
		}

		else { 
			Less7 = key;
			ss.clear();
			ss.str(Less7);
		}
			
		ss >> hex >> temp;
		temp = temp % Keys.size();

//Lines 116 - 137 is the hash function for the XOR, this uses a method of str.substr and grabs a range of certain number and then for XOR module for remainder.
		int remainder = key.size() % 7;		
		
		for(size_t i = 0; i < (key.size() / 7); i++) {
				ksize.push_back(key.substr(i * 7, 7));
		}
		if(remainder != 0) {
			ksize.push_back(key.substr(7 * (key.size() / 7), key.size()));
		}
			Intpb.resize(ksize.size());
		

		for(size_t i = 0; i < ksize.size(); i++) {
				ssd.clear();
				ssd.str(ksize[i]);
				ssd >> hex >> Intpb[i];
		}
		for(size_t i = 0; i <Intpb.size(); i++) {
			XOR1 ^= Intpb[i];
		}

		XOR1 = XOR1 % Keys.size();
		
		testL = temp;
		testX = XOR1;
		
//Lines 142 - 198 is the collision detection for both linear and double detection
		if(Fxn == 'L') {
			if(Coll == 'L') {
				for(size_t i = 0; i < Keys.size(); i++) {
					if(Keys[ (testL + i) % Keys.size() ] == "") {
						Keys[ (testL + i) % Keys.size() ] = key;
						Vals[ (testL + i) % Keys.size() ] = val;
						Nkeys++;
						return "";
						//break;
					}
				}
			}
			if(Coll == 'D') {
				for(size_t i = 0; i < Keys.size(); i++) {
						int tempp = (testX % Keys.size());
						if(tempp == 0) {
							tempp = 1;
						}
					if(Keys[ (testL + i * (tempp)) % Keys.size()] == "") {
						Keys[ (testL + i * (tempp)) % Keys.size()] = key;
						Vals[ (testL + i * (tempp)) % Keys.size()] = val;
						Nkeys++;
						return "";
						//break;
					}
				}
			}
		}
		if(Fxn == 'X') {
			if(Coll == 'L') {
				for(size_t i = 0; i < Keys.size(); i++) {
					if(Keys[ (testX + i) % Keys.size() ] == "") {
					Keys[ (testX + i) % Keys.size() ] = key;
					Vals[ (testX + i) % Keys.size() ] = val;
					Nkeys++;
					return "";
					//break;
				}
			}
		}
			if(Coll == 'D') {
				for(size_t i = 0; i < Keys.size(); i++) {
					int temppp = (testL % Keys.size());
					if(temppp == 0) {
						temppp = 1;
					}
					if(Keys[ (testX + i * (temppp)) % Keys.size()] == "") {
						Keys[ (testX + i * (temppp)) % Keys.size()] = key;
						Vals[ (testX + i * (temppp)) % Keys.size()] = val;
						Nkeys++;
						return "";
						//break;
					}
				}
			}
		}
  return "Cannot insert key";
}

string Hash_140::Find(const string &key)
{
//Error checks to make sure input is hex.
	for(size_t i = 0; i < key.size(); i++) {
		if((key[i] >= 48 && key[i] <= 57) || (key[i] >= 65 && key[i] <= 70) || (key[i] >= 97 && key[i] <= 102)) {
			
		}
		else{
			return "";
		}
	}
	
	istringstream ss;
	string Last7numbers, Less7;
	int temp;
	int XOR1 = 0;
	vector <string> ksize;
	vector <int> Intpb;
	int testL, testX;
	istringstream ssd;

//Lines 222 - 236 is the hash function for the last 7 digits
		if(key.size() > 7) {
			Last7numbers = key.substr(key.size() - 7, key.size()); 
			ss.clear();
			ss.str(Last7numbers);
		}

		else { 
			Less7 = key;
			ss.clear();
			ss.str(Less7);
		}
			
		ss >> hex >> temp;
		temp = temp % Keys.size();


//Lines 239 - 259 is the hash function for the XOR
		int remainder = key.size() % 7;

		for(size_t i = 0; i < key.size() / 7; i++) {
				ksize.push_back(key.substr(i * 7, 7));
		}
		if(remainder != 0) {
			ksize.push_back(key.substr(7 * (key.size() / 7), key.size()));
		}
			Intpb.resize(ksize.size());
	

		for(size_t i = 0; i < ksize.size(); i++) {
				ssd.clear();
				ssd.str(ksize[i]);
				ssd >> hex >> Intpb[i];
		}
		for(size_t i = 0; i <Intpb.size(); i++) {
			XOR1 ^= Intpb[i];
		}
		XOR1 = XOR1 % Keys.size();
		
		testL = temp;
		testX = XOR1;
//Lines 263 - 307 is the collision detection
		if(Fxn == 'L') {
			if(Coll == 'L') {
				for(size_t i = 0; i < Keys.size(); i++) {
					if(Keys[ (testL + i) % Keys.size() ] == key) {
						return Vals[ (testL + i) % Keys.size() ];
					}
					Nprobes++;
				}
			}
			if(Coll == 'D') {
				for(size_t i = 0; i < Keys.size(); i++) {
						int tempp = (testX % Keys.size());
						if(tempp == 0) {
							tempp = 1;
						}
					if(Keys[ (testL + i * (tempp)) % Keys.size()] == key) {
						return Vals[ (testL + i * (tempp)) % Keys.size()];
					}
					Nprobes++;
				}
			}
		}
		if(Fxn == 'X') {
			if(Coll == 'L') {
				for(size_t i = 0; i < Keys.size(); i++) {
					if(Keys[ (testX + i) % Keys.size() ] == key) {
					return Vals[ (testX + i) % Keys.size() ];
				}
				Nprobes++;
			}
		}
			if(Coll == 'D') {
				for(size_t i = 0; i < Keys.size(); i++) {
					int temppp = (testL % Keys.size());
					if(temppp == 0) {
						temppp = 1;
					}
					if(Keys[ (testX + i * (temppp)) % Keys.size()] == key) {
						return Vals[ (testX + i * (temppp)) % Keys.size()] ;
					}
					Nprobes++;
				}
			}
		}

return "";
}

	
void Hash_140::Print() const
{
	//This will print the info
	for(size_t i = 0; i < Keys.size(); i++) {
		if(Keys[i] != "") {
			printf("%5lu %s %s\n", i, Keys[i].c_str(), Vals[i].c_str());
		}
	}

}
//Total collisions found by traversing the keys of vectors. 0 - size;
size_t Hash_140::Total_Probes()
{
	if(Keys.size() == 0) {
		return 0;
	}
	Nprobes = 0;
	for(size_t i = 0; i < Keys.size(); i++) {
		if(Keys[i] != "") {
			Find(Keys[i]);
		}
	}


  return Nprobes;
}
