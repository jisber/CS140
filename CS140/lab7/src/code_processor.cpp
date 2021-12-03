//Jacob Isber
//Lab7
//10-24-19
#include "code_processor.hpp"
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

using namespace std;

//Adds the prizes to the Prize map.
bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity){
	
	if(points <= 0 || quantity <= 0)
		return false;
	if(Prizes.find(id) != Prizes.end()) 
		return false;
	
	Prize *p1;
	p1 = new Prize;
	p1->id = id;
	p1->description  = description; 
	p1->points = points;
	p1->quantity = quantity;
	Prizes.insert(make_pair(id,p1));

	return true;
}

//Adds the username to the User map
bool Code_Processor::New_User(const string &username, const string &realname, int starting_points){
	
	if(starting_points < 0) 
		return false;
	if(Names.find(username) != Names.end()) 
		return false;

	User *u1 = new User;
	u1 -> username = username;
	u1 -> realname = realname;
	u1 -> points = starting_points;
	Names.insert(make_pair(username, u1));
	
	return true;
}
//Deletes the user and phones
bool Code_Processor::Delete_User(const string &username){

	map <string, User*>::const_iterator nit;
	set <string>::const_iterator sit;
	nit = Names.find(username);

	if(Names.find(username) == Names.end()) 
		return false;
	
	for(sit = nit->second->phone_numbers.begin(); sit != nit->second->phone_numbers.end(); sit++) {
		Remove_Phone(username, *sit);
	}

	delete nit->second;
	Names.erase(username);

	return true;
}
//Adds the users phone to both the map and set.
bool Code_Processor::Add_Phone(const string &username, const string &phone){

	map <string, User*>::const_iterator nit;
	map<string, User*>::const_iterator mit;
	nit = Names.find(username);

	if(Names.find(username) == Names.end()) 
		return false;
	if(Phones.find(phone) != Phones.end()) 
		return false;
	
	nit->second->phone_numbers.insert(phone);

	Phones.insert(make_pair(phone, nit->second));

	return true;
}

//Removes the phone from both the map and the set
bool Code_Processor::Remove_Phone(const string &username, const string &phone){

	map <string, User*>::const_iterator nit;
	nit = Names.find(username);
	if(Names.find(username) == Names.end())
		return false;
	if(Phones.find(phone) == Phones.end()) 
		return false;
	if(Phones.find(phone)->second->username != username) 
		return false;

	nit->second->phone_numbers.erase(phone);
	Phones.erase(phone);

	return true;
}

//This shows all the phone numbers assigned to that user
string Code_Processor::Show_Phones(const string &username) const{

	string usernum;
	set <string>::const_iterator sit;
	map <string, User*>::const_iterator nit;
	nit = Names.find(username);
	if(Names.find(username) == Names.end())
		return "BAD USER";
	if(Names.find(username)->second->phone_numbers.empty()) 
		return "";
	
	for(sit = nit->second->phone_numbers.begin(); sit != nit->second->phone_numbers.end(); sit++) {
		usernum += *sit;
		usernum += "\n";
	}

	
	return usernum;
}
//Allows user to redeem codes.
int Code_Processor::Enter_Code(const string &username, const string &code){
	
	map <string, User*>::const_iterator nit;
	set <string>::const_iterator sit; 
	if(Codes.find(code) != Codes.end())
		return -1;
	if(Names.find(username) == Names.end()) 
		return -1;
	nit = Names.find(username);

	  size_t i;
	  unsigned int h;
	  h = 5381;
		for (i = 0; i < code.size(); i++) {
			h = (h << 5) + h + code[i];
		}
		if(h % 17 == 0) {
			nit->second->points += 10;
			Codes.insert(code);
			return 10;
		}
		else if(h % 13 == 0) {
			nit->second->points += 3;
			Codes.insert(code);
			return 3;
		}
		else return 0;

	return 0;
}
//Allows user to text code
int Code_Processor::Text_Code(const string &phone, const string &code){

	map <string, User*>::const_iterator nit;
	set <string>::const_iterator sit; 
	if(Codes.find(code) != Codes.end()) 
		return -1;
	if(Phones.find(phone) == Phones.end()) 
		return -1;
	nit = Phones.find(phone);
	
	  size_t i;
	  unsigned int h;
	  h = 5381;
		for (i = 0; i < code.size(); i++) {
			h = (h << 5) + h + code[i];
		}
		if(h % 17 == 0) {
			nit->second->points += 10;
			Codes.insert(code);
			return 10;
		}
		else if(h % 13 == 0) {
			nit->second->points += 3;
			Codes.insert(code);
			return 3;
		}
		else return 0;

	return 0;
}

//If the code is used, insert into the code set. 
bool Code_Processor::Mark_Code_Used(const string &code){
	size_t i;
	unsigned int h;
	if(Codes.find(code) != Codes.end()) 
		return false;

	h = 5381;
	for (i = 0; i < code.size(); i++) {
		h = (h << 5) + h + code[i];
	}
	if(h % 17 != 0 && h % 13 != 0) 
		return false;
	else {
		Codes.insert(code);
	}

	return true;
}

//Returns user balance
int Code_Processor::Balance(const string &username) const{
	
	if(Names.find(username) == Names.end()) 
		return -1;
	
	map<string, User*>::const_iterator mit;
	mit = Names.find(username);
	return mit->second->points;
}

//This allows a user to redeme a prize
bool Code_Processor::Redeem_Prize(const string &username, const string &prize){
	
	map<string, User*>::const_iterator mit;
	map<string, Prize*>::const_iterator nit;
	mit = Names.find(username);
	nit = Prizes.find(prize);
	if(Names.find(username) == Names.end()) 
		return false;
	if(Prizes.find(prize) == Prizes.end()) 
		return false;

	if(mit->second->points < nit->second->points){
		return false;
	}
	
	else {
		mit->second->points = mit->second->points - nit->second->points;
		nit->second->quantity -= 1;
		if(nit->second->quantity <= 0) {
			delete nit->second;
			Prizes.erase(prize);
		}
	}

	return true;
}

//This is the deconstructor.										   
Code_Processor::~Code_Processor(){
	
	map <string, Prize*>::const_iterator nit;
	map<string, User*>::const_iterator mit;

	for(mit = Names.begin(); mit != Names.end(); mit++) {
		delete mit->second;
	}


	for(nit = Prizes.begin(); nit != Prizes.end(); nit++) {
		delete nit->second;
	}
}

//This writes to the file. A TA helped me with the marked used portion on piazza. 
bool Code_Processor::Write(const string &filename) const{
	FILE * file;
	int counter = 0;
	map <string, Prize*>::const_iterator nit;
	map<string, User*>::const_iterator mit;
	set <string>::const_iterator sit;;	
	set <string>::const_iterator pit;;	
	
	file = fopen (filename.c_str(), "w");
	if(file == NULL) 
		return false;
	
	for(nit = Prizes.begin(); nit != Prizes.end(); nit++) {
		fprintf(file, "PRIZE %s %d %d %s \n", nit->second->id.c_str(),nit->second->points, nit->second->quantity, nit->second->description.c_str());
	}
	for(mit = Names.begin(); mit != Names.end(); mit++) {
		fprintf(file, "ADD_USER %s %d %s \n", mit->second->username.c_str(), mit->second->points, mit ->second-> realname.c_str());
		if(!(mit ->second->phone_numbers.empty())) {
			for(sit = mit->second->phone_numbers.begin(); sit != mit->second->phone_numbers.end(); sit++) {
				fprintf(file, "ADD_PHONE %s %s\n", mit->second->username.c_str(), (*sit).c_str()); 		
			}
		}
	}

//Apparently the marked used only allowed 8 codes to print out at once so that is what the counter and for loop is for.
	if(!(Codes.empty())) {
		fprintf(file, "MARK_USED ");
	}
		for(pit = Codes.begin(); pit != Codes.end(); pit++) {
			fprintf(file, "%s ", (*pit).c_str());
			if(counter != 0 && counter % 8 == 0) { 
				fprintf(file, "\nMARK_USED ");
			}
			counter++;
		}
	
	fprintf(file, "\n");
	fclose(file);
	return true;
}
