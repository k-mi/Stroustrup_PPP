// Visual Studio(Windows)では正常に動作

#include "std_lib_facilities.h"
using namespace std;

void input_name(vector<string>& name){
	string tmp;

	cout << "名前を入力してください > ";
	while(!cin.fail()){
		cin >> tmp;
		if(!cin.fail()){
			name.push_back(tmp);
			cout << "名前を入力してください > ";
		}
	}
	
	// cinのバッファをflushする
	cin.clear();
	int StreamBufSize = cin.rdbuf()->in_avail();
	cin.ignore(StreamBufSize,EOF);
}

void input_age(const vector<string>& name, vector<int>& age){
	for(int i = 0; i < name.size(); ++i){
		int tmp;
		cout << name[i] << "の年齢を入力してください > ";
		cin >> tmp;
		age.push_back(tmp);
	}
}

void print(const vector<string>& name, const vector<int>& age){
	for(int i = 0; i < name.size(); ++i)
		cout << name[i] << ", " << age[i] << endl;
}

void sort_name(vector<string>& name, vector<int>& age){
	vector<string> copy_name = name;
	vector<int> copy_age = age;
	sort(name.begin(), name.end());

	for(int i = 0; i < name.size(); ++i){
		for(int j = 0; j < name.size(); ++j){
			if(name[i] == copy_name[j]){
				age[i] = copy_age[j];
				break;
			}
		}
	}
}

int main(){
	vector<string> name;
	vector<int> age;

	input_name(name);
	input_age(name, age);

	cout << "------------" << endl;

	print(name, age);

	cout << "------------" << endl;

	sort_name(name, age);
	print(name, age);
}