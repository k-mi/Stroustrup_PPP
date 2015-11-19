#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <cctype>		// isupper
#include <regex>		// regex_replace (C++11)
using namespace std;

int main() {
	string filename;	// ファイル名
	cout << "inputfile: ";
	cin >> filename;
	ifstream ifs(filename.c_str());
	if(!ifs) {
		cerr << "input file can't open: " << filename << endl;
		return 0;
	}
	cout << "outputfile: ";
	cin >> filename;
	ofstream ofs(filename.c_str());
	if(!ofs) {
		cerr << "output file can't open: " << filename << endl;
		return 0;
	}

	vector<string> words;		// 単語を維持する
	set<string> ss;

	string line, word;
	while(getline(ifs, line)) {
		// 記号をホワイトスペースに変換
		line = regex_replace(line, regex("[.,:;!?\"(){}\\[\\]]"), " ");

		// キャピタライズ（大文字→小文字）
		for(int i = 0; i < line.size(); ++i)
			if(isupper(line[i])) line[i] += 32;

		// 否定形（can't→can not, *n't→* not）
		line = regex_replace(line, regex("can't"), "can not");
		line = regex_replace(line, regex("n't"), " not");

		// ホワイトスペースで単語に分割
		string tmp;
		istringstream iss(line);
		while(iss >> tmp) {
			words.push_back(tmp);
			ss.insert(tmp);
		}
		words.push_back("\n");
	}

	// 複数形の処理（たとえばshipsはshipとして扱う）
	set<string> multipul;
	for(vector<string>::iterator p = words.begin(); p != words.end(); ++p)
		if(ss.find(*p + "s") != ss.end()) multipul.insert(*p + "s");

	// 出力
	for(vector<string>::iterator p = words.begin(); p != words.end(); ++p) {
		if(multipul.find(*p) != multipul.end())	
			(*p).resize(p->size() - 1);
		if(*p == "\n") ofs << *p;
		else ofs << *p << ' ';
	}
}