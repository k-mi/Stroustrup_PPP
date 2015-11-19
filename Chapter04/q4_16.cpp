#include "std_lib_facilities.h"
#include <cassert>

int main(){
	int tmp, count, max = 0, mode = -1;
	vector<int> numbers;

	while(cin >> tmp)
		numbers.push_back(tmp);

	for(int i = 0; i < numbers.size(); ++i){
		count = 0;
		for(int j = i; j < numbers.size(); ++j){
			if(numbers[i] == numbers[j] && numbers[i] >= 0)
				count++;
		}
		if(count > max){
			max = count;
			mode = numbers[i];
		}
	}

	assert(mode != -1);
	cout << "最頻値: " << mode << endl;
}