#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

int main(){
	int tmp, sum = 0;
	char ch;
	string filename;

	cout << "入力するファイル名を入力してください > ";
	cin >> filename;
	
	ifstream ifs(filename.c_str());
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	if(!ifs) throw runtime_error("入力ファイルを開けませんでした。: " + filename);

	while(!ifs.eof()){	// EOFでループを抜ける
		ifs >> tmp;
		if(ifs.fail()){
			ifs.clear();
			ifs >> ch;
			continue;
		}
		sum += tmp;
	}

	cout << "sum: " << sum << endl;
}