#include <iostream>

using namespace std;

int main() {

	string name;

	cout << "Enter name";
	cin >> name;
	if(cin.fail()) {
		cerr << "error" << endl;
	}
	else {
		cout << name << endl;
	}
	return 0;
}
