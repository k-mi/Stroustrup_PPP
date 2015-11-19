#include <iostream>
#include <regex>
using namespace std;

int main(){
	string input = "\n";

	if(regex_match(input, regex("\\n"))) cout << "matched" << endl;
	else cout << "unmatched" << endl;
}