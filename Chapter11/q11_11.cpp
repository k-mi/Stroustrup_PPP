#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

int main(){
	char tmp;
	string filename;
	vector<char> v;

	cout << "ファイル名を入力してください。 > ";
	cin >> filename;
	ifstream ifs(filename.c_str(), ios_base::ate);	// 末尾へ移動する
	if(!ifs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	// tellg()でファイルの現在の位置を取得（実際の返り値はifstream::pos_type）
	for(int p = (int)ifs.tellg() - 1; p >= 0; p -= 1){
		ifs.seekg(p);
		ifs.get(tmp);
		v.push_back(tmp);
	}

	for(int i = 0; i < v.size(); ++i)
		cout << v[i];
	cout << endl;
}