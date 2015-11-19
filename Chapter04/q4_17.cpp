#include "std_lib_facilities.h"

int main(){
	int count, count_max = 0;
	string tmp, mode, max = "", min = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
	vector<string> strings;

	while(cin >> tmp){
		strings.push_back(tmp);

		if(min > tmp)
			min = tmp;
		if(max < tmp)
			max = tmp;
	}

	for(int i = 0; i < strings.size(); ++i){
		count = 0;
		for(int j = i; j < strings.size(); ++j){
			if(strings[i] == strings[j])
				count++;
		}
		if(count > count_max){
			count_max = count;
			mode = strings[i];
		}
	}

	cout << "最小値: " << min << endl;
	cout << "最大値: " << max << endl;
	cout << "最頻値: " << mode << endl;
}