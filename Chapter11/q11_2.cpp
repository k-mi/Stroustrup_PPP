#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <stdexcept>
using namespace std;

// 母音の場合かどうか判定
bool is_vowel(char c){
	switch(c){
		case 'a': case 'i': case 'u': case 'e': case 'o':
		case 'A': case 'I': case 'U': case 'E': case 'O':
			return true;
		default:
			return false;
	}
}

int main(){
	string filename, line, word, tmp;
	vector<string> words;
	vector< vector<string> > strings;

	cout << "ファイルからすべての母音を削除します。" << endl;
	cout << "ファイルの名前を入力してください。 > ";
	cin >> filename;
	ifstream ifs(filename);
	if(!ifs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	while(getline(ifs, line)){
		istringstream iss(line);
		words.clear();
		while(iss >> word){
			tmp = "";
			for(int i = 0; i < word.size(); ++i)
				if(!is_vowel(word[i]))
					tmp += word[i];
			if(tmp != "")
				words.push_back(tmp);
		}
		strings.push_back(words);
	}
	ifs.close();

	ofstream ofs(filename, ios_base::trunc);
	if(!ofs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	for(int i = 0; i < strings.size(); ++i){
		for(int j = 0; j < strings[i].size(); ++j)
			if(j != strings[i].size() - 1)
				ofs << strings[i][j] << ' ';
			else
				ofs << strings[i][j];
		ofs << endl;
	}
}