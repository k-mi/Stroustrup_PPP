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

	// アメリカ式の日付のフォーマット
	regex pat1("\\d{1,2}\\s?[/.-]\\s?\\d{1,2}\\s?[/.-]\\s?(\\d{4})|(\'\\d{2})");
	regex pat2("\\d{1,2}\\s?(January|February|March|April|May|June|July|August|September|October|November|December)\\s?\\d{4}");
	regex pat3("(January|February|March|April|May|June|July|August|September|October|November|December)\\s?\\d{1,2}[\\s,]\\s?\\d{4}");

	string line;
	int lineno = 1;
	while(getline(ifs, line)){
		if(regex_search(line, pat1) || regex_search(line, pat2) || regex_search(line, pat3))
			cout << lineno << ": " << line << endl;
		++lineno;
	}
}