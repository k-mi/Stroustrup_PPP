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

	cout << "output file: ";
	cin >> filename;
	ofstream ofs(filename);
	if(!ofs) return 0;

	// アメリカ式の日付の検索フォーマット
	regex pat1("(\\d{1,2})\\s?[/.-]\\s?(\\d{1,2})\\s?[/.-]\\s?(\\d{4}|\'\\d{2})");
	regex pat2("(\\d{1,2})\\s?(January|February|March|April|May|June|July|August|September|October|November|December)\\s?(\\d{4})");
	regex pat3("(January|February|March|April|May|June|July|August|September|October|November|December)\\s?(\\d{1,2})[\\s,]\\s?(\\d{4})");

	// 置きかえるフォーマット
	string format1("$3-$1-$2");
	string format2("$3-$2-$1");

	string line;
	while(getline(ifs, line)){
		line = regex_replace(line, pat1, format1);
		line = regex_replace(line, pat2, format2);
		line = regex_replace(line, pat3, format1);

		ofs << line << endl;
	}
}