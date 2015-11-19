#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

int main(){
	int count = 1;			// ファイルの行数
	string filename, line, word;

	cout << "入力するファイル名を入力してください > ";
	cin >> filename;
	ifstream ifs(filename.c_str());
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	if(!ifs) throw runtime_error("入力ファイルを開けませんでした。: " + filename);

	cout << "検索する単語を入力してください > ";
	cin >> word;

	while(getline(ifs, line)){
		string::size_type s = line.find(word);
		if(s != string::npos)
			cout << count << ": " << line << endl;
		count++;
	}
}