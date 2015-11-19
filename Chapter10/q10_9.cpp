#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

int main(){
	string filename, s1, s2;
	const string end = "~";

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

	ifs1 >> s1;
	ifs2 >> s2;
	while(s1 != end || s2 != end){
		if(s1 <= s2){
			ofs << s1 << endl;
			ifs1 >> s1;
			if(ifs1.eof()) s1 = end;
		}
		else if(s1 > s2){
			ofs << s2 << endl;
			ifs2 >> s2;
			if(ifs2.eof()) s2 = end;
		}
	}
}
