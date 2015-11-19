#include "std_lib_facilities.h"

/*
bool conjunctions(){
	string tmp;
	cin >> tmp;

	if(tmp == "and" || tmp == "or" || tmp == "but")
		return true;
	else
		return false;
}
*/

bool conjunctions(string tmp){
	if(tmp == "and" || tmp == "or" || tmp == "but")
		return true;
	else
		return false;
}

bool noun(){
	string tmp;
	cin >> tmp;

	if(tmp == "."){
		cout << "not OK" << endl;
		exit(EXIT_FAILURE);
	}

	if(tmp == "birds" || tmp == "fish" || tmp == "C++")
		return true;
	else
		return false;	
}

bool verb(){
	string tmp;
	cin >> tmp;

	if(tmp == "."){
		cout << "not OK" << endl;
		exit(EXIT_FAILURE);
	}

	if(tmp == "rules" || tmp == "fly" || tmp == "swim")
		return true;
	else
		return false;
}

bool sentence(){
	string tmp;
	cin >> tmp;

	if(tmp == "the" && noun() && verb())
		return true;
	else
		return false;
}

int main(){
	bool b = sentence();
	string tmp;
	cin >> tmp;

	if(b && tmp == ".")
		cout << "OK" << endl;
	else if(b && conjunctions(tmp) && sentence() && cin >> tmp && tmp == ".")
		cout << "OK" << endl;
	else
		cout << "not OK" << endl;
}