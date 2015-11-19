#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

int main(){
	int num, count;
	string filename;
	vector<int> v;

	cout << "入力するファイル名を入力してください。 > ";
	cin >> filename;
	ifstream ifs(filename.c_str());
	if(!ifs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	while(ifs >> num)
		v.push_back(num);

	sort(v.begin(), v.end());

	for(int i = 0; i < v.size(); ++i){
		if(i == 0){
			cout << v[i];
			count = 1;
		}
		else if(v[i] != v[i-1]){	// 重複終了
			if(count > 1)
				cout << '\t' << count << endl << v[i];
			else
				cout << endl << v[i];
			count = 1;
		}
		else
			count++;
	}
	cout << endl;
}