#include <iostream>
#include <fstream>
#include <cctype>
#include <stdexcept>
using namespace std;

int main(){
	string filename, line;

	cout << "読み取るテキストファイルの名前を入力してください。 > ";
	cin >> filename;
	ifstream ifs(filename);
	if(!ifs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	cout << "書き出すテキストファイルの名前を入力してください。 > ";
	cin >> filename;
	ofstream ofs(filename);
	if(!ofs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	while(getline(ifs, line)){	// 1行ずつ取得
		for(int i = 0; i < line.size(); ++i)
			ofs << (char)tolower(line[i]);
		ofs << endl;
	}
}