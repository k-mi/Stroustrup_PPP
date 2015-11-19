#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

int main(){
	string filename;
	cout << "input file: ";
	cin >> filename;

	ifstream ifs(filename);
	if(!ifs) return 0;

	// クレジットカードのフォーマット
	regex amex("3[47]\\d{13}");
	regex diners("30[0-5]\\d{11}|3095\\d{10}|3[689]\\d{12}");
	regex jcb("35[2-8]\\d{13}");
	regex master("5\\d{15}");
	regex visa("4\\d{16}|4\\d{13}");
	
	string line;
	int lineno = 1;
	while(getline(ifs, line)){
		if(regex_search(line, amex) || regex_search(line, diners) || regex_search(line, jcb) 
			|| regex_search(line, master) || regex_search(line, visa))
			cout << lineno << ": " << line << endl;
		++lineno;
	}
}