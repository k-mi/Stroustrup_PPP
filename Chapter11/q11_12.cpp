#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

int main(){
	string tmp;
	string filename;
	vector<string> v;

	cout << "ファイル名を入力してください。 > ";
	cin >> filename;
	ifstream ifs(filename.c_str());
	if(!ifs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	while(ifs >> tmp)
		v.push_back(tmp);

	for(int i = v.size() - 1; i >= 0; --i)
		cout << v[i] << ' ';
	cout << endl;
}