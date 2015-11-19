#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

int main(){
	string filename, s;

	cout << "1つ目のファイル名を入力してください。 > ";
	cin >> filename;
	ifstream ifs1(filename);
	if(!ifs1) throw runtime_error("ファイルを開けませんでした: " + filename);

	cout << "2つ目のファイル名を入力してください。 > ";
	cin >> filename;
	ifstream ifs2(filename);
	if(!ifs2) throw runtime_error("ファイルを開けませんでした: " + filename);

	cout << "出力先のファイル名を入力してください。 > ";
	cin >> filename;
	ofstream ofs(filename);
	if(!ofs) throw runtime_error("ファイルを開けませんでした: " + filename);

	while(getline(ifs1, s))
		ofs << s << endl;
	while(getline(ifs2, s))
		ofs << s << endl;
}
