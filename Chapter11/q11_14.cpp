#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
using namespace std;

int main(){
	double d;
	string filename;

	cout << "入力するファイル名を入力してください。 > ";
	cin >> filename;
	ifstream ifs(filename.c_str());
	if(!ifs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	cout << "出力するファイル名を入力してください。 > ";
	cin >> filename;
	ofstream ofs(filename.c_str());
	if(!ofs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	ofs << setprecision(8) << scientific;	// フォーマットの指定
	while(ifs){
		for(int i = 0; i < 4; ++i){
			if(ifs){
				ifs >> d;
				ofs << setw(20) << d;
			}
		}
		ofs << endl;
	}	
}