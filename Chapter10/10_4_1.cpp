#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

int main(){
	string name, tmp;

	cout << "Please enter input file name: ";	
	cin >> name;
	ifstream ist(name.c_str());	// istはnameによって関連づけられた入力ストリーム
	if(!ist) throw runtime_error("can't open input file: " + name);

	cout << "Please enter output file name: ";
	cin >> name;
	ofstream ost(name.c_str()); // ostはnameによって関連づけられた出力ストリーム
	if(!ost) throw runtime_error("can't open output file: " + name);

	while(getline(ist, tmp)){
		ost << tmp << endl;
		cout << tmp << endl;
	}
}